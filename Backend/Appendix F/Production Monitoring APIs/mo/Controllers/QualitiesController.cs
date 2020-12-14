using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using mo.Models.Quality;

namespace mo.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class QualitiesController : ControllerBase
    {
        private readonly QualityDbContext _context;

        public QualitiesController(QualityDbContext context)
        {
            _context = context;
        }

        // GET: api/Qualities
        [HttpGet]
        public async Task<ActionResult<IEnumerable<Quality>>> GetQuality()
        {
            return await _context.Quality.ToListAsync();
        }

        // GET: api/Qualities/5
        [HttpGet("{id}")]
        public async Task<ActionResult<Quality>> GetQuality(int id)
        {
            var quality = await _context.Quality.FindAsync(id);

            if (quality == null)
            {
                return NotFound();
            }

            return quality;
        }

        // PUT: api/Qualities/5
        // To protect from overposting attacks, enable the specific properties you want to bind to, for
        // more details, see https://go.microsoft.com/fwlink/?linkid=2123754.
        [HttpPut("{id}")]
        public async Task<IActionResult> PutQuality(int id, Quality quality)
        {
            if (id != quality.id)
            {
                return BadRequest();
            }

            _context.Entry(quality).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!QualityExists(id))
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

        // POST: api/Qualities
        // To protect from overposting attacks, enable the specific properties you want to bind to, for
        // more details, see https://go.microsoft.com/fwlink/?linkid=2123754.
        [HttpPost]
        public async Task<ActionResult<Quality>> PostQuality(Quality quality)
        {
            _context.Quality.Add(quality);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetQuality", new { id = quality.id }, quality);
        }

        // DELETE: api/Qualities/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<Quality>> DeleteQuality(int id)
        {
            var quality = await _context.Quality.FindAsync(id);
            if (quality == null)
            {
                return NotFound();
            }

            _context.Quality.Remove(quality);
            await _context.SaveChangesAsync();

            return quality;
        }

        private bool QualityExists(int id)
        {
            return _context.Quality.Any(e => e.id == id);
        }
    }
}
