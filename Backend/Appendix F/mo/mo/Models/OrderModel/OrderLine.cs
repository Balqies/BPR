using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace mo.Models.OrderModel
{
    public class OrderLine
    {
        public int id { get; set; }

        public int caseModelId { get; set; }

        public int mobileTypeId { get; set; }

        public int amount { get; set; }
    }
}
