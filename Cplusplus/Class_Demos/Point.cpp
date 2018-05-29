#include "stdafx.h"
#include <iostream>
#include <string>


class Object {
protected:
	Object() {}
	virtual ~Object() {}

public:
	virtual bool Equals(const Object & obj) const { return true; }
	virtual std::ostream & ToString(std::ostream & o) const { return o << ""; }
};

class Point: public Object {
public:
	Point(int x, int y) : x(x), y(y) { }
	Point() : Point(0, 0) { }

	bool Equals(const Object & obj) const override;
	std::ostream & ToString(std::ostream & o) const override { 
		return o << "Point(" << x << ", " << y << ")";
	}
protected:
	int x, y;
};

bool Point::Equals(const Object & obj) const {
	auto p = static_cast<const Point &>(obj);
	return (x == p.x) && (y == p.y);
}


class Point3D final : public Point {
public:
	Point3D(int x, int y, int z) : Point(x, y), z(z) {	}

	bool Equals(const Object & obj) const override;
	std::ostream & ToString(std::ostream & o) const override {
		return o << "Point(" << x << ", " << y << ", " << z << ")";
	}
protected:
	int z;
};

bool Point3D::Equals(const Object & obj) const {
	return Point::Equals( static_cast<const Point &>(obj) ) && z == static_cast<const Point3D &>(obj).z;
}

std::ostream & operator<<(std::ostream & o, const Object & obj) { return obj.ToString(o); }


int main() {
	Point point2Da(3, 4);
	Point point2Db;
	Point3D point3Da(2, 3, 4);
	Point3D point3Db(2, 3, 4);

	std::cout << "point2Da: " << point2Da << std::endl;
	std::cout << "point2Db: " << point2Db << std::endl;
	std::cout << "point2Da = point2Db : " << point2Da.Equals(point2Db) << std::endl;
	std::cout << "point3Da: " << point3Da << std::endl;
	std::cout << "point3Db: " << point3Db << std::endl;
	std::cout << "point3Da = point3Db : " << point3Da.Equals(point3Db) << std::endl;
	

	std::cin.get();
}
