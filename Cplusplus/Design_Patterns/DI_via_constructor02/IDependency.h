#pragma once

// public header, abstract base class to be implemented
class IDependency {
public:
	virtual ~IDependency() = default;
	virtual void printit() = 0;
};

/* NOTE:  - naming convevtion make- get- use-
*
* std::unique_ptr<IFoo> makeFoo();	- passes ownership to the caller;
*					  unique_ptr is later moved to the object, which ends up owning it
* std::shared_ptr<IFoo> getFoo();	- get an object that other objects might hold a reference to
* IFoo& useFoo();			- if there already exists an IFoo object which is owned by someone else,
*					  with the guarantee that it will outlive the caller
*/

std::unique_ptr<IDependency> makeImpl1();
std::unique_ptr<IDependency> makeImpl2();

std::shared_ptr<IDependency> getImpl1();
std::shared_ptr<IDependency> getImpl2();

