#include <iostream>

using namespace std;
class Date {
public:
	Date(int d = 1, int m = 1, int y = 1900);
	Date(const Date& oth);
	~Date();
	void setDate(int d, int mon, int y = 1900);
	void setDay(int day);
	void setMonth(int mon);
	void setYear(int year);
	int getDay()const;
	int getMonth()const;
	int getYear()const;
	void increaseDay();
	void compareDay(Date &othDate);
	void displayDate();
private:
	int year, month, day;
	/*set fonk.larýnda kullanýlacak*/
	const int monthDays[12] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
	/*displayde kullanýlacak*/
	const string monthString[12] = { "January","February","March","April","May","June","July","August","September","October","November","December" };
};

Date::Date(int d, int m, int y) {
	setDate(d, m, y);
	cout << "Date is created" << endl;
}

Date::Date(const Date& oth) {
	day = oth.day;
	month = oth.month;
	year = oth.year;
	cout << "Date is copied to the target" << endl;
}

Date::~Date() {
	cout << "Date is detroyed" << endl;
}

void Date::displayDate() {
	cout << day << "\\" << monthString[month - 1] << "\\" << year << endl;
}

void Date::setDate(int d, int mon, int y) {
	/*must call setMonth before setDay since setDay is depends on days of that month*/
	setMonth(mon);
	setDay(d);
	setYear(y);
}

void Date::setMonth(int mon) {
	if (mon >= 1 && mon <= 12) {
		month = mon;
	}
	else {
		month = 1;
	}
}

void Date::setDay(int d) {
	if (d >= 1 && d <= monthDays[month - 1]) {
		day = d;
	}
	else {
		day = 1;
	}
}


void Date::setYear(int y) {
	year = y;
}

int Date::getDay()const {
	return day;
}

int Date::getMonth()const {
	return month;
}

int Date::getYear()const {
	return year;
}

void Date::increaseDay() {
	if (month == 12 && day == monthDays[month - 1]) {
		year++;
		month = 1, day = 1;
	}
	else if(day == monthDays[month - 1]) {
		month++;
		day = 1;
	}
	else {
		day++;
	}
}
/*
void Date::compareDay(Date& oth) {
	Date date;
	if (year > oth.year) {
		(*oth).Date(date);
	}
}*/
void Date::compareDay(Date& oth) {
	long first = 365 * year + month * 30 + day;
	long second = 365 * oth.year + oth.month * 30 + oth.day;
	if (first > second) {
		cout << "First date is greater" << endl;
	}
	if (first < second) {
		cout << "Second date is greater" << endl;
	}
	else {
		cout << "Equal" << endl;
	}
}


