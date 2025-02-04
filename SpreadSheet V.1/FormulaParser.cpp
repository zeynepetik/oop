#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include "formulaParser.h"
#include "spreadSheet.h"

using namespace std;
//getting cell location from its reference
CellIndex FormulaParser::getCellLocation(const string &cellID)const{
    int c=cellID[0]-'A';
    int r=stoi(cellID.substr(1))-1;
    //will return as struct typed CellIndex
    return {r,c};
}
//getting cell reference from its row and column values
string FormulaParser::getCellID(int r, int c)const{
    char colAsLetter='A'+ c;
	string result=string(1,colAsLetter) + to_string(r);
	return result; 
}
//to parse and calculate the given formula
double  FormulaParser::parseFormula(const string &formula, const SpreadSheet &sheet)const{
    if(formula[0]!='=' || formula.empty()){
        return 0.0;
    }
    char op;
    int i=1;
    int size=formula.size();
    string cell1, cell2;//to store cell contents
    if(formula.find("SUM")!=string::npos){//content contain SUM keyword
        string range=formula.substr(5,formula.size()-2);//get range from formula 
        return sum(range, sheet);
    }
    
    if(formula.find("AVER")!=string::npos){
        string range=formula.substr(6,formula.size()-2);//get range from the formula
        return average(range, sheet);
    }
    
    if(formula.find("STDDEV")!=string::npos){
        string range=formula.substr(8,formula.size()-2);//get range from the formula
        return stddev(range, sheet);
    }
    
    if(formula.find("MAX")!=string::npos){
        string range=formula.substr(5,formula.size()-2);//get range from the formula
        return max(range, sheet);
    }
    
    if(formula.find("MIN")!=string::npos){
        string range=formula.substr(5,formula.size()-2);//get range from the formula
        return min(range, sheet);
    }
    //stores first cell's content
    while(i<size && (formula[i]>='A' && formula[i]<='Z') || (formula[i]>='0' && formula[i]<='9')){
    	cell1+=formula[i];
    	i++;
    }
    //stores the operator
    if(formula[i]=='+' ||formula[i]=='*' || formula[i]=='-' || formula[i]=='/'){
    	op=formula[i];
    	i++;
    }
    //stores second cell's contents
    while(i<size && (formula[i]>='A' && formula[i]<='Z') || (formula[i]>='0' && formula[i]<='9')){
    	cell2+=formula[i];
    	i++;
    }
    //converting cell's content into doubles
    double val1=0.0,val2=0.0;
    //if cell's content contain reference
    if(cell1[0]>='A' && cell1[0]<='Z'){
    	int r=getCellLocation(cell1).row;
    	int c=getCellLocation(cell1).col;
    	val1=stod(sheet.getCellValue(r,c));//get cell's numerical value
    }
    else{
    	val1=stod(cell1);//if it is not a reference but a numerical value
    }
    if(cell2[0]>='A' && cell2[0]<='Z'){
    	int r=getCellLocation(cell2).row;
    	int c=getCellLocation(cell2).col;
    	val2=stod(sheet.getCellValue(r,c));
    }
    else{
    	val2=stod(cell2);
    }
    switch(op){
        //according to operator calculate and return results
        case '+': return val1+val2;
        case '-': return val1-val2;
        case '/': return val2!=0 ? val1/val2 : 0.0;
        case '*': return val1*val2;
        default: return 0.0;
    }    
}
//to get range's start and end cells
void FormulaParser::parseRange(const string& range, CellIndex& start, CellIndex& end)const{
    /*finds the index that separates the start and end cells*/
    auto delimiter=range.find("..");
    if(delimiter==string::npos){
    	cout<<"Invalid range check for the .."<<endl;
    	start={0,0};
    	end={0,0};
    	return;
    }
    //getting start and end cell's reference and converting into row and column
    string startcell=range.substr(0,delimiter);//A1
    string endcell=range.substr(delimiter+2);//A10
    start=getCellLocation(startcell);
    end=getCellLocation(endcell);
}
double FormulaParser::sum(const string &range, const SpreadSheet &sheet)const{
    CellIndex start, end;
    parseRange(range,start,end);
    double result=0.0;
    for(int i=start.row;i<=end.row;i++){
        for(int j=start.col;j<=end.col;j++){
            double cell_val=stod(sheet.getCellValue(i,j));//getting contennt
            result+=cell_val;
        }
    }
    return result;
}
double FormulaParser::average(const string &range, const SpreadSheet &sheet)const{
    CellIndex start, end;
    parseRange(range,start,end);
    double result=0.0;
    int count=0;
    for(int i=start.row;i<=end.row;i++){
        for(int j=start.col;j<=end.col;j++){
            double cell_val=stod(sheet.getCellValue(i,j));//getting content
            result+=cell_val;
            count++;
        }
    }
    return result/count;
}
double FormulaParser::stddev(const string &range, const SpreadSheet &sheet)const{
    CellIndex start,end;
    double ave=average(range,sheet);
    parseRange(range,start, end);
    double squareSum=0.0;
    double cellVal;
    int count=0;
    for(int i=start.row;i<=end.row;i++){
        for(int j=start.col;j<=end.col;j++){
            cellVal=stod(sheet.getCellValue(i,j));//getting content
            squareSum+=pow(cellVal-ave,2);
            count++;
        }
    }
    double result=squareSum/count;
    return sqrt(result);
}
double FormulaParser::max(const string &range, const SpreadSheet &sheet)const{
    CellIndex start, end;
    parseRange(range,start,end);
    double max=stod(sheet.getCellValue(start.row,start.col));//start value
    for(int i=start.row;i<=end.row;i++){
        for(int j=start.col;j<=end.col;j++){
            double cell_val=stod(sheet.getCellValue(i,j));//getting content
            if(cell_val>max)max=cell_val;
        }
    }
    return max;
}
double FormulaParser::min(const string &range, const SpreadSheet &sheet)const{
    CellIndex start, end;
    parseRange(range,start,end);
    double min=stod(sheet.getCellValue(start.row,start.col));//start value
    for(int i=start.row;i<=end.row;i++){
        for(int j=start.col;j<=end.col;j++){
            double cell_val=stod(sheet.getCellValue(i,j));//getting content
            if(cell_val<min)min=cell_val;
        }
    }
    return min;
}
