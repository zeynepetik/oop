#include "spreadSheet.h"
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <memory>
#include <iomanip> // getCellValue fonksiyonunda kullanılan setprecision için gerekli 
#include <vector> //getfromfile da vektör kullandığım için
#include "formulaParser.h"

using namespace CellSpace;
using namespace std;
SpreadSheet::SpreadSheet(int r, int c) : row(r > 0 ? r : 10), col(c > 0 ? c : 10), parser() {
    initializeCells(row, col);
}

void SpreadSheet::initializeCells(int rows, int cols) {
    cells = make_unique<unique_ptr<unique_ptr<Cell>[]>[]>(rows);
    for (int i = 0; i < rows; ++i) {
        cells[i] = make_unique<unique_ptr<Cell>[]>(cols);
        for (int j = 0; j < cols; ++j) {
            cells[i][j] = make_unique<StringValueCell>(""); // Varsayılan olarak StringValueCell.
        }
    }
}

int SpreadSheet::getRow() const {
    return row;
}

int SpreadSheet::getCol() const {
    return col;
}

string SpreadSheet::getCellValue(int r, int c) const {
    if (r < 0 || c < 0 || r >= row || c >= col) {
        throw out_of_range("Invalid cell position");
    }
    //unique_ptr ile dynamic_cast yapılamayacağı için raw ptr ile yapıyor 
    auto * isformula= dynamic_cast<FormulaCell*>(cells[r][c].get());
    if (isformula) {
        double result=parser.parseFormula(isformula->getData(), *this);
        ostringstream stream;
        stream<<fixed<<setprecision(2)<<result;
        return stream.str();
    }
    auto * isdouble= dynamic_cast<DoubleValueCell*>(cells[r][c].get());
    if (isdouble) {
        double result=stod(isdouble->getData());
        ostringstream stream;
        stream<<fixed<<setprecision(2)<<result;
        return stream.str();
    }
    return cells[r][c]->getData();
}

void SpreadSheet::setCellValue(int r, int c, const string& input) {
    if (input.empty()) {
        cells[r][c] =make_unique<StringValueCell>("");
    }
    if (r >= row || c >= col) {
        initializeCells(max(r + 1, row), max(c + 1, col));
    }

    // Girilen veriye göre doğru hücre türünü seç:
    if (input[0] == '=') {
        cells[r][c] = make_unique<FormulaCell>(input);
    } else {
        try {
            double num = stod(input);
            if (input.find('.') !=string::npos) {
                cells[r][c] = make_unique<DoubleValueCell>(num);
            } else {
                cells[r][c] = make_unique<IntValueCell>(static_cast<int>(num));
            }
        } catch (const exception& e) {
            cells[r][c] =make_unique<StringValueCell>(input);
        }
    }
}


string SpreadSheet::getCellReference(int r, int c) const {
    if (r < 0 || c < 0)
        throw out_of_range("Invalid column or row values");
    char colLetter = 'A' + c;
    return string(1, colLetter) + to_string(r + 1);
}

int SpreadSheet::getRowIndex(const string& cellID) const {
    return stoi(cellID.substr(1)) - 1;
}

int SpreadSheet::getColIndex(const string& cellID) const {
    return cellID[0] - 'A';
}

void SpreadSheet::saveToFile(const string& file) const {
    ofstream outFile(file);
    if (!outFile.is_open()) {
        throw ios_base::failure("File could not be opened");
    }
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            //controlling if object is in the DoubleValueCell class
            auto * isdouble= dynamic_cast<DoubleValueCell*>(cells[i][j].get());
            if (isdouble) {
            	double result=stod(isdouble->getData());
        	ostringstream stream;
        	stream<<fixed<<setprecision(2)<<result;
        	outFile<<stream.str();
    	    }else{
    	    	outFile << (cells[i][j]->getData());
    	    }
            if (j < col - 1) {
                outFile << ",";
            }
        }
        outFile << "\n";
    }
    outFile.close();
}

void SpreadSheet::getFromFile(const string& file) {
    ifstream inFile(file);
    if (!inFile.is_open()) {
        throw ios_base::failure("File could not be opened");
    }

    string line;
    vector<vector<string>> tempCell;
    int maxColCount = 0;

    // Dosyayı satır satır oku
    while (getline(inFile, line)) {
        vector<string> row;
        string cellContent;

        for (char ch : line) {
            if (ch == ',') {
                row.push_back(cellContent); // Hücreyi satıra ekle
                cellContent.clear();
            } else {
                cellContent += ch;
            }
        }
        // Satırın son hücresini ekle
        row.push_back(cellContent);

        maxColCount = max(maxColCount, static_cast<int>(row.size()));
        tempCell.push_back(row);
    }

    inFile.close();

    // SpreadSheet'i güncelle
    int newRow = tempCell.size();
    int newCol = maxColCount;

    // Mevcut hücreleri sıfırla ve yeni boyuta göre ayarla
    initializeCells(newRow, newCol);
    row = newRow;
    col = newCol;

    // Hücreleri doldur
    for (int r = 0; r < newRow; ++r) {
        for (int c = 0; c < newCol; ++c) {
            if (c < tempCell[r].size()) {
                setCellValue(r, c, tempCell[r][c]); // Gerçek veri
            } else {
                setCellValue(r, c, ""); // Eksik hücreler için varsayılan değer
            }
        }
    }
}

void SpreadSheet::display(AnsiTerminal &terminal, int currRow, int currCol) const {
    terminal.clearScreen();
    terminal.printAt(2, 1, "Arrow Keys: Navigate | Enter: E | 's': Save | 'l': Load | 'Q': Quit");
    string cellReference = getCellReference(currRow, currCol);
    string cellValue = getCellValue(currRow, currCol);
    terminal.printInvertedAt(3, 1, "Selected Cell: " + cellReference + " = " + cells[currRow][currCol]->getData());

    terminal.printAt(5, 5, " ");
    for (int c = 0; c < col; ++c) {
        char colHeader = 'A' + c;
        terminal.printInvertedAt(5, c * 10 + 10, string(1, colHeader));
    }

    for (int r = 0; r < row; ++r) {
        terminal.printInvertedAt(6 + r, 2, to_string(r + 1));
        for (int c = 0; c < col; ++c) {
            string cellValue = getCellValue(r, c);
            if (r == currRow && c == currCol) {
                terminal.printInvertedAt(6 + r, c * 10 + 10, cellValue.empty() ? " " : cellValue);
            } else {
                terminal.printAt(6 + r, c * 10 + 10, cellValue.empty() ? "." : cellValue);
            }
        }
    }
}

