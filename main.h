#include <iostream>
#include <string> 
using namespace std; 

#include <iostream>
#include <string> 
using namespace std; 

class bankAccount {
protected: // may need to be changed to protected later 
  string name;
  int accountNumber;
  int age;
  char typeDeposit; 
  char gender; // m / M / f / F 
  //saving account = s ;
  //golden account = g ;
  //fixed deposit = f ;
  
public:
  bankAccount (string, int, int, char, char); // initialize private/protected data members
  void showBankAccount (void);
  
};


  bankAccount :: bankAccount (string n, int acc, int a, char d, char g){
    // remember to use fflush(stdin);
    name = n;
    accountNumber = acc;
    age = a;
    typeDeposit = d;
    gender = g; 
    
  }
  
  void bankAccount :: showBankAccount (void){
    cout <<endl<< "Hello " << name << endl; 
    
    if (gender == 'm'|| gender == 'M'){
      cout <<"Gender: Male" << endl; 
    } else if ( gender == 'f' || gender == 'F'){
      cout << "Gender: Female" << endl;
    }
    
    cout << "Gender: " << gender << endl; 
    cout << "Age: " << age << endl; 
    cout << "This is your account number: " << accountNumber << endl;
    
    if ( typeDeposit == 's') {
      cout << "Type of deposit: Saving Account. " << endl;
    } else if (typeDeposit == 'g') {
      cout <<"Type of deposit: Golden Account. " << endl;
    } else if (typeDeposit == 'f'){
      cout <<"Type of deposit: Fixed Deposit. " << endl;
    }
    
    }


  class balanceCheck : public bankAccount { // child of bankAccount
  private: // not sure if need to be protected yet 
    double accountBalance;
    char modeBalance; // d for deposite and w for withdrawal
    double depositAmount, withdrawalAmount;
    double amountWithdrawal;
    double amountDeposit;
  public:
    void inputWithdrawalDeposit(void);
    void updateBalance(void);
    void showBalance(void);
	balanceCheck(string, int, int, char, char);
  };
  
  void balanceCheck::inputWithdrawalDeposit(void){
    cout <<"Please select the mode (Withdrawal : w / Deposit : d): ";
    cin >> modeBalance; 

	if (accountBalance <= 0 && modeBalance == 'w'){
		cout <<endl <<"Gentle reminder: " << endl; 
		cout <<"Your balance is lesser or equals to zero, unable to perform any withdrawal operations. " << endl;
		return ; 
	}
    
    if (modeBalance == 'w'){
      cout <<"Please enter the amount you wish to withdraw: " << endl;
      cin >> withdrawalAmount;
    } else if (modeBalance == 'd'){
      cout <<"Please enter the amount you wish to deposit: " << endl;
      cin >> depositAmount;
    }
  }
  
  void balanceCheck::updateBalance (void){
    if (modeBalance == 'd'){
      accountBalance = accountBalance + depositAmount; 
    } else if (modeBalance =='w'){
      accountBalance = accountBalance - withdrawalAmount; 
    }
  }
  
  void balanceCheck:: showBalance (void) {
    cout <<"Your balance is: " << accountBalance << endl << endl;
  }


 balanceCheck :: balanceCheck (string n, int acc, int a, char d, char g) : bankAccount(n,acc, a, d, g) {
	name = n;
    accountNumber = acc;
    age = a;
    typeDeposit = d;
    gender = g;
	depositAmount =0;
	withdrawalAmount = 0;
	accountBalance = 0;
  }
  
  /* so what we need to do is to 
  1. ask if the user wants to withdraw/deposit, and then records the amount ---> inputWithdrawalDeposit();
  2. then call updateBalance() to update the amount deposited / withdrawn to accountBalance;
  3. anytime i need to check accountBalance, call showBalance(); 
  */
