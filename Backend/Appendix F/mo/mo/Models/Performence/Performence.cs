using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace mo.Models.Performence
{
    public class Performence
    {
        public int id { get; set; }
        public int monitoringPointId { get; set; }
        public int actualOutput { get; set; }
        public int thereticalOutput { get; set; }
        public DateTime date { get; set; }
    }
}
