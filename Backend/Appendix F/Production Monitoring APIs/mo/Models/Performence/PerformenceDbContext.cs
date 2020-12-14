using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace mo.Models.Performence
{
    public class PerformenceDbContext : DbContext
    {
        public DbSet<Performence> Performence { get; set; }

        public PerformenceDbContext(DbContextOptions<PerformenceDbContext> options) : base(options)
        {
        }
        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            modelBuilder.Entity<Performence>().ToTable("Performence");
        }
    }
}


