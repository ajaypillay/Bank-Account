#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <limits>
#include <cmath>

using namespace std;

void clearScreen() { // Function to clear the terminal screen
    int x = 0;
    while (x < 25) {
        cout<<"\n";
        x++;
    }
    return;
}

string timeNow() { // Returns the current timestamp, local to the computer
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
    buf[10] = ' ';
    return buf;
}

class Logger { // This is the logging class which takes care of all logging features
    public:
        void withdrawDeposit(string, string, int, double); // Logs all withdrawals and deposits
        void login(string); // Logs logging in
        void logout(string); // Logs logging out
        void newAccount(string, string); // Logs creation of a new account
};

void Logger::withdrawDeposit(string a, string b, int c, double d){
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

class bankAccount { // Parent class of balanceCheck, this class deals with all bank account functions
    public:
        string typeDeposit; // s - saving account, g - golden account, f - fixed deposit
    protected:
        string name;
        int accountNumber;
        int age;
        string gender; // m / M / f / F
    public:
        bankAccount(string, int, int, string, string); // initialize protected data members
        void showBankAccount(void); // Shows bank account info
        void checkGoldenAccountValidity(void); // Checks age of golden account creators since they need to be >55 years old
        void reselectAccount(void); // Offers to reselect account if can't create golden account
        Logger log; // Logger object to log all events
};

void bankAccount::reselectAccount(void) {
    clearScreen();
    showBankAccount();
	cout<<"\nThe Golden Account is only for depositors aged 55 years old or above.\nPlease reselect your option."<<endl;
	cout<<"\nEnter [S] for Saving Account or [F] for Fixed Deposit: ";
	cin>>typeDeposit;
	while (typeDeposit != "s" && typeDeposit != "S" && typeDeposit != "f" && typeDeposit != "F"){
        showBankAccount(); // Error checking
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
            reselectAccount();
        }
    }
}

bankAccount::bankAccount (string n, int acc, int a, string d, string g) { // Constructor
    name = n;
    accountNumber = acc;
    age = a;
    typeDeposit = d;
    gender = g;
}

void bankAccount::showBankAccount(void) { // Shows bank account info
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
        int yearsFixedDeposit;
    private:
        string modeBalance; // d - deposit, w - withdraw
        double depositAmount, withdrawalAmount;
        double amountWithdrawal;
        double amountDeposit;
        int timeOfCreation;
        double interestRate;
        double temp;
    public:
        balanceCheck(string, int, int, string, string, int);
        void inputWithdrawalDeposit(void); // Handles all transaction scenarios
        void showBalance(void); // Shows the balance remaining for any account
        void interestCalc (void); // Calculates interest based on timestamps
        Logger log; // Logger object
};

void balanceCheck::interestCalc(void) {
    // Every 20 seconds is treated as a year
    // Simple Interest = PRT
    int x = time(0);
    if (typeDeposit == "s") {
        accountBalance = accountBalance + accountBalance*0.0025*floor((x-timeOfCreation)/20);
        interestRate = 0.25;
    }
    else if (typeDeposit == "g") {
        if (accountBalance < 50000) {
            accountBalance = accountBalance + accountBalance*0.00375*floor((x-timeOfCreation)/20);
            interestRate = 0.375;
        }
        else if (accountBalance >= 50000) {
            accountBalance = accountBalance + accountBalance*0.005*floor((x-timeOfCreation)/20);
            interestRate = 0.5;
        }
    }
    else if (typeDeposit == "f") {
        temp = accountBalance;
        if (yearsFixedDeposit == 1) {
            accountBalance = accountBalance + accountBalance*0.0055*floor((x-timeOfCreation)/20);
            interestRate = 0.55;
        }
        else if (yearsFixedDeposit == 2){
            accountBalance = accountBalance + accountBalance*0.007*floor((x-timeOfCreation)/20);
            interestRate = 0.7;
        }
        else if (yearsFixedDeposit == 3){
            accountBalance = accountBalance + accountBalance*0.008*floor((x-timeOfCreation)/20);
            interestRate = 0.8;
        }
    }
}

