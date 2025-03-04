//Sujay Sundar

/*
  rec03.cpp
  2024 Fall
 */

// Provided
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// Task 1
// Define an Account struct
struct Account {
     string name;
     int accountNumber;
};

// Task 2
// Define an Account class (use a different name than in Task 1)
class AccountClass {
     friend ostream& operator<<(ostream& os, const AccountClass& ac);
public:
     AccountClass(const string& name, int accountNumber) : name(name), accountNumber(accountNumber) {}
     const string& getAccountName() const {return name;}
     int getAccountNumber() const {return accountNumber;}
private:
     string name;
     int accountNumber;
};

ostream& operator<<(ostream& os, const AccountClass& ac) {
     cout << ac.getAccountName() << ac.getAccountNumber() << endl;
     return os;
     ac.name;
}



// Task 3
// Define another Account class (use a different name than in Task
// 1&2) and a Transaction class. The Transaction class is to be
// defined outside of the Account class, i.e. it is not "nested".
class TransactionClass {
     friend ostream& operator<<(ostream& os, const TransactionClass& tc);
public:
     TransactionClass(const string& transactionStatus, int amount) : transactionStatus(transactionStatus), amount(amount) {}
private:
     string transactionStatus;
     int amount;
};

ostream& operator<<(ostream& os, const TransactionClass& tc) {
     os << "\t" << tc.transactionStatus << " " << tc.amount;
     return os;
}


class AccountClass2 {
     friend ostream& operator<<(ostream& os, const AccountClass2& ac2);
public:
     AccountClass2(const string& accountName, int accountNumber) : accountName(accountName), accountNumber(accountNumber), balance(0) {}
     const string& getAccountName() const {return accountName;}
     int getAccountNumber() const {return accountNumber;}
     void deposit(int amount) {
          balance = balance + amount;
          TransactionClass transaction("deposit", amount);
          history.push_back(transaction);
     }
     void withdrawal(int amount) {
          if (balance >= amount) {
               balance = balance - amount;
               TransactionClass transaction("withdrawal", amount);
               history.push_back(transaction);
          } else {
               cout << "Account# " << accountNumber << " has only " << balance << ". Insufficient for withdrawal of " << amount << endl;
          }
     }
     //const string& getAccountName() const {return transactionStatus;}
     //int getAccountNumber() const {return amount;}
private:
     vector<TransactionClass> history;
     int balance;
     string accountName;
     int accountNumber;
};

ostream& operator<<(ostream& os, const AccountClass2& ac2) {
     os << ac2.accountName << "\t" << ac2.accountNumber;
     for (size_t i = 0; i < ac2.history.size(); ++i) {
          os << ac2.history[i] << endl; // Print each transaction
     }
     return os;
}

// Task 4
// Define yet another Account class, this time with a nested public
// Transaction class. Again use a different name for the Account class
// than in the previous Tasks. Note that it is NOT necessary to rename
// the Transaction class, since it is nested.

class AccountClass3 {
public:
     class TransactionClass {
          friend ostream& operator<<(ostream& os, const TransactionClass& tc);
     public:
          TransactionClass(const string& transactionStatus, int amount) : transactionStatus(transactionStatus), amount(amount) {}
     private:
          string transactionStatus;
          int amount;
     };

     AccountClass3(const string& accountName, int accountNumber) : accountName(accountName), accountNumber(accountNumber), balance(0) {}

     void deposit(int amount) {
          balance = balance + amount;
          TransactionClass transaction_class("deposit", amount);
          history.push_back(transaction_class);
     }

     void withdrawal(int amount) {
          if (balance >= amount) {
               balance = balance - amount;
               TransactionClass transaction_class("withdrawal", amount);
               history.push_back(transaction_class);
          } else {
               cout << "Account# " << accountNumber << " has only " << balance << ". Insufficient for withdrawal of " << amount << endl;
          }
     }

     friend ostream& operator<<(ostream& os, const AccountClass3& ac3);

     vector<TransactionClass> history;
     int balance;
     string accountName;
     int accountNumber;
};

ostream operator<<(ostream& os, const AccountClass3 ac3) {
     os << ac3.accountName << "\t" << ac3.accountNumber;
     for (size_t i = 0; i < ac3.history.size(); ++i) {
          os << ac3.history[i] << endl; // Print each transaction
     }
}


// Task 5
// Same as Task 4, but make the Transaction nested class private.
// Yes, the Account class needs a new name but, again, the Transaction
// class does not.


