using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace mo.Models.MobileDesign
{
    public class MobileTypeDbContext : DbContext
    {
        public DbSet<MobileType> MobileType { get; set; }


        public MobileTypeDbContext(DbContextOptions<MobileTypeDbContext> options) : base(options)
        {
        }
        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            modelBuilder.Entity<MobileType>().ToTable("MobileType");
        }
    }
}
