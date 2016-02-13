/*
 * A simple
 * Bank Account Management System
 *
 * Done by:
 *
 * Ajay Pillay (1423921)
 * Dinesdkumar Jaya Kumaran (1423567)
 * Mun Kar Kin (1454246)
 *
 * For the module ET101M: Advanced Computer Programming
 * School of Electrical and Electronic Engineering
 * Singapore Polytechnic
 *
 *
 */

#include "accountHandlersAndLogging.h"
#include "fileIO.h"

using namespace std;

int main (){

    int timeOfCreation = time(0); //Gets the current timestamp

	string name; // Username
	string pass; // Password
	string quit; // Check if user wants to quit
	int age = 0, accountNumber; // Age of user, account number is assigned
	string gender; // Gender of user
	string typeDeposit; // Type of deposit, "f" - fixed deposit, "g" - golden account, "s" - saving account
	string accountChoice = "a"; // Account choice "e" - existing account (read from Accounts.txt), "n" - new account
	int fixedDepositYears; // Years for fixed deposit, 1, 2 or 3

    Logger log; // Logger class from accountHandlers.h

    while (quit != "Q" && quit != "q") { // Contained inside while loop to allow user to restart after transaction
        clearScreen();
        cout<<"================================================================================"<<endl;
        cout<<"     \\`\\/\\/\\/`/                                                  \\`\\/\\/\\/`/"<<endl;
        cout<<"      )======(                                                    )======("<<endl;
        cout<<"    .'        '.                                                .'        '."<<endl;
        cout<<"   /    _||__   \\                                              /    _||__   \\"<<endl;
        cout<<"  /    (_||_     \\     Welcome to the Grand Central Bank,     /    (_||_     \\"<<endl;
        cout<<" |     __||_)     |     where your money is our concern.     |     __||_)     |"<<endl;
        cout<<" |       ||       |                                          |       ||       |"<<endl;
        cout<<" '.              .'                                          '.              .'"<<endl;
        cout<<"   '------------'                                              '------------'"<<endl<<endl;
        cout<<"================================================================================"<<endl;
        cout<<"                           Account Management System                            \n\n\n"<<endl;

        cout<<"Press any key to continue...";
        getch(); // From <conio.h>
        clearScreen();

        cout<<"Do you have an existing account or would you like to open a new account?\n\n[E] - Existing\n[N] - New\n\n";
        cin>>accountChoice;
        while (accountChoice != "e" && accountChoice != "E" && accountChoice != "n" && accountChoice != "N") { // Checking the input for accountChoice
            clearScreen();
            cout<<"Invalid option! Please reselect:\n\n";
            cout<<"Do you have an existing account or would you like to open a new account?\n\n[E] - Existing\n[N] - New\n\n";
            cin>>accountChoice;
        }
        fflush(stdin);

        if (accountChoice == "e" || accountChoice == "E") { // if there is an existing account
            existing Existing_Account; // Class from fileIOandlogging.h
            Existing_Account.enterCredentials(); // Enter the user credentials (username and password)
            while (Existing_Account.successStatus == 0) {
                Existing_Account.checkCredentials(); // Keeps asking until valid credentials entered
            }

            name = Existing_Account.username; // Returning variables from the object to main.cpp
            accountNumber = Existing_Account.accountNumber;
            age = Existing_Account.age;
            typeDeposit = Existing_Account.accountType;
            gender = Existing_Account.gender;
            timeOfCreation = Existing_Account.timeOfCreation;

            balanceCheck Account(name, accountNumber, age, typeDeposit, gender, timeOfCreation);  // Creating an object of a child class
            Account.accountBalance = Existing_Account.accountBalance;
            if (typeDeposit == "f") Account.yearsFixedDeposit = Existing_Account.fixedDepositYears; // If a fixed deposit is used

            Account.showBankAccount();
            Account.inputWithdrawalDeposit();
            Account.showBalance();
            saveAccount saveAcc(name, pass, gender, age, accountNumber, Account.typeDeposit, Account.accountBalance, timeOfCreation);
            saveAcc.saveExisting();
        }
        else if (accountChoice == "n" || accountChoice == "N") { // If user creates a new account
            clearScreen();
            cout<<"Please enter your name: ";
            getline(cin, name);
            fflush(stdin);
            cout<<"Please enter your password: ";
            getline(cin, pass);
            fflush(stdin);
            cout<<"Please enter your age: ";
            cin>>age;
            while(!cin || !(age > 0)) { // Error checking for every single input
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                clearScreen();
                cout<<"Please enter your username: "<<name;
                cout<<"\nPlease enter your password: "<<pass<<"\n\n";
                cout<<"Invalid age! Please reenter:\n\n";
                cout<<"Please enter your age: ";
                cin>>age;
            }
            cout<<"Please enter your gender (M/F): ";
            cin>>gender;
            while (gender != "M" && gender != "m" && gender != "F" && gender != "f" ){
                clearScreen();
                cout<<"Please enter your username: "<<name;
                cout<<"\nPlease enter your password: "<<pass;
                cout<<"\nPlease enter your age: "<<age<<"\n\n";
                cout<<"Invalid gender! Please reenter:\n\n";
                cout<<"Please enter your gender (M/F): ";
                cin>>gender;
            }

            cout<<endl<<"Please enter the type of account you wish to open: "<<endl<<endl;
            cout<<"[S] - Saving Account\n[G] - Golden Account\n[F] - Fixed Deposit"<<endl<<endl;
            cin>>typeDeposit;

            while (typeDeposit != "s" && typeDeposit != "S" && typeDeposit != "g" && typeDeposit != "G" && typeDeposit != "f" && typeDeposit != "F"){
                clearScreen(); // Even more error checking here
                cout<<"Please enter your username: "<<name;
                cout<<"\nPlease enter your password: "<<pass;
                cout<<"\nPlease enter your age: "<<age;
                cout<<"\nPlease enter your gender (M/F): "<<gender<<"\n\n";
                cout<<"Invalid account type! Please reenter:\n\n";
                cout<<endl<<"Please enter the type of account you wish to open: "<<endl<<endl;
                cout<<"[S] - Saving Account\n[G] - Golden Account\n[F] - Fixed Deposit"<<endl<<endl;
                cin>>typeDeposit;
            }

            typeDeposit = tolower(typeDeposit[0]);

            if (typeDeposit == "f") {
                cout<<"Please enter the maturity date (1, 2 or 3 years): ";
                cin>>fixedDepositYears;
                while(!cin || !(fixedDepositYears > 0 && fixedDepositYears < 4)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    clearScreen();
                    cout<<"Please enter your username: "<<name;
                    cout<<"\nPlease enter your password: "<<pass;
                    cout<<"\nPlease enter your age: "<<age;
                    cout<<"\nPlease enter your gender (M/F): "<<gender;
                    cout<<endl<<"Please enter the type of account you wish to open: "<<endl<<endl;
                    cout<<"[S] - Saving Account\n[G] - Golden Account\n[F] - Fixed Deposit"<<endl<<endl<<typeDeposit<<"\n\n";
                    cout<<"Invalid number of years! Please reenter:\n\n";
                    cout<<"Please enter the maturity date (1, 2 or 3 years): ";
                    cin>>fixedDepositYears;
                }
            }

            ifstream NumOfAccounts ("NumOfAccs.txt");
            string line; // Increment the number in NumOfAccs.txt, this is for the new accounts' number

            if (NumOfAccounts.is_open()) {
                while (getline(NumOfAccounts, line)) {
                    stringstream(line)>>accountNumber;
                }
                NumOfAccounts.close();
                accountNumber++;
            }

            log.newAccount(name, typeDeposit); // Logging in Log.txt
            timeOfCreation = time(0);
            balanceCheck Account(name, accountNumber, age, typeDeposit, gender, timeOfCreation);  //creating an object of child
            if (typeDeposit == "f") Account.yearsFixedDeposit = fixedDepositYears;
            Account.checkGoldenAccountValidity();
            Account.showBankAccount();
            Account.inputWithdrawalDeposit();
            Account.showBalance();
            saveAccount saveAcc(name, pass, gender, age, accountNumber, Account.typeDeposit, Account.accountBalance, timeOfCreation);
            if (typeDeposit == "f") saveAcc.fixedDepositYears = fixedDepositYears;
            saveAcc.saveNew();
        }
        log.logout(name); // Logging
        cout<<"\n\n[Q]uit or [R]estart?";
        cin>>quit;
        while (quit != "R" && quit != "r" && quit != "Q" && quit != "q") {
            clearScreen();
            cout<<"\n\nInvalid option entered! Please reselect: \n\n";
            cout<<"\n\n[Q]uit or [R]estart?";
            cin>>quit;
        }
    }
	return 0;
}
