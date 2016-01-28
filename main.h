#include <iostream>
#include <string> 
using namespace std; 


// ajay will take care of the assigning of account number 

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
  // NIL = n 
  
public:
  bankAccount (string, int, int, char, char); // initialize private/protected data members
  void showBankAccount (void);
  void checkGoldenAccountValidity (void); 
  void reselectAccount (void); 
  
};

void bankAccount :: reselectAccount (void){
	cout <<"\nGolden Account is only for users above 55 years old, please reselect your option.";
	cout <<"\nEnter (s) for Saving Account or (f) for Fixed Deposit: ";
	cin >> typeDeposit; 
}

void bankAccount :: checkGoldenAccountValidity (void){
	if (typeDeposit =='g'){
	if (age >55 ) {
		typeDeposit = 'g'; 
	} else if (age <=55){
		typeDeposit = 'n';
		reselectAccount ();  // here 
	}
}


}

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
	double interestSavingAcc;
	double interestGoldenAcc; 
	double interestFixedDeposit; 
	int yearsFixedDeposit; 
  public:
    void inputWithdrawalDeposit(void);
    void updateBalance(void);
    void showBalance(void);
	balanceCheck(string, int, int, char, char);
	void accountCheck (void);
  };

  void balanceCheck :: accountCheck (void){
	  if (typeDeposit == 's'){
		  while (accountBalance < 100){
		  cout <<"\nThe minimum balance is $100, please make some deposit!"<<endl;
		  inputWithdrawalDeposit();
		  updateBalance();
		  showBalance(); 
	  }
	  interestSavingAcc = 0.25; 

	  } else if (typeDeposit =='g'){

		  if (accountBalance < 50000){
		  while (accountBalance <100){
			  cout <<"\nThe minimum balance is $100, please make some deposit!"<<endl;
			  inputWithdrawalDeposit();
			  updateBalance();
			  showBalance();
		  }
		  interestGoldenAcc = 0.375; 
	  }

	  else if (accountBalance > 50000){
		  interestGoldenAcc = 0.5; 
		  
	  } 

	  } else if (typeDeposit =='f'){
		  while (accountBalance < 5000){
		  cout <<"\nThe minimum balance is $5000, please make some deposit!"<<endl;
		  inputWithdrawalDeposit();
		  updateBalance();
		  showBalance();
	  }

	  if (yearsFixedDeposit == 1){ // haven't have a way to assign the yearsFixedDeposit yet, overlap with ajay's work 
		  interestFixedDeposit = 0.55;
	  } else if (yearsFixedDeposit == 2){
		  interestFixedDeposit = 0.7;
	  } else if (yearsFixedDeposit >= 3){
		  interestFixedDeposit = 0.8;
	  }
	  }

  }
  

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
	  if (accountBalance < withdrawalAmount){
		  cout <<"You do not have enough money!"<<endl;
		  withdrawalAmount = 0;
	  }

    } else if (modeBalance == 'd'){
      cout <<"Please enter the amount you wish to deposit: " << endl;
      cin >> depositAmount;
	  if (depositAmount < 0){
		  cout <<"Invalid deposit amount" <<endl;
		  depositAmount =0;
	  }
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
