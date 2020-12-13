using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Hosting;
using Microsoft.AspNetCore.HttpsPolicy;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;
using mo.Models;
using mo.Models.Avaliability;
using mo.Models.MobileDesign;
using mo.Models.MonitoringPoint;
using mo.Models.OrderModel;
using mo.Models.Performence;
using mo.Models.Quality;

namespace mo
{
    public class Startup
    {
        public Startup(IConfiguration configuration)
        {
            Configuration = configuration;
        }

        public IConfiguration Configuration { get; }

        // This method gets called by the runtime. Use this method to add services to the container.
        public void ConfigureServices(IServiceCollection services)
        {
            services.AddSwaggerGen();
            services.AddDbContext<CustomersDbContext>(options => options.UseSqlServer(Configuration.GetConnectionString("ProductionMonitoringDbConnectionString")));
            services.AddDbContext<OrderDbContext>(options => options.UseSqlServer(Configuration.GetConnectionString("ProductionMonitoringDbConnectionString")));
            services.AddDbContext<OrderLineDbContext>(options => options.UseSqlServer(Configuration.GetConnectionString("ProductionMonitoringDbConnectionString")));
            services.AddDbContext<CaseModelDbContext>(options => options.UseSqlServer(Configuration.GetConnectionString("ProductionMonitoringDbConnectionString")));
            services.AddDbContext<MobileTypeDbContext>(options => options.UseSqlServer(Configuration.GetConnectionString("ProductionMonitoringDbConnectionString")));
            services.AddDbContext<MonitoringPointDbContext>(options => options.UseSqlServer(Configuration.GetConnectionString("ProductionMonitoringDbConnectionString")));
            services.AddDbContext<AvaliabilityDbContext>(options => options.UseSqlServer(Configuration.GetConnectionString("ProductionMonitoringDbConnectionString")));
            services.AddDbContext<PerformenceDbContext>(options => options.UseSqlServer(Configuration.GetConnectionString("ProductionMonitoringDbConnectionString")));
            services.AddDbContext<QualityDbContext>(options => options.UseSqlServer(Configuration.GetConnectionString("ProductionMonitoringDbConnectionString")));
           
            services.AddControllers();
        }

        // This method gets called by the runtime. Use this method to configure the HTTP request pipeline.
        public void Configure(IApplicationBuilder app, IWebHostEnvironment env)
        {
            if (env.IsDevelopment())
            {
                app.UseDeveloperExceptionPage();
            }
            // Enable middleware to serve generated Swagger as a JSON endpoint.
            app.UseSwagger();

            // Enable middleware to serve swagger-ui (HTML, JS, CSS, etc.),
            // specifying the Swagger JSON endpoint.
            app.UseSwaggerUI(c =>
            {
                c.SwaggerEndpoint("/swagger/v1/swagger.json", "My API V1");
            });

            app.UseHttpsRedirection();

            app.UseRouting();

            app.UseAuthorization();

            app.UseEndpoints(endpoints =>
            {
                endpoints.MapControllers();
            });
        }
    }
}
