#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <time.h>
#include <stdio.h>
#include <limits>

using namespace std;

void clearScreen() {
    int x = 0;
    while (x < 25) {
        cout<<"\n";
        x++;
    }
    return;
}

string timeNow() {
    time_t now = time(0);
    struct tm  tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
    buf[10] = ' ';
    return buf;
}

class Logger {
    public:
        void withdrawDeposit(string, string, int, int);
        void login(string);
        void logout(string);
        void newAccount(string, string);
};

void Logger::withdrawDeposit(string a, string b, int c, int d){
    ofstream Log;
    Log.open("Log.txt", ios_base::app);
    Log<<"["<<timeNow()<<"] "<<a<<" has "<<b<<" $"<<c<<". Balance: $"<<d<<"\n";
}

void Logger::login(string a){
    ofstream Log;
    Log.open("Log.txt", ios_base::app);
    Log<<"["<<timeNow()<<"] "<<a<<" has successfully logged in.\n";
}

void Logger::logout(string a){
    ofstream Log;
    Log.open("Log.txt", ios_base::app);
    Log<<"["<<timeNow()<<"] "<<a<<" has successfully logged out.\n";
}

void Logger::newAccount(string a, string b){
    ofstream Log;
    Log.open("Log.txt", ios_base::app);

    if (b == "s") {
        Log<<"["<<timeNow()<<"] "<<a<<" has opened a Saving Account.\n";
    }
    else if (b == "d") {
        Log<<"["<<timeNow()<<"] "<<a<<" has opened a Fixed Deposit Account.\n";
    }
    else if (b == "g") {
        Log<<"["<<timeNow()<<"] "<<a<<" has opened a Golden Account.\n";
    }
}

class bankAccount {
    public:
        string typeDeposit;
    protected:
        string name;
        int accountNumber;
        int age;
        string gender; // m / M / f / F
        //saving account = s ;
        //golden account = g ;
        //fixed deposit = f ;
        // NIL = n
    public:
        bankAccount(string, int, int, string, string); // initialize private/protected data members
        void showBankAccount(void);
        void checkGoldenAccountValidity(void);
        void reselectAccount(void);
        Logger log;
};

void bankAccount::reselectAccount(void) {
    clearScreen();
    showBankAccount();
	cout<<"\nThe Golden Account is only for depositors aged 55 years old or above.\nPlease reselect your option."<<endl;
	cout<<"\nEnter [S] for Saving Account or [F] for Fixed Deposit: ";
	cin>>typeDeposit;
	while (typeDeposit != "s" && typeDeposit != "S" && typeDeposit != "f" && typeDeposit != "F"){
        showBankAccount();
        cout<<"\nInvalid account type! Please reenter:\n\n";
        cout<<"\nThe Golden Account is only for depositors aged 55 years old or above.\nPlease reselect your option."<<endl;
        cout<<"\nEnter [S] for Saving Account or [F] for Fixed Deposit: ";
        cin>>typeDeposit;
    }
}

void bankAccount::checkGoldenAccountValidity(void) {
	if (typeDeposit == "g") {
        if (age >= 55) {
            typeDeposit = "g";
        }
        else if (age < 55) {
            typeDeposit = "n";
            reselectAccount();  // here
        }
    }
}

bankAccount::bankAccount (string n, int acc, int a, string d, string g) {
    // remember to use fflush(stdin);
    name = n;
    accountNumber = acc;
    age = a;
    typeDeposit = d;
    gender = g;
}

void bankAccount::showBankAccount(void) {
    clearScreen();
    cout<<endl<<"Hello, "<<name<<"!"<<endl<<endl;
    if (gender == "m" || gender == "M") {
        cout<<"Gender: Male"<<endl;
    }
    else if (gender == "f" || gender == "F") {
        cout<<"Gender: Female"<<endl;
    }

    cout<<"Age: "<<age<<endl;
    cout<<"Account Number: GCB-"<<accountNumber<<endl;

    if (typeDeposit == "s") {
        cout<<"Type of account: Saving Account "<<endl;
    }
    else if (typeDeposit == "g") {
        cout<<"Type of account: Golden Account"<<endl;
    }
    else if (typeDeposit == "f") {
        cout<<"Type of account: Fixed Deposit "<<endl;
    }
}

