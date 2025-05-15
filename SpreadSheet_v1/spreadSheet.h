#ifndef SPREADSHEET_H
#define SPREADSHEET_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "cell.h"
#include "formulaParser.h"
#include "AnsiTerminal.h"

using namespace std;

class SpreadSheet {
public:
	SpreadSheet(int r=10,int c=10);
	void setCellValue(int r,int c, const string& value);
	string getCellValue(int r,int c)const;	
	int getRow()const;
	int getCol()const;
	void updateCell(const string cellID, const string& newContent);
	void recalculateCell();
	//gets cell ID from row and columns
	string getCellReference(int r, int c)const;
	void saveToFile(const string& file)const;
	void getFromFile(const string& file);
	/*gets row and column from cell ID*/
	int getRowIndex(const string& cellID)const;
	int getColIndex(const string& cellID)const;
	void display(AnsiTerminal &terminal, int currRow, int currCol)const;//gpt used

private:
	vector<vector<Cell>> cells;
	int row,col;
	void updateDependentCells(const string& cellID);
	FormulaParser parser;//got that from gpt couldnt figure out what is the use of formulaParser usage
};
#endif
