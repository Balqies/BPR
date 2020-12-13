using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace mo.Models
{
    public class Customer
    {
        public int id { get; set; }
        public string firstName { get; set; }
        public string lastName { get; set; }
        public string email { get; set; }
        public int mobile { get; set; }
        public string city { get; set; }
        public DateTime dateOfCreation { get; set; }
    }
}