class balanceCheck:public bankAccount { // child of bankAccount
    public:
        double accountBalance;
    private: // not sure if need to be protected yet
        string modeBalance; // d for deposite and w for withdrawal
        double depositAmount, withdrawalAmount;
        double amountWithdrawal;
        double amountDeposit;
        double interestSavingAcc;
        double interestGoldenAcc;
        double interestFixedDeposit;
        int yearsFixedDeposit;
    public:
        balanceCheck(string, int, int, string, string);
        void inputWithdrawalDeposit(void);
        void showBalance(void);
        void interestCalc (void);
        Logger log;
};

void balanceCheck::interestCalc(void) {
    if (typeDeposit == "s") {
        interestSavingAcc = 0.25;
    }
    else if (typeDeposit =="g") {
        if (accountBalance < 50000) {
            interestGoldenAcc = 0.375;
        }
        else if (accountBalance > 50000) {
		  interestGoldenAcc = 0.5;
        }
    }
    else if (typeDeposit =="f") {
        if (yearsFixedDeposit == 1) { // haven't have a way to assign the yearsFixedDeposit yet, overlap with ajay's work
            interestFixedDeposit = 0.55;
        }
        else if (yearsFixedDeposit == 2){
            interestFixedDeposit = 0.7;
        }
        else if (yearsFixedDeposit >= 3){
            interestFixedDeposit = 0.8;
        }
    }
}

