#include "main.h"
#include "second.h"
#include <conio.h>
#include <limits>

using namespace std;

int main (){

	string name;
	string pass; //password
	int age = 0, accountNumber;
	string gender;
	string typeDeposit;
	int x = 0;

    Logger log;

	string accountChoice = "a";

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
    cout<<"                           Account Management System                            "<<endl;

    cout<<"Press any key to continue...";
    getch(); // From <conio.h>
    clearScreen();

    cout<<"Do you have an existing account or would you like to open a new account?\n\n[E] - Existing\n[N] - New\n\n";
    cin>>accountChoice;
    while (accountChoice != "e" && accountChoice != "E" && accountChoice != "n" && accountChoice != "N") {
        clearScreen();
        cout<<"Invalid option! Please reselect:\n\n";
        cout<<"Do you have an existing account or would you like to open a new account?\n\n[E] - Existing\n[N] - New\n\n";
        cin>>accountChoice;
    }
    fflush(stdin);

    if (accountChoice == "e" || accountChoice == "E") {
        existing Existing_Account;
        Existing_Account.enterCredentials();
        while (Existing_Account.successStatus == 0) {
            Existing_Account.checkCredentials();
        }

        name = Existing_Account.username;
        accountNumber = Existing_Account.accountNumber;
        age = Existing_Account.age;
        typeDeposit = Existing_Account.accountType;
        gender = Existing_Account.gender;

        balanceCheck Account(name, accountNumber, age, typeDeposit, gender);  //creating an object of child
        Account.accountBalance = Existing_Account.accountBalance;

        Account.showBankAccount();
        Account.inputWithdrawalDeposit();
        Account.showBalance();
        saveAccount saveAcc(name, pass, gender, age, accountNumber, Account.typeDeposit, Account.accountBalance);
        saveAcc.saveExisting();
    }
    else if (accountChoice == "n" || accountChoice == "N") {
        clearScreen();
        cout<<"Please enter your name: ";
        getline(cin, name);
        fflush(stdin);
        cout<<"Please enter your password: ";
        getline(cin, pass);
        fflush(stdin);
        cout<<"Please enter your age: ";
        cin>>age;
        while(!cin || !(age > 0)) {
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
            clearScreen();
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

        ifstream NumOfAccounts ("NumOfAccs.txt");
        string line;
        int x = 0;

        if (NumOfAccounts.is_open()) {
            while (getline(NumOfAccounts, line)) {
                stringstream(line)>>accountNumber;
            }
            NumOfAccounts.close();
            accountNumber++;
        }

        log.newAccount(name, typeDeposit);

        balanceCheck Account(name, accountNumber, age, typeDeposit, gender);  //creating an object of child
        Account.checkGoldenAccountValidity();
        Account.showBankAccount();
        Account.inputWithdrawalDeposit();
        Account.showBalance();
        saveAccount saveAcc(name, pass, gender, age, accountNumber, Account.typeDeposit, Account.accountBalance);
        saveAcc.saveNew();
    }

    log.logout(name);
	return 0;
}