void balanceCheck::inputWithdrawalDeposit(void) {
    if (accountBalance != 0) { // Calculate interest if account exists, new accounts will have $0 hence no need to calc interest
        interestCalc();
    }
    if (typeDeposit == "s") { // This if-else if chunk deals with assigning interest rates based on type of account created
        interestRate = 0.25;
    }
    else if (typeDeposit == "g") {
        if (accountBalance < 50000) {
            interestRate = 0.375;
        }
        else if (accountBalance >= 50000) {
            interestRate = 0.5;
        }
    }
    else if (typeDeposit == "f") {
        if (yearsFixedDeposit == 1) {
            interestRate = 0.55;
        }
        else if (yearsFixedDeposit == 2){
            interestRate = 0.7;
        }
        else if (yearsFixedDeposit == 3){
            interestRate = 0.8;
        }
    }
    cout<<"Interest rate: "<<interestRate<<"%"<<endl;
    cout<<"Balance: $"<<accountBalance<<endl;
    cout<<endl<<"Please select the mode - [W]ithdrawal or [D]eposit: ";
    cin>>modeBalance;
    while (modeBalance != "w" && modeBalance != "W" && modeBalance != "d" && modeBalance != "D"){
        clearScreen(); // Reselect until proper mode is selected
        showBankAccount();
        cout<<"Balance: $"<<accountBalance<<endl;
        cout<<"\nInvalid option! Please reselect:\n\n";
        cout<<endl<<"Please select the mode - [W]ithdrawal or [D]eposit: ";
        cin>>modeBalance;
    }

    if (modeBalance == "D") modeBalance = "d";
    else if(modeBalance == "W") modeBalance = "w";

	if (accountBalance <= 0 && modeBalance == "w") {
        clearScreen(); // If user tries to withdraw from an account containing $0
        showBankAccount();
		cout<<endl<<"!!! Warning !!!"<<endl<<endl;
		cout<<"Insufficient funds in account."<<endl;
		inputWithdrawalDeposit();
	}

    else if (modeBalance == "w") {
        cout<<"Please enter the amount you wish to withdraw: $";
        cin>>withdrawalAmount;
        while(!cin || !(withdrawalAmount > 0)) {
            cin.clear(); // Checking the withdrawalAmount variable such that it actually contains a positive integer
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
            clearScreen(); // If user tries to withdraw more than what's in the account
            showBankAccount();
            cout<<"\n\nYou cannot withdraw more money than available in your account. Operation terminating.\n"<<endl;
            withdrawalAmount = 0;
            inputWithdrawalDeposit();
        }
        else {
            if (typeDeposit == "s") {
                if ((accountBalance - withdrawalAmount) < 100) {
                    clearScreen(); // If a user tries to withdraw money from the account such that there is less than the minimum balance required
                    showBankAccount(); // In this case, min balance is $100
                    cout<<"\nSaving Accounts require a minimum of $100 balance at all times.\n";
                    inputWithdrawalDeposit();
                }
                else { // Successful withdrawal
                    accountBalance = accountBalance - withdrawalAmount;
                    log.withdrawDeposit(name, "withdrawn", withdrawalAmount, accountBalance);
                }
            }
            else if (typeDeposit == "g") { // Same as above, but for golden accounts
                if ((accountBalance - withdrawalAmount) < 100) {
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
                if ((accountBalance - withdrawalAmount) < 5000) {
                    clearScreen(); // Fixed deposits require a minimum of $5000 in the account
                    showBankAccount();
                    cout<<"\nFixed Deposits require a minimum of $5,000 balance at all times.\n";
                    inputWithdrawalDeposit();
                }
                else if ((time(0) - timeOfCreation)/20 < yearsFixedDeposit*20) {
                    string conf; // If the user tries to withdraw before the maturity date, penalty is imposed
                    cout<<"\nWarning: You are trying to withdraw before your maturity date, a penalty of $"<<yearsFixedDeposit*50<<" will be imposed.\n";
                    cout<<"Confirm? Y/N: ";
                    cin>>conf;
                    if (conf == "y" || conf == "Y") { // Interest is recalculated here using 0.25%
                        accountBalance = (temp + temp*0.0025*((time(0)-timeOfCreation)/20)) - withdrawalAmount;
                        log.withdrawDeposit(name, "withdrawn", withdrawalAmount, accountBalance);
                    }
                    else { // Go back to withdrawal/deposit screen
                        clearScreen();
                        showBankAccount();
                        inputWithdrawalDeposit();
                    }
                }
                else { // Successful withdrawal for fixed deposit
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
            cin.clear(); // Error checking for depositAmount variable, must be a positive integer
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            clearScreen();
            showBankAccount();
            cout<<"Balance: $"<<accountBalance<<endl;
            cout<<endl<<"Please select the mode - [W]ithdrawal or [D]eposit: "<<modeBalance<<"\n\n";
            cout<<"Invalid amount! Please reenter:\n\n";
            cout<<"Please enter the amount you wish to deposit: $";
            cin>>depositAmount;
        }
        if (typeDeposit == "s") { // Deposit for saving account
            if ((accountBalance + depositAmount) < 100) {
                clearScreen(); // If after a deposit, amount is less than minimum of $100
                showBankAccount();
                cout<<"\nSaving Accounts require a minimum of $100 balance at all times.\n";
                inputWithdrawalDeposit();
            }
            else { // Successful deposit
                accountBalance = accountBalance + depositAmount;
                log.withdrawDeposit(name, "deposited", depositAmount, accountBalance);
            }
        }
        else if (typeDeposit == "g") { // Same as above, but for golden accounts
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
        else if (typeDeposit == "f") { // Fixed accounts require a minimum of $5000 to start
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

void balanceCheck::showBalance(void) { // Shows the account balance
    cout<<"\n\nYour account balance is: $"<<accountBalance<<endl<<endl;
}

balanceCheck::balanceCheck(string n, int acc, int a, string d, string g, int u):bankAccount(n, acc, a, d, g) {
	name = n; // Constructor
    accountNumber = acc;
    age = a;
    typeDeposit = d;
    gender = g;
    timeOfCreation = u;
	depositAmount = 0;
	withdrawalAmount = 0;
	accountBalance = 0;
}

