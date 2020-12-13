using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace mo.Models.MobileDesign
{
    public class CaseModelDbContext : DbContext
    {
        public DbSet<CaseModel> CaseModels { get; set; }


        public CaseModelDbContext(DbContextOptions<CaseModelDbContext> options) : base(options)
        {
        }
        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            modelBuilder.Entity<CaseModel>().ToTable("CaseModel");
        }
    }
}
