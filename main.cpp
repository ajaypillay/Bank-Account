#include "main.h"
#include <string>

int main (){
string name; 
	int age, accountNumber; 
	char gender;
	char typeDeposit;

	cout << "Please enter your name: ";
	
	cin >>name;
	fflush(stdin);
	cout <<"Please enter your account number: " ;
	cin >> accountNumber; 
	cout <<"Please enter your age: ";
	cin >> age; 
	cout <<"Please enter your gender (M/m/F/f): "; 
	cin >> gender;
	cout << "Please enter the type of account: " ; 
	cout << "Input s for Saving Account" << endl << "Input g for Golden Account" << endl << "Input f for Fixed Deposit";
	cin >> typeDeposit;

	bankAccount account1(name,accountNumber, age, typeDeposit, gender); 
	balanceCheck account_1;  

	account1.showBankAccount();
	account_1. inputWithdrawalDeposit();
	account_1.updateBalance();
	account_1. showBalance();

	return 0;

} 
