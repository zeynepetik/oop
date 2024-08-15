#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Matrix {
	int row, col;
	int** matrix;
public:
	Matrix(int row = 2, int col = 2);
	~Matrix();
	Matrix(Matrix& oth);
	int getRow()const {
		return row;
	};
	int getCol()const {
		return col;
	};
	void setValue(int r, int c, int value);
	void randomSet();
	void identityMatrixSet();/*unit matrix*/
	void display();
	void addMatrix(Matrix& oth);
	void multMatrix(Matrix& oth);
	void isEqual(Matrix& oth);
	void transpoz();
};

Matrix::Matrix(int r, int c) {
	row = r, col = c;
	matrix = new int*[row];
	for (int i = 0; i < row; i++) {
		matrix[i] = new int[col];
	}
	cout << "Matrix is created" << endl;
}

Matrix::~Matrix() {
	for (int i = 0; i < row; i++) {
		delete[]matrix[i];
	}
	delete[]matrix;
	cout << "Matrix is destroyed" << endl;
}

Matrix::Matrix(Matrix& oth) {
	for (int i = 0; i < row; i++) {
		delete[]matrix[i];
	}
	delete[]matrix;
	matrix = new int*[oth.row];
	for (int i = 0; i < oth.row; i++) {
		matrix[i] = new int[oth.col];
	}
	col = oth.col, row = oth.row;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			matrix[i][j] = oth.matrix[i][j];
		}
	}
	cout << "Matrix copied to target" << endl;
}

void Matrix::setValue(int r, int c, int value) {
	matrix[r][c] = value;
}

void Matrix::randomSet() {
	int i, j;
	srand(time(NULL));
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			matrix[i][j] = rand() % 10;
		}
	}
}

void Matrix::identityMatrixSet() {
	int i, j;
	if (row == col) {
		for (i = 0; i < row; i++) {
			for (j = 0; j < col; j++) {
				if (i == j)matrix[i][j] = 1;
				else {
					matrix[i][j] = 0;
				}
			}
		}
	}
	else {
		cout << "It is not an nxn matrix" << endl;
	}
}

void Matrix::display() {
	int i, j;
	/*col kadar ekliyor row kadar \n yapýyor*/
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

void Matrix::addMatrix(Matrix& oth) {
	if (row == oth.row && col == oth.col) {
		Matrix add(row,col);
		int i, j;
		for (i = 0; i < row; i++) {
			for (j = 0; j < col; j++) {
				add.setValue(i, j, matrix[i][j] + oth.matrix[i][j]);
			}
		}
		add.display();
	}
	else {
		cout << "Dimensions must be equal to add" << endl;
	}
}

void Matrix::multMatrix(Matrix& oth) {
	if (col==oth.row) {
		Matrix result(row,oth.col);
		int i, j, k, m, sum = 0;
		for (i = 0; i < row; i++) {
			for (j = 0; j < oth.col; j++) {
				sum = 0;
				for (k = 0; k < oth.row; k++) {
					sum += matrix[i][k] * oth.matrix[k][j];
				}
				result.matrix[i][j] = sum;
			}
		}
		result.display();
	}
	else {
		cout << "These matrixes cannot be multiplied" << endl;
	}
}

void Matrix::isEqual(Matrix& oth) {
	if (row != oth.row || col != oth.col) {
		cout << "Matrixes are not equal"<<endl;
	}
	else{
		int i, j;
		for (i = 0; i < row; i++) {
			for (j = 0; j < col; j++) {
				if (matrix[i][j] != oth.matrix[i][j]) {
					cout << "Matrixes are not equal" << endl;
					break;
				}
			}
		}
		cout << "Matrixes are equal" << endl;
	}
}

void Matrix::transpoz() {
	Matrix result(col,row);
	int i, j;
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			result.matrix[j][i] = matrix[i][j];
		}
	}
	result.display();
}