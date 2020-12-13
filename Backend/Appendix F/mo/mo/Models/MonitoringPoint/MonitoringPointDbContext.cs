using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace mo.Models.MonitoringPoint
{
    public class MonitoringPointDbContext : DbContext
    {
        public DbSet<MonitoringPoint> MonitoringPoints { get; set; }

        public MonitoringPointDbContext(DbContextOptions<MonitoringPointDbContext> options) : base(options)
        {
        }
        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            modelBuilder.Entity<MonitoringPoint>().ToTable("MonitoringPoint");
        }
    }
}