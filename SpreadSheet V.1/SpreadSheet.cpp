#include <iostream>
#include <vector>
#include "spreadSheet.h"
#include <fstream>
#include <algorithm>
#include <sstream>

using namespace std;

SpreadSheet::SpreadSheet(int r,int c){
	if(r<=0||c<=0){
		row=10,col=10;
	}
	else{
		row=r; col=c;
	}
	cells.resize(row);
	for(auto& inner_vec : cells){
		inner_vec.resize(col);
	}
}

int SpreadSheet::getRow()const{return row;}

int SpreadSheet::getCol()const{return col;}
//to get cell's content
string SpreadSheet::getCellValue(int r, int c)const{
	if(c<0 || r<0){
		cout<<"Invalid row or column";
		exit(-1);
	}
	string cellVal=cells[r][c].getData();
	if(cellVal[0]!='='){
		return cellVal;
	}
	else{
		double result=parser.parseFormula(cellVal,*this);//if contains formula get the value
		return to_string(static_cast<int>(result));
	}
}
//setting value and if size is not enough resize it
void SpreadSheet::setCellValue(int r, int c, const string& data){
	if(r>row){
		cells.resize(r);
		row=r;
	}
	if(c>col){
		for(int i=0;i<cells.size();i++){
			cells[i].resize(c);
			col=c;
		}
	}
	if(data[0]=='='){
		cells[r][c].setIsFormula(true);
	}
	else if(data[0]!='='){
		cells[r][c].setIsFormula(false);
	}
	cells[r][c].setData(data);
}
//getting row and column values from their cell reference
int SpreadSheet::getRowIndex(const string& cellID)const{
	return stoi(cellID.substr(1))-1;
}
int SpreadSheet::getColIndex(const string& cellID)const{
	return cellID[0]-'A';
	
}
//get cell reference from its row and column values
string SpreadSheet::getCellReference(int r, int c)const{
	char colAsLetter='A'+ c;
	string result=string(1,colAsLetter) + to_string(r);
	return result; 
}
//did not use it 
//if cell contains given cell ID will change that cell's value
void SpreadSheet::updateDependentCells(const string& cellID){
	int currRow=getRowIndex(cellID);
	int currCol=getColIndex(cellID);
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			if(cells[i][j].getData().find(cellID)!=string::npos){
				string cellVal=cells[i][j].getData();
				updateCell(cellID, to_string(static_cast<int>(parser.parseFormula(cellVal, *this))));
			}
		}
	}
}
//did not use it
//update a cell's value
void SpreadSheet::updateCell(const string cellID, const string& newContent){
	int currRow=getRowIndex(cellID);
	int currCol=getColIndex(cellID);
	if(currCol<0 || currRow<0 || currCol>=col || currRow>=row){
		cout<<"Invalid row or column";
		exit(-1);
	}
	if(newContent[0]=='='){
		bool form=true;
		cells[currRow][currCol].setIsFormula(form);
		stringstream ss;
		//convert formula's double value to string
		double result=parser.parseFormula(newContent,*this);
		ss<<result;
		cells[currRow][currCol].setData(ss.str());
	}
	else if(newContent[0]!='='){
		bool form=false;
		cells[currRow][currCol].setIsFormula(form);
		cells[currRow][currCol].setData(newContent);
	}
	//calls this function to recalculate dependent cells
	recalculateCell();
}
//if cell contains formula recalculates it
void SpreadSheet::recalculateCell(){
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			string cellVal=cells[i][j].getData();
			if(!cellVal.empty() &&cellVal[0]=='='){
				double cell_val=parser.parseFormula(cellVal,*this);//getting numerical value of cell's content
				stringstream ss;
				ss<<cell_val;
				cells[i][j].setData(ss.str());
			}
		}
	}
}

//to save the file
void SpreadSheet::saveToFile(const string& fname)const{
    ofstream file(fname);
    if(!(file.is_open())){
        cerr<<"File could not open for writing"<<endl;
        return;
    }
    int i,j;
    for(i=0;i<row;i++){
        for(j=0;j<col;j++){
        	string cellVal=cells[i][j].getData();
        	if(!cellVal.empty()){
       		     file<<cells[i][j].getData();
        	}
        	else{
        		file<<" ";//if cell is empty print space
        	}
            	if(j<cells[i].size()-1)file<<",";//at the end of every content put comma except the last one
        }
       	file<<endl;
    }
    file.close();
}
//load table from a file
void SpreadSheet::getFromFile(const string& fname){
    ifstream file(fname);
	if(!file.is_open()){
		cerr<<"File Could Not Open!";
		return;
	}
	cells.clear();//clear cells for the new ones
	string line;
	vector<vector<string>> tempCell;//to store cell contents temporarily it felt safer
	while(getline(file, line)){
		vector<string> RowData;//to store rows separately
		string incell;//will get content of a cell
		for(char ch : line){
			if(ch==','){
				RowData.push_back(incell);//add into vector
				incell.clear();//clear for the next cell's content
			}
			else{
				incell+=ch;//getting contents of the cell
			}
		}
		//for the last cell's info
		RowData.push_back(incell);
		//put the that row's cell contents 
		tempCell.push_back(RowData);
	}
	//initializing row and column values
	row=tempCell.size();
	col=tempCell[0].size();
	//resizing cells
	cells.resize(row, vector<Cell> (col));
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			cells[i][j].setData(tempCell[i][j]);//put data into original vector
		}
	}
	file.close();
}

void SpreadSheet::display(AnsiTerminal &terminal, int currentRow, int currentCol) const {
    terminal.clearScreen();
	//user guide
    terminal.printAt(2, 1, "Arrow Keys: Navigate | Enter: Edit | 's': Save | 'l': Load | 'Q': Quit");
    // SELECTED CELLL
    string cellReference = getCellReference(currentRow+1, currentCol);
    string cellValue = getCellValue(currentRow, currentCol);
    terminal.printInvertedAt(3, 1, "Selected Cell: " + cellReference + " = " + cells[currentRow][currentCol].getData());

    // COLUMN HEADERS
    terminal.printAt(5, 5, " "); 
    for (int c = 0; c < col; c++) {
        char colHeader = 'A' + c;
        terminal.printInvertedAt(5, c * 10 + 10, string(1, colHeader)); 
    }

    for (int r = 0; r < row; r++) {
		//print row headers
        terminal.printInvertedAt(6 + r, 2, to_string(r + 1));
        for (int c = 0; c < col; c++) {
            string cellValue = getCellValue(r, c);
			//if its selected cell highlight it
            if (r == currentRow && c == currentCol) {
                terminal.printInvertedAt(6 + r, c * 10 + 10, cellValue.empty() ? " " : cellValue);
            } else {
                terminal.printAt(6 + r, c * 10 + 10, cellValue.empty() ? "." : cellValue);
            }
        }
    }
}