void balanceCheck::inputWithdrawalDeposit(void) {
    cout<<"Balance: $"<<accountBalance<<endl;
    cout<<endl<<"Please select the mode - [W]ithdrawal or [D]eposit: ";
    cin>>modeBalance;
    while (modeBalance != "w" && modeBalance != "W" && modeBalance != "d" && modeBalance != "D"){
        clearScreen();
        showBankAccount();
        cout<<"Balance: $"<<accountBalance<<endl;
        cout<<"\nInvalid option! Please reselect:\n\n";
        cout<<endl<<"Please select the mode - [W]ithdrawal or [D]eposit: ";
        cin>>modeBalance;
    }

    if (modeBalance == "D") modeBalance = "d";
    else if(modeBalance == "W") modeBalance = "w";

	if (accountBalance <= 0 && modeBalance == "w") {
        clearScreen();
		cout<<endl<<"!!! Warning !!!"<<endl<<endl;
		cout<<"Insufficient funds in account."<<endl;
		inputWithdrawalDeposit();
	}

    else if (modeBalance == "w") {
        cout<<"Please enter the amount you wish to withdraw: $";
        cin>>withdrawalAmount;
        while(!cin || !(withdrawalAmount > 0)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            clearScreen();
            showBankAccount();
            cout<<"Balance: $"<<accountBalance<<endl;
            cout<<endl<<"Please select the mode - [W]ithdrawal or [D]eposit: "<<modeBalance<<"\n\n";
            cout<<"Invalid amount! Please reenter:\n\n";
            cout<<"Please enter the amount you wish to withdraw: $";
            cin>>withdrawalAmount;
        }
        if (accountBalance < withdrawalAmount) {
            clearScreen();
            showBankAccount();
            cout<<"\n\nYou cannot withdraw more money than available in your account. Operation terminating.\n"<<endl;
            withdrawalAmount = 0;
            inputWithdrawalDeposit();
        }
        else {
            if (typeDeposit == "s") {
                if ((accountBalance - withdrawalAmount) <= 100) {
                    clearScreen();
                    showBankAccount();
                    cout<<"\nSaving Accounts require a minimum of $100 balance at all times.\n";
                    inputWithdrawalDeposit();
                }
                else {
                    accountBalance = accountBalance - withdrawalAmount;
                    log.withdrawDeposit(name, "withdrawn", withdrawalAmount, accountBalance);
                }
            }
            else if (typeDeposit == "g") {
                if ((accountBalance - withdrawalAmount) <= 100) {
                    clearScreen();
                    showBankAccount();
                    cout<<"\nGolden Accounts require a minimum of $100 balance at all times.\n";
                    inputWithdrawalDeposit();
                }
                else {
                    accountBalance = accountBalance - withdrawalAmount;
                    log.withdrawDeposit(name, "withdrawn", withdrawalAmount, accountBalance);
                }
            }
            else if (typeDeposit == "f") {
                if ((accountBalance - withdrawalAmount) <= 5000) {
                    clearScreen();
                    showBankAccount();
                    cout<<"\nFixed Deposits require a minimum of $5,000 balance at all times.\n";
                    inputWithdrawalDeposit();
                }
                else {
                    accountBalance = accountBalance - withdrawalAmount;
                    log.withdrawDeposit(name, "withdrawn", withdrawalAmount, accountBalance);
                }
            }
        }
    }

    else if (modeBalance == "d") {
        cout<<"Please enter the amount you wish to deposit: $";
        cin>>depositAmount;
        while(!cin || !(depositAmount > 0)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            clearScreen();
            showBankAccount();
            cout<<"Balance: $"<<accountBalance<<endl;
            cout<<endl<<"Please select the mode - [W]ithdrawal or [D]eposit: "<<modeBalance<<"\n\n";
            cout<<"Invalid amount! Please reenter:\n\n";
            cout<<"Please enter the amount you wish to deposit: $";
            cin>>depositAmount;
        }
        if (depositAmount < 0) {
            clearScreen();
            showBankAccount();
            cout<<"\n\nInvalid deposit amount. Operation terminating.\n"<<endl;
            depositAmount = 0;
            inputWithdrawalDeposit();
        }
        else {
            if (typeDeposit == "s") {
                if ((accountBalance + depositAmount) < 100) {
                    clearScreen();
                    showBankAccount();
                    cout<<"\nSaving Accounts require a minimum of $100 balance at all times.\n";
                    inputWithdrawalDeposit();
                }
                else {
                    accountBalance = accountBalance + depositAmount;
                    log.withdrawDeposit(name, "deposited", depositAmount, accountBalance);
                }
            }
            else if (typeDeposit == "g") {
                if ((accountBalance + depositAmount) < 100) {
                    clearScreen();
                    showBankAccount();
                    cout<<"\nGolden Accounts require a minimum of $100 balance at all times.\n";
                    inputWithdrawalDeposit();
                }
                else {
                    accountBalance = accountBalance + depositAmount;
                    log.withdrawDeposit(name, "deposited", depositAmount, accountBalance);
                }
            }
            else if (typeDeposit == "f") {
                if ((accountBalance + depositAmount) < 5000) {
                    clearScreen();
                    showBankAccount();
                    cout<<"\nFixed Deposits require a minimum of $5,000 balance at all times.\n";
                    inputWithdrawalDeposit();
                }
                else {
                    accountBalance = accountBalance + depositAmount;
                    log.withdrawDeposit(name, "deposited", depositAmount, accountBalance);
                }
            }
        }
    }
}

void balanceCheck::showBalance(void) {
    cout<<"\n\nYour account balance is: $"<<accountBalance<<endl<<endl;
}

balanceCheck::balanceCheck(string n, int acc, int a, string d, string g):bankAccount(n, acc, a, d, g) {
	name = n;
    accountNumber = acc;
    age = a;
    typeDeposit = d;
    gender = g;
	depositAmount = 0;
	withdrawalAmount = 0;
	accountBalance = 0;
}

