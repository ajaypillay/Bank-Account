#include <iostream>
#include <string> 
using namespace std; 

class bankAccount {
protected: // may need to be changed to protected later 
  string name;
  int accountNumber;
  int age;
  char deposit; 
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
    deposit = d;
    gender = g; 
    
  }
  
  void bankAccount :: showBankAccount (void){
    cout << "Hello " << name << endl; 
    
    if (g == 'm'|| g == 'M'){
      cout <<"Gender: Male" << endl; 
    } else if ( g == 'f' || g == 'F'){
      cout << "Gender: Female" << endl;
    }
    
    cout << "Gender: " << gender << endl; 
    cout << "Age: " << age << endl; 
    cout << "This is your account number: " << accountNumber << endl;
    
    if ( deposit == 's') {
      cout << "Type of deposit: Saving Account. " << endl;
    } else if (deposit == 'g') {
      cout <<"Type of deposit: Golden Account. " << endl;
    } else if (deposit == 'f'){
      cout <<"Type of deposit: Fixed Deposite. " << endl;
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
  };
  
  void balanceCheck::inputWithdrawalDeposit(void){
    cout <<"Please select the mode (Withdrawal : w / Deposit : g): " << endl;
    cin >> modeBalance; 
    
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
      accountBalance = accountBalance + withdrawalAmount; 
    }
  }
  
  void balanceCheck:: showBalance (void) {
    cout <<"Your balance is: " << accountBalance << endl;
  }
  
  /* so what we need to do is to 
  1. ask if the user wants to withdraw/deposit, and then records the amount ---> inputWithdrawalDeposit();
  2. then call updateBalance() to update the amount deposited / withdrawn to accountBalance;
  3. anytime i need to check accountBalance, call showBalance(); 
  


