    using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace mo.Models.OrderModel
{
    public class Order
    {
        public int id { get; set; }
        public int customerId { get; set; }

        public DateTime date { get; set; }
    }
}
