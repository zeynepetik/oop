#ifndef CELL_H
#define CELL_H
#include <iostream>
#include <string>

using namespace std;

class Cell {
public:
	Cell(string c="");
	void setData(string c);
	string getData()const;
	bool isFormula();
	void setIsFormula(bool isform);
private:
	string content;
	bool isFormul;
};
#endif
