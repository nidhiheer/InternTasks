#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Enum for account types
enum class AccountType { SAVINGS, CHECKING };

// Base class for accounts
class Account {
protected:
    string accountNumber;
    double balance;
    AccountType type;

public:
    Account(string accountNumber, double balance, AccountType type)
        : accountNumber(accountNumber), balance(balance), type(type) {}

    string getAccountNumber() { return accountNumber; }
    double getBalance() { return balance; }
    AccountType getType() { return type; }

    void deposit(double amount) { balance += amount; }
    bool withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            return true;
        }
        return false;
    }
};

// Savings account class
class SavingsAccount : public Account {
public:
    SavingsAccount(string accountNumber, double balance)
        : Account(accountNumber, balance, AccountType::SAVINGS) {}

    void addInterest(double interestRate) {
        balance += balance * interestRate / 100;
    }
};

// Checking account class
class CheckingAccount : public Account {
public:
    CheckingAccount(string accountNumber, double balance)
        : Account(accountNumber, balance, AccountType::CHECKING) {}

    void setOverdraftLimit(double limit) {
        // Implement overdraft limit logic
    }
};

// Bank class
class Bank {
private:
    vector<Account*> accounts;

public:
    void openAccount(string accountNumber, double balance, AccountType type) {
        if (type == AccountType::SAVINGS) {
            accounts.push_back(new SavingsAccount(accountNumber, balance));
        } else if (type == AccountType::CHECKING) {
            accounts.push_back(new CheckingAccount(accountNumber, balance));
        }
    }

    Account* getAccount(string accountNumber) {
        for (Account* account : accounts) {
            if (account->getAccountNumber() == accountNumber) {
                return account;
            }
        }
        return nullptr;
    }

    void deposit(string accountNumber, double amount) {
        Account* account = getAccount(accountNumber);
        if (account) {
            account->deposit(amount);
        }
    }

    bool withdraw(string accountNumber, double amount) {
        Account* account = getAccount(accountNumber);
        if (account) {
            return account->withdraw(amount);
        }
        return false;
    }

    void displayAccountInfo(string accountNumber) {
        Account* account = getAccount(accountNumber);
        if (account) {
            cout << "Account Number: " << account->getAccountNumber() << endl;
            cout << "Balance: " << account->getBalance() << endl;
            cout << "Type: " << (account->getType() == AccountType::SAVINGS ? "Savings" : "Checking") << endl;
        }
    }
};

int main() {
    Bank bank;

    int choice;
    string accountNumber;
    double balance;
    AccountType type;

    while (true) {
        cout << "1. Open Account" << endl;
        cout << "2. Deposit" << endl;
        cout << "3. Withdraw" << endl;
        cout << "4. Display Account Info" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter account number: ";
                cin >> accountNumber;
                cout << "Enter initial balance: ";
                cin >> balance;
                cout << "Enter account type (0 for Savings, 1 for Checking): ";
                int typeChoice;
                cin >> typeChoice;
                type = typeChoice == 0 ? AccountType::SAVINGS : AccountType::CHECKING;
                bank.openAccount(accountNumber, balance, type);
                break;
            case 2:
                cout << "Enter account number: ";
                cin >> accountNumber;
                cout << "Enter amount to deposit: ";
                double depositAmount;
                cin >> depositAmount;
                bank.deposit(accountNumber, depositAmount);
                break;
            case 3:
                cout << "Enter account number: ";
                cin >> accountNumber;
                cout << "Enter amount to withdraw: ";
                double withdrawAmount;
                cin >> withdrawAmount;
                if (bank.withdraw(accountNumber, withdrawAmount)) {
                    cout << "Withdrawal successful." << endl;
                } else {
                    cout << "Insufficient balance." << endl;
                }
                break;
                        case 4:
                cout << "Enter account number: ";
                cin >> accountNumber;
                bank.displayAccountInfo(accountNumber);
                break;
            case 5:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}   


          