#include <iostream>
#include "cell.h"

using namespace std;
namespace CellSpace{
    IntValueCell::IntValueCell(int val):content(val){}
    string IntValueCell::getData()const{
    	return to_string(content);
    }
    void IntValueCell::setData(const string& input){
    	content=stoi(input);
    }

    DoubleValueCell::DoubleValueCell(double val){
    	content=val;
    }
    string DoubleValueCell::getData() const{
    	return to_string(content);
    }
    void DoubleValueCell::setData(const string& input){
    	content=stod(input);
    }

    StringValueCell::StringValueCell(const string& val):content(val){
    }
    string StringValueCell::getData()const{
    	return content;
    }
    void StringValueCell::setData(const string& input){
    	content=input;
    }

    FormulaCell::FormulaCell(const string& form):content(form){
    }
    string FormulaCell::getData() const{
    	return content;
    }
    void FormulaCell::setData(const string& input){
    	content=input;
    }


}
