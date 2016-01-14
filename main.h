class bankAccount {
private: // may need to be changed to protected later 
  string name;
  int accountNumber;
  int age;
  char deposit; 
  char gender; // m / M / f / F 
  //saving account = s ;
  //golden account = g ;
  //fixed deposit = f ;
  
public:
  bankAccount (); // initialize private/protected data members
  void showBankAccount (void);
  
};
  
  void bankAccount :: bankAccount (string n, int acc, int a, char d, char g){
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


  
  
