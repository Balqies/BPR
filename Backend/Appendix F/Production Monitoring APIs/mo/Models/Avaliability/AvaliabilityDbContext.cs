using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace mo.Models.Avaliability
{
    public class AvaliabilityDbContext : DbContext
    {
        public DbSet<Avaliability> Avaliabilitys { get; set; }

        public AvaliabilityDbContext(DbContextOptions<AvaliabilityDbContext> options) : base(options)
        {
        }
        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            modelBuilder.Entity<Avaliability>().ToTable("Avaliability");
        }
    }
}

