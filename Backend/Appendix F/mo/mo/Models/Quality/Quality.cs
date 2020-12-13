using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace mo.Models.Quality
{
    public class Quality
    {
        public int id { get; set; }
        public int monitoringPointId { get; set; }
        public int goodProduct { get; set; }
        public int totalProduct { get; set; }
        public DateTime date { get; set; }
    }
}
