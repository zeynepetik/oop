#include <iostream>
using namespace std;
class Student {
	string student_name, stu_surname, stu_id;
public://de�i�kn ve fonk.lar�n mainden eri�ilebilirli�ini sa�l�yor
	void displayInfo();
	void setinfo(string name, string surname, string id) {
		student_name = name;
		stu_surname = surname;
		stu_id = id;
	};
	~Student() {
		cout << "Desteuctor worked" << endl;
	}
	Student(const Student& oth) {
		cout << "Copy constructer worked"<<endl;
		student_name = oth.student_name;
		stu_surname = oth.stu_surname;
		stu_id = oth.stu_id;
	}
	//string getinfo();
	//Student();
	Student(string name, string surname,string id) {
		cout << "Constructor worked" << endl;
		student_name = name;
		stu_surname = surname;
		stu_id = id;
	};
};

/*Student::Student() {
	student_name = "none";
	stu_id = "none";
	stu_surname = "none";
}*/

void Student:: displayInfo() {//ba�a Student getirme nedeni ba�ka biir classda da ayn� fonk. olabilirdi
	//student class�n�n displayInfo fonksiyounu
	cout << "Name: " << student_name << " " << stu_surname << endl;
	cout << "ID: " << stu_id << endl;

}/*
void Student::setinfo(string name, string surname, string id){
	student_name = name;
	stu_surname = surname;
	stu_id = id;

}*/