int main() {

    // Task 1: account as struct
    //      1a
    cout << "Task1a:\n"
         << "Filling vector of struct objects, define a local struct instance\n"
         << "and set fields explicitly:\n";
     ifstream ifs;
     ifs.open("accounts.txt");
     if (!ifs) {
          cerr << "failed to open accounts.txt";
          exit(1);
     }
     vector<Account> accounts;
     Account a;
     string name;
     int accountNumber;
     while (ifs >> name >> accountNumber) {
          a.name = name;
          a.accountNumber = accountNumber;
          accounts.push_back(a);
     }
     ifs.close();
     for (size_t i = 0; i < accounts.size(); ++i) {
          cout << accounts[i].name << accounts[i].accountNumber << endl;
     }

    //      1b
    cout << "Task1b:\n"
         << "Filling vector of struct objects, using {} initialization:\n";
     accounts.clear();
     ifs.open("accounts.txt");
     if (!ifs) {
          cerr << "failed to open accounts.txt";
          exit(1);
     }
     while (ifs >> name >> accountNumber) {
          Account accountOne{name, accountNumber};
          accounts.push_back(accountOne);
     }
     ifs.close();
     for (size_t i = 0; i < accounts.size(); ++i) {
          cout << accounts[i].name << accounts[i].accountNumber << endl;
     }



    //==================================
    // Task 2: account as class

    //      2a
    cout << "==============\n";
    cout << "\nTask2a:"
         << "\nFilling vector of class objects, using local class object:\n";
     accounts.clear();
     ifs.open("accounts.txt");
     if (!ifs) {
          cerr << "failed to open accounts.txt";
          exit(1);
     }
     while (ifs >> name >> accountNumber) {
          Account accountOne{name, accountNumber};
          accounts.push_back(accountOne);
     }
     ifs.close();
     for (size_t i = 0; i < accounts.size(); ++i) {
          cout << accounts[i].name << accounts[i].accountNumber << endl;
     }

    cout << "\nTask2b:\n";
    cout << "output using output operator with getters\n";
     ifs.open("accounts.txt");
     vector<AccountClass> account_classes;
     while (ifs >> name >> accountNumber) {
          account_classes.push_back(AccountClass(name, accountNumber));
     }
     for (const AccountClass& a : account_classes) {
          cout << a.getAccountName() << a.getAccountNumber() << endl;
     }

     ifs.close();

    cout << "\nTask2c:\n"
         << "output using output operator as friend without getters\n";
     ifs.open("accounts.txt");
     account_classes.clear();
     while (ifs >> name >> accountNumber) {
          account_classes.push_back(AccountClass(name, accountNumber));
     }
     for (const AccountClass& a : account_classes) {
          cout << a.getAccountName() << a.getAccountNumber() << endl;
     }
     ifs.close();

    cout << "\nTask2d:\n"
         << "Filling vector of class objects, using temporary class object:\n";
     ifs.open("accounts.txt");
     account_classes.clear();
     while (ifs >> name >> accountNumber) {
          AccountClass ac(name, accountNumber);
          account_classes.push_back(ac);
     }
     for (const AccountClass& ac : account_classes) {
          cout << ac.getAccountName() << ac.getAccountNumber() << endl;
     }

     ifs.close();


    cout << "\nTask2e:\n"
         << "Filling vector of class objects, using emplace_back:\n";
     ifs.open("accounts.txt");
     account_classes.clear();
     while (ifs >> name >> accountNumber) {
          AccountClass ac(name, accountNumber);
          account_classes.emplace_back(ac);
     }
     for (const AccountClass& ac : account_classes) {
          cout << ac.getAccountName() << ac.getAccountNumber() << endl;
     }

     ifs.close();

    cout << "==============\n"
         << "\nTask 3:\nAccounts and Transaction:\n";
     string first_word;
     ifs.open("transactions.txt");
     vector<AccountClass2> Accounts;
     while (ifs >> first_word) {
          if (first_word == "Account") {
               string accountName;
               int accountNumber;

               ifs >> accountName >> accountNumber;


               AccountClass2 account(accountName, accountNumber);
               Accounts.push_back(account);
          } if (first_word == "Deposit") {
               int accountNumber;
               int deposit_amount;

               ifs >> accountNumber >> deposit_amount;


               for (size_t i = 0; i < Accounts.size(); ++i) {
                    if (Accounts[i].getAccountNumber() == accountNumber) {
                         Accounts[i].deposit(deposit_amount);
                    }
               }

          } if (first_word == "Withdraw") {
               int accountNumber;
               int withdrawal_amount;

               ifs >> accountNumber >> withdrawal_amount;

               for (size_t i = 0; i < Accounts.size(); ++i) {
                    if (Accounts[i].getAccountNumber() == accountNumber) {
                         Accounts[i].withdrawal(withdrawal_amount);
                    }
               }
          }
     }

     for (size_t i = 0; i < Accounts.size(); ++i) {
          cout << Accounts[i] << endl;
     }

     ifs.close();


    cout << "==============\n"
         << "\nTask 4:\nTransaction nested in public section of Account:\n";

     string first_word1;
     ifs.open("transactions.txt");
     vector<AccountClass3> Accounts1;
     while (ifs >> first_word) {
          if (first_word == "Account") {
               string accountName;
               int accountNumber;

               ifs >> accountName >> accountNumber;


               AccountClass3 account(accountName, accountNumber);
               Accounts1.push_back(account);
          } if (first_word == "Deposit") {
               int accountNumber;
               int deposit_amount;

               ifs >> accountNumber >> deposit_amount;


               for (size_t i = 0; i < Accounts1.size(); ++i) {
                    if (Accounts1[i].accountNumber == accountNumber) {
                         Accounts1[i].deposit(deposit_amount);
                    }
               }

          } if (first_word == "Withdraw") {
               int accountNumber;
               int withdrawal_amount;

               ifs >> accountNumber >> withdrawal_amount;

               for (size_t i = 0; i < Accounts1.size(); ++i) {
                    if (Accounts1[i].accountNumber == accountNumber) {
                         Accounts1[i].withdrawal(withdrawal_amount);
                    }
               }
          }
     }

     for (size_t i = 0; i < Accounts1.size(); ++i) {
          cout << Accounts1[i] << endl;
     }

     ifs.close();



    cout << "==============\n"
         << "\nTask 5:\nTransaction nested in private section of Account:\n";


}

