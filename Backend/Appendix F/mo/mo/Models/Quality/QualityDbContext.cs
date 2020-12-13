using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace mo.Models.Quality
{
    public class QualityDbContext : DbContext
    {
        public DbSet<Quality> Quality { get; set; }

        public QualityDbContext(DbContextOptions<QualityDbContext> options) : base(options)
        {
        }
        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            modelBuilder.Entity<Quality>().ToTable("Quality");
        }
    }
}