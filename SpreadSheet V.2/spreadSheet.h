#ifndef SPREADSHEET_H
#define SPREADSHEET_H

#include <iostream>
#include <string>
#include <memory>
#include <fstream>
#include "cell.h"
#include "formulaParser.h"
#include "AnsiTerminal.h"

using namespace CellSpace;

class SpreadSheet {
public:
    SpreadSheet(int r = 10, int c = 10);
    void setCellValue(int r, int c, const std::string& value);
    std::string getCellValue(int r, int c) const;
    int getRow() const;
    int getCol() const;
    std::string getCellReference(int r, int c) const;
    void saveToFile(const std::string& file) const;
    void getFromFile(const std::string& file);
    int getRowIndex(const std::string& cellID) const;
    int getColIndex(const std::string& cellID) const;
    void display(AnsiTerminal &terminal, int currRow, int currCol) const;

private:
    std::unique_ptr<std::unique_ptr<std::unique_ptr<Cell>[]>[]> cells;
    int row, col;
    void initializeCells(int rows, int cols);
    FormulaParser parser;
};

#endif

