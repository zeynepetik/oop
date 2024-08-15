#include <iostream>

using namespace std;
class Array{
	int* data, size, capacity;
	int findIndex(int number, int b=0);
public:
	Array(int user_capacity = 5);
	~Array();
	Array(const Array& copyArray);
	int getSize()const;
	int getCapacity()const;
	void addItem(int Item);
	void printItem();
	void removeIndexItem(int index);
	void removeItem(int item);
	void findElement(int number, int index = 0);

};

Array::Array(int user_capacity) {
	capacity = user_capacity;
	size = 0;
	data = new int[capacity];
	printf("Array Created\n");
}

Array::~Array() {
	cout << "Destructor Worked" << endl;
}

Array::Array(const Array& copyArray) {
	capacity = copyArray.capacity;
	data = copyArray.data;
	size = copyArray.size;
	printf("Copy Constructor Worked\n");
}

int Array::getSize()const {
	return size;
}

int Array::getCapacity()const {
	return capacity+1;
}
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
void Array::addItem(int Item) {
	if (size == capacity) {
		int* temp_data = new int[capacity + 10];
		for (int i = 0; i < size; i++) {
			temp_data[i] = data[i];
		}
		delete[]data;
		data = temp_data;
		capacity += 10;
	}
	data[size] = Item;
	size++;
}

void Array::printItem() {
	int i;
	cout << "{";
	if (size != 0) {
		for (i = 0; i < size; i++) {
			if (i != size - 1)printf("%d, ", data[i]);
			else {
				printf("%d ", data[i]);
			}
		}
		cout << "}" << endl;
	}
	cout << "\n" << "Size: " << size << " Capacity: " << capacity << endl;
}

void Array::removeIndexItem(int index) {
	int i, j, flag = 0;
	if (index < 0 || index >= size) {
		cout << "Invalid index" << endl;
	}
	for (i = 0; i < size; i++) {
		if (i == index) {
			size--;
			for (j = i; j < size; j++) {
				data[j] = data[j + 1];
			}
		}
	}
	if (flag == 0)cout << "There is not enough index" << endl;
}

void Array::removeItem(int item) {
	int i, j, counter = 0;
	for (i = 0; i < size; i++) {
		if (data[i] == item) {
			counter++;
			for (j = i; j < size; j++) {
				data[j] = data[j + 1];
			}
		}
	}
	if (counter == 0) {
		cout << "Could not find the item" << endl;
	}
	size -= counter;
}

int Array::findIndex(int number, int index) {
	int i;
	for (i = index; i < size; i++) {
		if (data[i] == number) {
			return i+1;
		}
	}
	return -1;
}

void Array::findElement(int number, int index) {
	int result = findIndex(number, index);
	if (result == -1) {
		cout << number << " could not find after index "<<index << endl;
	}
	else {
		cout << number << " found at index " << result << endl;
	}
}

