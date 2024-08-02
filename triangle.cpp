#include <iostream>
#include "triangle.h"

using namespace std;

int main() {
	float a, b, c;
	printf("Enter the values for the triangle respectively a,b,c\n");
	cin >> a >> b >> c;
	Triangle triangle1(a, b, c);
	/*Triangle tri2 = {a,b,c};//another way to call constructor
	Triangle tri3 = triangle1;//another way of copy constructor*/
	triangle1.triangleType();
	cout << "Area of triangle 1: " << triangle1.Area() << endl;
	cout << "Sides of tri1" << endl;
	cout << "Side A: " << triangle1.getSideA() << endl;
	cout << "Side B: " << triangle1.getSideB() << endl;
	cout << "Side C: " << triangle1.getSideC() << endl;
	Triangle tri2(a,b,c);
	tri2.setValue(2, 7, 8);
	tri2.triangleType();
	cout << "Area of triangle 2: " << tri2.Area() << endl;
	cout << "Sides of tri1" << endl;
	cout << "Side A: " << tri2.getSideA() << endl;
	cout << "Side B: " << tri2.getSideB() << endl;
	cout << "Side C: " << tri2.getSideC() << endl;
	/*
	cout << "Sides of tri2" << endl;
	tri2.setValue(1, 2, 3);
	cout << "Side A: " << tri2.getSideA() << endl;
	cout << "Side B: " << tri2.getSideB() << endl;
	cout << "Side C: " << tri2.getSideC() << endl;
	*/
}