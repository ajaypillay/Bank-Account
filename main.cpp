#include "main.h"

int main (){

	string name; 
	int age, accountNumber; 
	char gender;
	char typeDeposit;

	cout << "Please enter your name: ";
	getline(cin, name); 
	fflush(stdin);
	cout <<"Please enter your account number: " ;
	cin >> accountNumber; 
	cout <<"Please enter your age: ";
	cin >> age; 
	cout <<"Please enter your gender (M/m/F/f): "; 
	cin >> gender;
	cout <<endl<< "Please enter the type of account: "<<endl ; 
	cout << "Input s for Saving Account" << endl << "Input g for Golden Account" << endl << "Input f for Fixed Deposit"<<endl;
	cin >> typeDeposit;

	balanceCheck account_1(name,accountNumber, age, typeDeposit, gender);  //creating an object of child 

	account_1.showBankAccount();
	account_1. inputWithdrawalDeposit();
	account_1.updateBalance();
	account_1. showBalance();

	return 0;

	// I wanted to access the member functions of the child class using object of parents 
}



  


