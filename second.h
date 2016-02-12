#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <conio.h>

using namespace std;

class existing {
    public:
        string username;
        string password;
        string gender;
        int age;
        int accountNumber;
        string accountType;
        int accountBalance;
        int successStatus = 0; // 1 = success
    public:
        void enterCredentials(void);
        void checkCredentials(void);
        Logger log;
};

void existing::enterCredentials(void) {
    clearScreen();
    cout<<"Username: ";
    getline(cin, username);
    fflush(stdin);
    cout<<"Password: ";
    getline(cin, password);
    fflush(stdin);
}

void existing::checkCredentials(void) {
    ifstream accounts ("Accounts.txt");
    string line;
    int x = 0;

    if (accounts.is_open()) {
        while (getline(accounts, line)) {
            if (x == 1) { // Enters this loop for successful username to check password
                if (password == line){
                    x = 2; // Enters this for successful password
                }
                else {
                    x = 0;
                }
            }
            else if (x == 2) {
                x = 3;
                gender = line;
            }
            else if (x == 3) {
                x = 4;
                stringstream(line)>>age;
            }
            else if (x == 4) {
                x = 5;
                stringstream(line)>>accountNumber;
            }
            else if (x == 5) {
                x = 6;
                accountType = line;
                log.login(username);
            }
            else if (x == 6) {
                x = 7;
                stringstream(line)>>accountBalance;
                successStatus = 1;
            }
            if (username == line) { //Enters this upon username match
                x = 1;
            }
        }
        accounts.close();
        if (x == 0){
            clearScreen();
            cout<<"Login unsuccessful, invalid username or password. Please try again.\n";
            cout<<"Press any key to continue...";
            getch(); // From <conio.h>
            enterCredentials();
        }
    }
}

class saveAccount {
    protected:
        string username;
        string password;
        string gender;
        int age;
        int accountNumber;
        string accountType;
        int balance;
    public:
        saveAccount(string, string, string, int, int, string, int);
        void saveNew(void);
        void saveExisting(void);
};

saveAccount::saveAccount(string a, string b, string c, int x, int y, string d, int z) {
    username = a;
    password = b;
    gender = c;
    age = x;
    accountNumber = y;
    accountType = d;
    balance = z;
}

void saveAccount::saveNew(void) {
    ofstream accounts;
    accounts.open("Accounts.txt", ios_base::app);
    accounts<<"\n"<<username<<"\n";
    accounts<<password<<"\n";
    accounts<<gender<<"\n";
    accounts<<age<<"\n";
    accounts<<accountNumber<<"\n";
    accounts<<accountType<<"\n";
    accounts<<balance<<"\n";

    int num;
    string line;
    ifstream accountNum ("NumOfAccs.txt");
    if (accountNum.is_open()) {
        while (getline(accountNum, line)){
            stringstream(line)>>num;
        }
        accountNum.close();
    }
    num++;
    ofstream accountsNum2 ("NumOfAccs.txt");
    if (accountsNum2.is_open()) {
        accountsNum2<<num;
        accountsNum2.close();
    }
}

void saveAccount::saveExisting(void) {
    ifstream filein("Accounts.txt"); //File to read from
    ofstream fileout("test.txt"); //Temporary file
    string temp;
    int x = 0;

    while (filein>>temp) {
        if (x > 0){
            if (x == 1){
                ostringstream tempStr;
                tempStr<<balance;
                temp = tempStr.str();
            }
            x--;
        }
        if (temp == username) {
            x = 6;
        }
        temp += "\n";
        fileout<<temp;
    }
    filein.close();
    fileout.close();
    remove("Accounts.txt");
    rename("test.txt", "Accounts.txt");
}

