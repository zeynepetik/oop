#include <iostream>
#include "spreadSheet.h"
#include "AnsiTerminal.h"

using namespace std;

int main() {
    AnsiTerminal terminal;
    int row,col;
    cout<<"ENTER DESIRED DIMENSIONS FOR THE TABLE\nFirst one is row and second is column"<<endl;
    cin>>row;
    cin>>col;
    SpreadSheet sheet(row,col);
    
    bool running = true;
    int currentRow = 0, currentCol = 0;

    while (running) {
    sheet.display(terminal, currentRow, currentCol);

    char input = terminal.getSpecialKey();
    switch (input) {
        case 'U': // Up Arrow
            if (currentRow > 0) currentRow--;
            break;
        case 'D': // Down Arrow
            if (currentRow < sheet.getRow() - 1) currentRow++;
            break;
        case 'L': // Left Arrow
            if (currentCol > 0) currentCol--;
            break;
        case 'R': // Right Arrow
            if (currentCol < sheet.getCol() - 1) currentCol++;
            break;
        case 'E': {
            //terminal.printAt(sheet.getRow()-10+17, 1, "Enter new value: ");
            string newValue=terminal.getUserInput(sheet.getRow()-10+17, 1);
            sheet.setCellValue(currentRow, currentCol, newValue);
            break;
        }
        case 's': {
            terminal.printAt(sheet.getRow()-10+17, 1, "Enter file name to save: ");
            string filename=terminal.getUserInput(sheet.getRow()-10+18, 1);
            sheet.saveToFile(filename);
            //terminal.printAt(sheet.getRow()-10+18, 1, "Saved successfully!");
            break;
        }
        case 'l': {
            terminal.printAt(sheet.getRow()-10+17, 1, "Enter file name to load: ");
            string filename=terminal.getUserInput(sheet.getRow()-10+18, 1);
            sheet.getFromFile(filename);
            //terminal.printAt(sheet.getRow()-10+18, 1, "Loaded successfully!");
            break;
        }
        case 'Q': 
            running = false;
            break;
        default:
            break;
    }
}

    terminal.clearScreen();
    terminal.printAt(1, 1, "Goodbye!");
    return 0;
}
