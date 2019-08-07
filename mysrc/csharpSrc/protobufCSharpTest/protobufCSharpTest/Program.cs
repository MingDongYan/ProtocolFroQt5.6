using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.Serialization.Formatters.Binary;
using Google.Protobuf;
using Tutorial;
namespace protobufCSharpTest
{
    class Program
    {
        static void Main(string[] args)
        {
            /* Person john = new Person
             {
                 Id = 1234,
                 Name = "John Doe",
                 Email = "jdoe@example.com",
                 Phones = { new Person.Types.PhoneNumber { Number = "555-4321", Type = Person.Types.PhoneType.Home } }
             };

             using (var output = File.Create("john.dat"))
             {
                 john.WriteTo(output);
             }*/
            /*Person john = new Person();
            using (var input = File.OpenRead("john.dat"))
            {
                john = Person.Parser.ParseFrom(input);
                Console.WriteLine("Name:" + john.Name);
                Console.WriteLine("Email:" + john.Email);
            }*/
            /*PetrolActBook bk = new PetrolActBook();

            Act_And_Petrol_Station_Data john = new Act_And_Petrol_Station_Data
            {
                ActId = 1234,
                PetrolStationNo = 12
            };
            bk.ActAndPetrolStationData.Add(john);
            using (var output = File.Create("john2.xml"))
            {
                bk.WriteTo(output);
            }*/

            PetrolActBook bk2 = new PetrolActBook();
            using (var input = File.OpenRead("test.binary"))
            {
                bk2 = PetrolActBook.Parser.ParseFrom(input);
                foreach (Act_And_Petrol_Station_Data data in bk2.ActAndPetrolStationData)
                {
                    Console.WriteLine("ActId:" + data.ActId);
                    Console.WriteLine("Petrol No:" + data.PetrolStationNo);
                }
            }
        }
    }
}
