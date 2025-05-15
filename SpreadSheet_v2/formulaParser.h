#ifndef FORMULAPARSER_H
#define FORMULAPARSER_H
#include <iostream>
#include <string>
class SpreadSheet;

using namespace std;
//to store row and column together
struct CellIndex{
	int row,col;
};

class FormulaParser{
public:
	//parse and calculate the formula
	double parseFormula(const string& Formula, const SpreadSheet& sheet)const;
	double sum(const string& range, const SpreadSheet& sheet)const;
	double average(const string& range, const SpreadSheet& sheet)const;
	double stddev(const string& range, const SpreadSheet& sheet)const;
	double max(const string& range, const SpreadSheet& sheet)const;
	double min(const string& range, const SpreadSheet& sheet)const;

private:
	/*calculates range's start and end cells*/
	void parseRange(const string& range, CellIndex& start, CellIndex& end)const;
	/*converts cell id into row and col*/
	CellIndex getCellLocation(const string& cellID)const;
	string getCellID(int r, int c)const;

};
#endif
