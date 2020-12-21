//============================================================================
// Name        : banking_app.cpp
// Author      : Ryan Mitchell,
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <conio.h>
#include <iomanip>
using namespace std;

class BankAccount {
	public:
		BankAccount();
		void SetInitInvestment(double initialToSet);				// Constructor and Mutators/Accessors defined
		double GetInitInvestment();
		void SetMonthlyDeposit(double depositToSet);
		double GetMonthlyDeposit();
		void SetAnnualInterest(double interestToSet);
		double GetAnnualInterest();
		void SetNumYears(int yearsToSet);
		int GetNumYears();
	private:
		double initInvestment;										// Variables defined
		double monthlyDeposit;
		double annualInterest;
		int numYears;
		int numMonths;
};
BankAccount::BankAccount() {										// Default constructor
	initInvestment = 0;
	monthlyDeposit = 0;
	annualInterest = 0;
	numYears = 0;
	numMonths = 0;
}
void BankAccount::SetInitInvestment(double initialToSet) {
	initInvestment = initialToSet;
}
double BankAccount::GetInitInvestment() {
	return initInvestment;
}
void BankAccount::SetMonthlyDeposit(double depositToSet) {
	monthlyDeposit = depositToSet;
}
double BankAccount::GetMonthlyDeposit() {
	return monthlyDeposit;
}
void BankAccount::SetAnnualInterest(double interestToSet) {
	annualInterest = interestToSet;
}
double BankAccount::GetAnnualInterest() {
	return annualInterest;
}
void BankAccount::SetNumYears(int yearsToSet) {
	numYears = yearsToSet;
}
int BankAccount::GetNumYears() {
	return numYears;
}

double YearEndBal(BankAccount bankNumber, int year, bool withDepo) {					// Function to determine which balance to calculate
	double finalTotal = 0;																// Bool variable to determine which branch
	double startingAmount = bankNumber.GetInitInvestment();								// Object passed and accessed to define variables
	double interest = bankNumber.GetAnnualInterest() / 100;
	double monthlyInterest = 1 + (interest / 12);
	double monthlyDepo = bankNumber.GetMonthlyDeposit();
	if (!withDepo) {
		for (int i = 0; i < year; ++i) {
				finalTotal = startingAmount + (startingAmount * interest);
				startingAmount = finalTotal;
			}
	} else {
		for (int i = 0; i < year * 12; ++i) {
			finalTotal = (startingAmount + monthlyDepo) * monthlyInterest;
			startingAmount = finalTotal;
		}
	}
	return finalTotal;
}

double YearEndInterest(BankAccount bankNumber, int year) {								// Method to calculate interest for NO deposits
	double finalTotal = 0;
	double startingAmount = bankNumber.GetInitInvestment();
	double interest = bankNumber.GetAnnualInterest() / 100;
	double amountInterest = 0;
	for (int i = 0; i < year; ++i) {
		finalTotal = startingAmount + (startingAmount * interest);
		amountInterest = finalTotal - startingAmount;
		startingAmount = finalTotal;
	}
	return amountInterest;
}
double YearEndInterestForMonthly(BankAccount bankNumber, int year) {					// Method to calculate interest WITh monthly deposits
	double finalTotal = 0;
	double monthStart = 0;
	double startingAmount = bankNumber.GetInitInvestment();
	double monthlyInterest = 1 + (bankNumber.GetAnnualInterest() / 100) / 12;
	double monthlyDepo = bankNumber.GetMonthlyDeposit();
	double amountInterest = 0;
	for (int i = 1; i <= year * 12; ++i) {
		monthStart = startingAmount + monthlyDepo;
		finalTotal = monthStart * monthlyInterest;
		amountInterest += finalTotal - monthStart;
		startingAmount = finalTotal;
		if ((i % 12 == 0) && (i != year * 12)) {
			amountInterest = 0;
		}
	}
	return amountInterest;
}

void DisplayBalIntWithout(BankAccount bankNumber) {										// Display screen with for loop to determine how many
	int numYears = bankNumber.GetNumYears();											// years are required to display. Parameter is object
	cout << "   Balance and Interest Without Additional Monthly Deposits" << endl;
	cout << "===============================================================" << endl;
	cout << "  Year         Year End Balance       Year End Earned Interest " << endl;
	cout << "---------------------------------------------------------------" << endl;
	for (int i = 1; i <= numYears; ++i) {
		cout << "   " << i << "                 " << fixed << setprecision(2) << YearEndBal(bankNumber, i, false) << "                  "
				<< YearEndInterest(bankNumber, i) << endl;
	}
	cout << endl << endl;

}
void DisplayBalIntWith(BankAccount bankNumber) {										// Same as above for monthly deposits included
	int numYears = bankNumber.GetNumYears();
	cout << "   Balance and Interest With Additional Monthly Deposits" << endl;
	cout << "===============================================================" << endl;
	cout << "  Year         Year End Balance       Year End Earned Interest " << endl;
	cout << "---------------------------------------------------------------" << endl;
	for (int i = 1; i <= numYears; ++i) {
		cout << "   " << i << "               " << fixed << setprecision(2) << YearEndBal(bankNumber, i, true) << "                  "
				<< YearEndInterestForMonthly(bankNumber, i) << endl;
	}
	cout << endl << endl;

}

void GatherInput(BankAccount* bankNumber) {									// Console for user input, gathers variables and uses
	double doubleTemp;
	int intTemp;															// referenced pointer to assign object variables

	cout << "********************************" << endl;
	cout << "********** Data Input **********" << endl;
	cout << "Initial Investment Amount: $";
	cin >> doubleTemp;
	bankNumber->SetInitInvestment(doubleTemp);
	cout << "Monthly Deposit: $";
	cin >> doubleTemp;
	bankNumber->SetMonthlyDeposit(doubleTemp);
	cout << "Annual Interest: %";
	cin >> doubleTemp;
	bankNumber->SetAnnualInterest(doubleTemp);
	cout << "Number of years: ";
	cin >> intTemp;
	bankNumber->SetNumYears(intTemp);
	cout << "--------------------------" << endl;

}


int main() {														// Main method, object initiated and pointer created for reference
	BankAccount userBank;
	BankAccount* bankAccess = &userBank;

	GatherInput(bankAccess);
	DisplayBalIntWithout(userBank);									// Displays static charts for output
	DisplayBalIntWith(userBank);


	return 0;
}
