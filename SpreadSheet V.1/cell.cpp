#include <iostream>
#include "cell.h"
#include <vector>

using namespace std;
//constructor to initialize cell's contents
Cell::Cell(string c){
	content=c;
	if(c[0]=='=') isFormul=true;
	else{
		isFormul=false;
	}
}
//controling if content is formula or not
bool Cell::isFormula(){
	if(content[0]=='=')
		isFormul=true;
	else{
		isFormul=false;
	}
	return isFormul;
}

void Cell::setIsFormula(bool formula){
	isFormul=formula;
}

void Cell::setData(string c){
	content=c;
}

string Cell::getData()const{ return content;}
