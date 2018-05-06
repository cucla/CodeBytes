using System;

namespace Delegate
{
    // DECLARE THE DELEGATE TYPE
    public delegate string MyDelegate(int arg1, int arg2);

    class MyClass
    {
        public string instanceMethod1(int arg1, int arg2)
        {
            return ((arg1 + arg2) * arg1).ToString();
        }
    }

    class Program
    {
        static string func1(int a, int b)
        {
            return (a + b).ToString();
        }
        static string func2(int a, int b)
        {
            return (a * b).ToString();
        }

        static void Main(string[] args)
        {
            MyDelegate f = func1;
            Console.WriteLine("The number is: " + f(10, 20));           // The number is: 30 
            f = func2;
            Console.WriteLine("The number is: " + f(10, 20));           // The number is: 200

            f = delegate (int arg1, int arg2)   // ANONYMOUS DELEGATES
            {
            return (arg1 - arg2).ToString();
            };
            Console.WriteLine("The number is: " + f(10, 20));           // The number is: -10
            
            MyClass mc = new MyClass();
            f = mc.instanceMethod1;             // BOUND TO CLASS INSTANCE
            Console.WriteLine("The number is: " + f(10, 20));           // The number is: 300


            Console.WriteLine("\nPress Enter Key to Continue...");
            Console.ReadLine();
        }
    }
}
