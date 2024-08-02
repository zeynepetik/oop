#include <iostream>
using namespace std;
class Triangle {

	float sideA, sideB, sideC;

public:
	Triangle(float a,float b,float c);
	~Triangle();
	Triangle(const Triangle &oth);
	bool isTriangle(float a, float b, float c);
	float getSideA() const {
		return sideA;
	};
	float getSideB() const {
		return sideB;
	};
	float getSideC() const {
		return sideC;
	};
	//const at the end guarantees that calling this function won't change the state of the object.
	void setValue(float a, float b, float c);
	bool isEquilateral();
	bool isScalene();
	bool isIsosceles();
	void triangleType();
	float Area();
};

Triangle::Triangle(float a, float b, float c) {
	while (isTriangle(a, b, c) == false) {
		cout << "Enter valid value" << endl;
		cin >> a >> b >> c;
	}
	sideA = a;
	sideB = b;
	sideC = c;
	cout << "Triangle is created" << endl;
}



Triangle::~Triangle() {
	cout << "Triangle is destroyed" << endl;
}

Triangle:: Triangle(const Triangle &oth){
	sideA = oth.sideA;
	sideB = oth.sideB;
	sideC = oth.sideC;
	cout << "Object is copied" << endl;
}

bool Triangle::isTriangle(float a, float b, float c) {
	float side1, side2, side3;
	side1 = a - b;
	if (side1 < 0) {
		side1 = side1 * (-1);
	}
	side2 = a - c;
	if (side2 < 0) {
		side2 = side2 * (-1);
	}
	side3 = c - b;
	if (side3 < 0) {
		side3 = side3 * (-1);
	}
	if (!(side1<c && c<a+b)) {
		cout << "invalid C value" << endl;
		return false;
	}
	if (!(side2 < b && b < a + c)) {
		cout << "invalid B value" << endl;
		return false;
	}
	if (!(side3 < a && a < c + b)) {
		cout << "invalid A value" << endl;
		return false;
	}
	return true;
}

void Triangle::setValue(float a, float b, float c) {
	while (isTriangle(a, b, c) == false) {
		cout << "Enter valid value" << endl;
		cin >> a >> b >> c;
	}
	sideA = a;
	sideB = b;
	sideC = c;
	cout << "Triangle is created" << endl;
}

bool Triangle::isEquilateral() {
	if (sideA == sideB && sideB == sideC) {
		return true;
	}
	return false;
}

bool Triangle::isScalene() {
	if (!isIsosceles()) {
		return true;
	}
}

bool Triangle::isIsosceles() {
	if (isEquilateral())return true;
	else{
		if(sideA==sideB || sideA==sideC || sideB==sideC)
		return true;
	}	
	return false;
}

void Triangle::triangleType() {
	if (isEquilateral()) {
		cout << "This is an equilateral triangle" << endl;
	}
	else if (isIsosceles()) {//if you write just if then it will print both eq. tri. and isc. tri so use else if
		cout << "This is an isosceles triangle" << endl;
	}
	else {
		cout << "This is a scalene triangle" << endl;
	}
}

/*float Triangle::Area() {
	float peri = sideA + sideB + sideC;
	peri = peri / 2;
	return sqrt(peri * (peri - sideA) * (peri - sideB) * (peri - sideC));
}*/

float Triangle::Area() {
	if (isEquilateral()) {
		return sqrt(3) / 4 * sideA * sideA;
	}
	else {
		float peri = sideA + sideB + sideC;
		peri = peri / 2;
		return sqrt(peri * (peri - sideA) * (peri - sideB) * (peri - sideC));
	}

}