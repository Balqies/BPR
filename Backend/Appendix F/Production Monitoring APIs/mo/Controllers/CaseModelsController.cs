using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using mo.Models.MobileDesign;

namespace mo.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class CaseModelsController : ControllerBase
    {
        private readonly CaseModelDbContext _context;

        public CaseModelsController(CaseModelDbContext context)
        {
            _context = context;
        }

        // GET: api/CaseModels
        [HttpGet]
        public async Task<ActionResult<IEnumerable<CaseModel>>> GetCaseModels()
        {
            return await _context.CaseModels.ToListAsync();
        }

        // GET: api/CaseModels/5
        [HttpGet("{id}")]
        public async Task<ActionResult<CaseModel>> GetCaseModel(int id)
        {
            var caseModel = await _context.CaseModels.FindAsync(id);

            if (caseModel == null)
            {
                return NotFound();
            }

            return caseModel;
        }

        // PUT: api/CaseModels/5
        // To protect from overposting attacks, enable the specific properties you want to bind to, for
        // more details, see https://go.microsoft.com/fwlink/?linkid=2123754.
        [HttpPut("{id}")]
        public async Task<IActionResult> PutCaseModel(int id, CaseModel caseModel)
        {
            if (id != caseModel.id)
            {
                return BadRequest();
            }

            _context.Entry(caseModel).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!CaseModelExists(id))
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

        // POST: api/CaseModels
        // To protect from overposting attacks, enable the specific properties you want to bind to, for
        // more details, see https://go.microsoft.com/fwlink/?linkid=2123754.
        [HttpPost]
        public async Task<ActionResult<CaseModel>> PostCaseModel(CaseModel caseModel)
        {
            _context.CaseModels.Add(caseModel);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetCaseModel", new { id = caseModel.id }, caseModel);
        }

        // DELETE: api/CaseModels/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<CaseModel>> DeleteCaseModel(int id)
        {
            var caseModel = await _context.CaseModels.FindAsync(id);
            if (caseModel == null)
            {
                return NotFound();
            }

            _context.CaseModels.Remove(caseModel);
            await _context.SaveChangesAsync();

            return caseModel;
        }

        private bool CaseModelExists(int id)
        {
            return _context.CaseModels.Any(e => e.id == id);
        }
    }
}
