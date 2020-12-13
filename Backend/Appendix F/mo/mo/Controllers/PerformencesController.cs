using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using mo.Models.Performence;

namespace mo.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class PerformencesController : ControllerBase
    {
        private readonly PerformenceDbContext _context;

        public PerformencesController(PerformenceDbContext context)
        {
            _context = context;
        }

        // GET: api/Performences
        [HttpGet]
        public async Task<ActionResult<IEnumerable<Performence>>> GetPerformence()
        {
            return await _context.Performence.ToListAsync();
        }

        // GET: api/Performences/5
        [HttpGet("{id}")]
        public async Task<ActionResult<Performence>> GetPerformence(int id)
        {
            var performence = await _context.Performence.FindAsync(id);

            if (performence == null)
            {
                return NotFound();
            }

            return performence;
        }

        // PUT: api/Performences/5
        // To protect from overposting attacks, enable the specific properties you want to bind to, for
        // more details, see https://go.microsoft.com/fwlink/?linkid=2123754.
        [HttpPut("{id}")]
        public async Task<IActionResult> PutPerformence(int id, Performence performence)
        {
            if (id != performence.id)
            {
                return BadRequest();
            }

            _context.Entry(performence).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!PerformenceExists(id))
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

        // POST: api/Performences
        // To protect from overposting attacks, enable the specific properties you want to bind to, for
        // more details, see https://go.microsoft.com/fwlink/?linkid=2123754.
        [HttpPost]
        public async Task<ActionResult<Performence>> PostPerformence(Performence performence)
        {
            _context.Performence.Add(performence);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetPerformence", new { id = performence.id }, performence);
        }

        // DELETE: api/Performences/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<Performence>> DeletePerformence(int id)
        {
            var performence = await _context.Performence.FindAsync(id);
            if (performence == null)
            {
                return NotFound();
            }

            _context.Performence.Remove(performence);
            await _context.SaveChangesAsync();

            return performence;
        }

        private bool PerformenceExists(int id)
        {
            return _context.Performence.Any(e => e.id == id);
        }
    }
}
