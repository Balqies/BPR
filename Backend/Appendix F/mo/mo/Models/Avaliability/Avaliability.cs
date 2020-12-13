using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace mo.Models.Avaliability
{
    public class Avaliability
    {
        public int id { get; set; }
        public int monitoringPointId { get; set; }
        public int planedProductionTime { get; set; }
        public int runningTime { get; set; }
        public DateTime date { get; set; }
    }
}
