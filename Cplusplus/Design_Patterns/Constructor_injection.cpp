// Dependency injection via constructor injection
// https://stackoverflow.com/questions/39267388/best-practices-for-dependency-injection-via-constructor
// Destruction order: 
//			A/B -> Dependency (last)

#define DISALLOW_COPY_AND_ASSIGN(Class) \
  Class(const Class &) = delete;        \
  Class & operator=(const Class &) = delete


class Dependency {
public:
	Dependency(int n) : num(n) {}
	int operator()(int arr_num) const { return num + arr_num; }

	int num = 0;
};


// No 1. Save the reference to dependent class 
class A {
public:
	A(const Dependency & thing) : m_thing(thing) {}
	// A(const Dependency &&) = delete;   // no binding to temporary objects (callables)
										  // or make 'Dependency & m_thing' nonconst

	DISALLOW_COPY_AND_ASSIGN(A);  // reference cannot be copied
	void printit() { std::cout << "From A class " << m_thing.num << std::endl; }

protected:
	const Dependency & m_thing;
};

// No 2. Save raw pointer to dependent class 
class B {
public:
	B(Dependency * d) : m_thing(d) {
		if (d == nullptr)
			throw std::exception("null dependency");
	}
	void printit() { std::cout << "From B class " << m_thing->num << std::endl; }

protected:
	Dependency * m_thing;
};

// No 3. Save smart pointer to dependent class 
class C {
public:
	C(std::shared_ptr<Dependency> d) : m_thing(d) {
		if (!d)
			throw std::exception("null dependency");
	}
	void printit() { std::cout << "From C class " << m_thing->num << std::endl; }

private:
	std::shared_ptr<Dependency> m_thing;
};


int main()
{
	Dependency myDependency(5);
	A myA01(myDependency);
	myA01.printit();

	A myA02(myDependency(20));   // only with const ref
	myA02.printit();

	A myA03(myDependency(100));  // only with const ref
	myA03.printit();

	B myB(&myDependency);
	myB.printit();

	C myC(std::make_shared<Dependency>(55));
	myC.printit();


	std::cin.get();
}

/* OUTPUT
From A class 5
From A class 25
From A class 105
From B class 5
From C class 55
*/
