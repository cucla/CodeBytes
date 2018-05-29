#include "stdafx.h"
#include <iostream>
#include <string>


// Setter Injection
// http://www.bogotobogo.com/DesignPatterns/Dependency_Injection_Design_Pattern_Inversion_Of_Control_IoC.php

class Shape {
public:
	virtual void draw() = 0;
};

class Circle : public Shape {
public:
	void draw() { std::cout << "circle\n"; }
};

class Triangle : public Shape {
public:
	void draw() { std::cout << "triangle\n"; }
};


class Drawing {
public:
	void drawShape(Shape * pShape) {
		pShape->draw();
	}

private:
	Shape * pShape;
};


class IDrawing {
public:
	IDrawing() { d = new Drawing; }
	void draw(std::string s) {
		if (s == "triangle")
			d->drawShape(new Triangle);
		else if (s == "circle")
			d->drawShape(new Circle);
		else
			std::cout << " Need shape";
	}

private:
	Drawing * d;
};


int main()
{
	IDrawing myDrawing;
	myDrawing.draw("circle");


	std::cin.get();
}

