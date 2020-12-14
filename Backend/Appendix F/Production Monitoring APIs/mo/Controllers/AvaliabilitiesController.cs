using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using mo.Models.Avaliability;

namespace mo.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class AvaliabilitiesController : ControllerBase
    {
        private readonly AvaliabilityDbContext _context;

        public AvaliabilitiesController(AvaliabilityDbContext context)
        {
            _context = context;
        }

        // GET: api/Avaliabilities
        [HttpGet]
        public async Task<ActionResult<IEnumerable<Avaliability>>> GetAvaliabilitys()
        {
            return await _context.Avaliabilitys.ToListAsync();
        }

        // GET: api/Avaliabilities/5
        [HttpGet("{id}")]
        public async Task<ActionResult<Avaliability>> GetAvaliability(int id)
        {
            var avaliability = await _context.Avaliabilitys.FindAsync(id);

            if (avaliability == null)
            {
                return NotFound();
            }

            return avaliability;
        }

        // PUT: api/Avaliabilities/5
        // To protect from overposting attacks, enable the specific properties you want to bind to, for
        // more details, see https://go.microsoft.com/fwlink/?linkid=2123754.
        [HttpPut("{id}")]
        public async Task<IActionResult> PutAvaliability(int id, Avaliability avaliability)
        {
            if (id != avaliability.id)
            {
                return BadRequest();
            }

            _context.Entry(avaliability).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!AvaliabilityExists(id))
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

        // POST: api/Avaliabilities
        // To protect from overposting attacks, enable the specific properties you want to bind to, for
        // more details, see https://go.microsoft.com/fwlink/?linkid=2123754.
        [HttpPost]
        public async Task<ActionResult<Avaliability>> PostAvaliability(Avaliability avaliability)
        {
            _context.Avaliabilitys.Add(avaliability);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetAvaliability", new { id = avaliability.id }, avaliability);
        }

        // DELETE: api/Avaliabilities/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<Avaliability>> DeleteAvaliability(int id)
        {
            var avaliability = await _context.Avaliabilitys.FindAsync(id);
            if (avaliability == null)
            {
                return NotFound();
            }

            _context.Avaliabilitys.Remove(avaliability);
            await _context.SaveChangesAsync();

            return avaliability;
        }

        private bool AvaliabilityExists(int id)
        {
            return _context.Avaliabilitys.Any(e => e.id == id);
        }
    }
}
