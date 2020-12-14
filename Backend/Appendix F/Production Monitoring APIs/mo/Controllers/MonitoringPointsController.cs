using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using mo.Models.MonitoringPoint;

namespace mo.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class MonitoringPointsController : ControllerBase
    {
        private readonly MonitoringPointDbContext _context;

        public MonitoringPointsController(MonitoringPointDbContext context)
        {
            _context = context;
        }

        // GET: api/MonitoringPoints
        [HttpGet]
        public async Task<ActionResult<IEnumerable<MonitoringPoint>>> GetMonitoringPoints()
        {
            return await _context.MonitoringPoints.ToListAsync();
        }

        // GET: api/MonitoringPoints/5
        [HttpGet("{id}")]
        public async Task<ActionResult<MonitoringPoint>> GetMonitoringPoint(int id)
        {
            var monitoringPoint = await _context.MonitoringPoints.FindAsync(id);

            if (monitoringPoint == null)
            {
                return NotFound();
            }

            return monitoringPoint;
        }

        // PUT: api/MonitoringPoints/5
        // To protect from overposting attacks, enable the specific properties you want to bind to, for
        // more details, see https://go.microsoft.com/fwlink/?linkid=2123754.
        [HttpPut("{id}")]
        public async Task<IActionResult> PutMonitoringPoint(int id, MonitoringPoint monitoringPoint)
        {
            if (id != monitoringPoint.id)
            {
                return BadRequest();
            }

            _context.Entry(monitoringPoint).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!MonitoringPointExists(id))
                {
                    return NotFound();
                }
                else
                {
                    throw;
                }
            }

            return NoContent();
        }

        // POST: api/MonitoringPoints
        // To protect from overposting attacks, enable the specific properties you want to bind to, for
        // more details, see https://go.microsoft.com/fwlink/?linkid=2123754.
        [HttpPost]
        public async Task<ActionResult<MonitoringPoint>> PostMonitoringPoint(MonitoringPoint monitoringPoint)
        {
            _context.MonitoringPoints.Add(monitoringPoint);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetMonitoringPoint", new { id = monitoringPoint.id }, monitoringPoint);
        }

        // DELETE: api/MonitoringPoints/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<MonitoringPoint>> DeleteMonitoringPoint(int id)
        {
            var monitoringPoint = await _context.MonitoringPoints.FindAsync(id);
            if (monitoringPoint == null)
            {
                return NotFound();
            }

            _context.MonitoringPoints.Remove(monitoringPoint);
            await _context.SaveChangesAsync();

            return monitoringPoint;
        }

        private bool MonitoringPointExists(int id)
        {
            return _context.MonitoringPoints.Any(e => e.id == id);
        }
    }
}
