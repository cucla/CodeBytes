using System;

namespace Delegate
{
    // DECLARE THE DELEGATE TYPE
    public delegate String someDelegate(double a, double b);

    class SomeClass
    {
        public String foo(double a, double b)
        {
            String result = (a * b).ToString();
            Console.WriteLine("Result: " + result);
            return result;
        }
    }

    class Program
    {
        static String bar(double a, double b)
        {
            String result = (a + b).ToString();
            Console.WriteLine("Result: " + result);
            return result;
        }
        static String baz(double a, double b)
        {
            String result = (a - b).ToString();
            Console.WriteLine("Result: " + result);
            return result;
        }

        static void Main()
        {
            double a = 10, b = 2.5;
            someDelegate d1 = bar;      // DELEGATE CHAIN
            someDelegate d2 = baz;
            someDelegate dd = d1 + d2;

            SomeClass obj = new SomeClass();
            someDelegate d3 = obj.foo;
            dd += d3;
            dd(a, b);       // or someDelegate d = bar; ... d = baz; ... d = obj.foo;

            someDelegate d = delegate (double xa, double xb)   // ANONYMOUS DELEGATES
            {
                return (xa * xb).ToString();
            };
            Console.WriteLine("Result: " + d(a, b));           // Result: 25

           
            Console.Read();
        }
    }
}

/*
 * Result: 12.5
 * Result: 7.5
 * Result: 25
 * Result: 25
 */
