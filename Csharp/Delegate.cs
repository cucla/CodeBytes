using System;

namespace Delegate
{
    // DECLARE THE DELEGATE TYPE
    public delegate String someDelegate(double a, double b);

    class SomeClass
    {
        public String foo(double a, double b)
        {
            return Math.Pow(a, b).ToString();
        }
    }

    class Program
    {
        static String bar(double a, double b)
        {
            return (a + b).ToString();
        }
        static String baz(double a, double b)
        {
            return (a - b).ToString();
        }

        static void Main()
        {
            someDelegate d = bar;
            Console.WriteLine("Result: " + d(10, 2.5));           // Result: 12.5
            d = baz;
            Console.WriteLine("Result: " + d(10, 2.5));           // Result: 7.5

            d = delegate (double a, double b)   // ANONYMOUS DELEGATE
            {
                return (a * b).ToString();
            };
            Console.WriteLine("Result: " + d(10, 2.5));           // Result: 25

            SomeClass obj = new SomeClass();
            d = obj.foo;             // BOUND TO CLASS INSTANCE
            Console.WriteLine("Result: " + d(10, 2.5));           // Result: 316.227766016838


            Console.Read();
        }
    }
}
