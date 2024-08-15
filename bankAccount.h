#include <iostream>

using namespace std;
class BankAcc {
public:
	BankAcc(string name, string surname, float balance = 0, string phone_number = "");
	BankAcc(const BankAcc& oth);
	~BankAcc();
	bool controlNameSurname(string nameOrSurname);
	bool controlPhoneNumber(string phoneNumber);
	void displayProfile();
	void credit(float);
	void withdraw(float);
	void sendMoney(BankAcc& othAccount, float amount);
	void setPersonName(string name);
	void setPersonSurname(string surname);
	void setPersonPhone(string phone);
	void setPersonBalance(float balance = 0);
	int getPersonBalance() const { return accountBalance; };
	string getPersonName()const { return personName; };
	string getPersonSurname() const { return personSurname; };
	string getPersonPhone() const { return personPhone; };
private:
	float accountBalance;
	string personName, personSurname, personPhone;
};

BankAcc::BankAcc(string name, string surname, float balance, string phone_number) {
	personName = name;
	personSurname = surname;
	personPhone = phone_number;
	accountBalance = balance;
}

BankAcc::BankAcc(const BankAcc& oth) {
	personName = oth.personName;
	personSurname = oth.personSurname;
	personPhone = oth.personPhone;
	accountBalance = oth.accountBalance;
}

BankAcc::~BankAcc() {
	cout << "Bank account is destroyed" << endl;
}

bool BankAcc::controlNameSurname(string nameOrSurname) {
	int i = 0;
	while (nameOrSurname[i] != '\0') {
		if (!(nameOrSurname[i] >= 'A' && nameOrSurname[i] <= 'Z') && !(nameOrSurname[i] >= 'a' && nameOrSurname[i] <= 'z')) {
			return false;
		}
		i++;
	}
	if (i != 0)return true;
	else {
		return false;
	}
}

bool BankAcc::controlPhoneNumber(string phoneNumber) {
	int i = 0;
	if (phoneNumber == "") {
		return false;
	}
	while (phoneNumber[i] != '\0') {
		if (!(phoneNumber[i] >= '0' && phoneNumber[i] <= '9')) {
			return false;
		}
		i++;
	}
	if (i != 11)return false;
	return true;
}

void BankAcc::displayProfile() {
	cout << "NAME & SURNAME: " << personName << " " << personSurname << endl;
	cout << "PHONE NUMBER: " << personPhone << endl;
	cout << "ACCOUNT BALANCE: " << accountBalance << endl;
}

void BankAcc::credit(float cash) {
	if (!(cash < 0)) {
		accountBalance += cash;
	}
	else {
		cout << "Invalid amount" << endl;
	}
}

void BankAcc::withdraw(float cash) {
	if (!(cash < 0) && cash<=accountBalance) {
		accountBalance -= cash;
	}
	if(cash > accountBalance){
		cout << "Insufficient account balance" << endl;
	}
}

void BankAcc::sendMoney(BankAcc& oth, float amount) {
	if (amount > accountBalance) {
		cout << "Insufficient account balance" << endl;
	}
	else{
		oth.accountBalance += amount;
		accountBalance -= amount;
		cout << amount << "sent to " << oth.personName << " " << oth.personSurname << "from " << personName << " " << personSurname << endl;
	}
}

void BankAcc::setPersonName(string name) {
	personName = name;
}

void BankAcc::setPersonSurname(string surname) {
	personSurname = surname;
}

void BankAcc::setPersonPhone(string phone) {
	personPhone = phone;
}

void BankAcc::setPersonBalance(float balance ){
	accountBalance = balance;
}