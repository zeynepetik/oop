#include <iostream>

using namespace std;

class Complex {
	int real, image;
public:
	Complex(int r = 0, int i = 0);
	~Complex();
	Complex(const Complex& oth);
	int getReal()const;
	int getImage()const;
	void setValue(int r = 0, int i = 0);
	Complex addComplex(const Complex& oth);
	Complex multiplyComplex(const Complex& oth);
	Complex substractComplex(Complex& oth);
	Complex multiplyConstant(int constant);
	void multiplyMinus();
	void displayComplex();
};

Complex::Complex(int r, int i) {
	cout << "Complex number created" << endl;
	real = r;
	image=i;
}

Complex::~Complex() {
	cout << "Destructor worked" << endl;
}

Complex::Complex(const Complex& oth) {
	cout << "Copy constructor worked" << endl;
	real = oth.real;
	image = oth.image;
}

int Complex::getReal() const {
	return real;
}

int Complex::getImage() const {
	return image;
}

void Complex::setValue(int r, int i) {
	real = r;
	image = i;
}

void Complex::displayComplex() {
	/*if (image >= 0) {
		cout << real << "+" << image << "i" << endl;
	}
	else {
		cout << real << image << "i" << endl;
	}*/
	image>=0 ? cout<<real<<"+"<<image<<"i"<<endl : cout<<real<<image<<"i"<<endl;
	// ?nden öncesi True dönerse : iþaretinin ön kýsmý false dönerse son kýsmý çalýþýyor.
}

Complex Complex:: addComplex(const Complex& oth) {
	Complex result;
	result.image = image + oth.image;
	result.real = real + oth.real;
	return result;
}

Complex Complex::multiplyComplex(const Complex& oth) {
	Complex result;
	result.image = image * (oth.image);
	result.real = real * (oth.real);
	return result;
}

Complex Complex::multiplyConstant(int constant) {
	Complex result;
	result.image = image * constant;
	result.real = real * constant;
	return result;
}

Complex Complex::substractComplex(Complex& oth) {
	Complex result;
	result.real = real - oth.real;
	result.image = image - oth.image;
	return result;
}
/*
void Complex::multiplyMinus() {

}*/