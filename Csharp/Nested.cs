using System;
using System.Runtime.InteropServices;


namespace CSharpApp
{
    // use a static class for 'globals'
    public static class MyGlobals
    {
        public static int glob; 
    }
    class Outer
    {
        private int d_value = 0;
        private static int s_value; 
        private class PrivateInner
        {
            private int d_privateInner;
		    public PrivateInner() 
            {
                d_privateInner = 55;
            }
            public void privateInnerFunc() { Console.WriteLine("PrivateInner::privateInnerFunc()"); }
        }
        public class Inner01
        {
            private void mutateOuter(ref Outer oc)
            {
                oc.d_value++;
            }
        }
        public class Inner02
        {
            internal int innerField;    // use internal instead of private
                                        // acsess level compares with 'friend' class in C++
            public Inner02()
            {
                innerField = 22;
                Console.WriteLine("Created Inner02 Object");
            }
            public void setOuter(ref Outer oc, int i)
            {
                Outer.s_value = i;
                Console.WriteLine($"Outer's s_value: { Outer.s_value }");

                oc.d_value = i;
                Console.WriteLine($"Outer's d_value: { oc.d_value }");

                MyGlobals.glob = i;
                Console.WriteLine($"Global's s_value: { MyGlobals.glob }");
            }
            Inner01 in1 = new Inner01();    // Outer::Inner02 can access Outer::Inner01
            PrivateInner privateInnerObj = new PrivateInner();  // Outer::Inner02 can access public fields Outer::PrivateInner
        }

        PrivateInner privateInnerObj = new PrivateInner();  // Outer creates object of PrivateInner
        public void caller()
        {
            privateInnerObj.privateInnerFunc();
        }
        public static Inner01 getInner() { return new Inner01(); }  // Outer class can use Inner as 'return' and 'args'
        public int getInnerPrivate(ref Inner02 ic)
        {
            return ic.innerField;
        }
    }

    class Demo
    {
        static void Main(string[] args)
        {
            Outer outer = new Outer();
            Outer.Inner02 inner2 = new Outer.Inner02();

            inner2.setOuter(ref outer, 10);		// pass reference to Outer

            outer.caller();

            Outer.Inner01 inner1 = Outer.getInner();

            var a = outer.getInnerPrivate(ref inner2);
            Console.WriteLine($"Inner's member: { a }");


            Console.Read();
        }
    }
}
