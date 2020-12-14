using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace mo.Models.OrderModel
{
    public class OrderLineDbContext : DbContext
    {
        public DbSet<OrderLine> OrderLines { get; set; }

        public OrderLineDbContext(DbContextOptions<OrderLineDbContext> options) : base(options)
        {
        }
        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            modelBuilder.Entity<OrderLine>().ToTable("OrderLine");
        }
    }
}