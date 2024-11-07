#include <iostream>
#include <string>
using namespace std;

class Account {
public:
    string accountNumber;
    string accountHolderName;
    float balance;
    bool isActive; // To track if an account is active or not

    Account(string accNum = "", string accHolder = "", float bal = 0.0)
        : accountNumber(accNum), accountHolderName(accHolder), balance(bal), isActive(true) {} // Initialize isActive to true
};

class Bank {
private:
    static const int MAX_ACCOUNTS = 100; // Maximum number of accounts
    Account accounts[MAX_ACCOUNTS]; // Array of Account objects
    int count; // Current number of accounts

public:
    Bank() : count(0) {} // Initialize count to 0

    void addAccount(const Account& account) {
        if (count < MAX_ACCOUNTS) {
            accounts[count] = account; // Add the account to the array
            count++;
            cout << "Account added successfully!" << endl;
        } else {
            cout << "Bank is full, cannot add more accounts." << endl;
        }
    }

    void displayAccounts() {
        if (count == 0) {
            cout << "No accounts in the bank." << endl;
            return;
        }
        cout << "Accounts in the Bank:" << endl;
        for (int i = 0; i < count; i++) {
            cout << "Account Number: " << accounts[i].accountNumber
                 << ", Account Holder: " << accounts[i].accountHolderName
                 << ", Balance: $" << accounts[i].balance
                 << ", Active: " << (accounts[i].isActive ? "Yes" : "No") << endl;
        }
    }

    void searchAccount(const string& accountNumber) {
        for (int i = 0; i < count; i++) {
            if (accounts[i].accountNumber == accountNumber) {
                cout << "Account found: " << endl;
                cout << "Account Number: " << accounts[i].accountNumber
                     << ", Account Holder: " << accounts[i].accountHolderName
                     << ", Balance: $" << accounts[i].balance
                     << ", Active: " << (accounts[i].isActive ? "Yes" : "No") << endl;
                return;
            }
        }
        cout << "Account not found." << endl;
    }

    void viewTotalBalance(const string& accountNumber) {
        for (int i = 0; i < count; i++) {
            if (accounts[i].accountNumber == accountNumber) {
                cout << "Total Balance for account " << accountNumber 
                     << " is: $" << accounts[i].balance << endl;
                return;
            }
        }
        cout << "Account not found." << endl;
    }

    void depositMoney(const string& accountNumber, float amount) {
        for (int i = 0; i < count; i++) {
            if (accounts[i].accountNumber == accountNumber) {
                if (accounts[i].isActive) {
                    accounts[i].balance += amount; // Add the deposit amount to balance
                    cout << "Deposited $" << amount << " into account " << accountNumber << endl;
                    cout << "New balance: $" << accounts[i].balance << endl;
                } else {
                    cout << "Account " << accountNumber << " is inactive." << endl;
                }
                return;
            }
        }
        cout << "Account not found." << endl;
    }

    void withdrawMoney(const string& accountNumber, float amount) {
        for (int i = 0; i < count; i++) {
            if (accounts[i].accountNumber == accountNumber) {
                if (accounts[i].isActive) {
                    if (accounts[i].balance >= amount) {
                        accounts[i].balance -= amount; // Subtract the withdrawal amount from balance
                        cout << "Withdrew $" << amount << " from account " << accountNumber << endl;
                        cout << "New balance: $" << accounts[i].balance << endl;
                    } else {
                        cout << "Insufficient balance in account " << accountNumber << endl;
                    }
                } else {
                    cout << "Account " << accountNumber << " is inactive." << endl;
                }
                return;
            }
        }
        cout << "Account not found." << endl;
    }

    void deactivateAccount(const string& accountNumber) {
        for (int i = 0; i < count; i++) {
            if (accounts[i].accountNumber == accountNumber) {
                if (accounts[i].isActive) {
                    accounts[i].isActive = false; // Mark account as inactive
                    cout << "Account " << accountNumber << " has been deactivated." << endl;
                } else {
                    cout << "Account " << accountNumber << " is already inactive." << endl;
                }
                return;
            }
        }
        cout << "Account not found." << endl;
    }

    void activateAccount(const string& accountNumber) {
        for (int i = 0; i < count; i++) {
            if (accounts[i].accountNumber == accountNumber) {
                if (!accounts[i].isActive) {
                    accounts[i].isActive = true; // Mark account as active
                    cout << "Account " << accountNumber << " has been activated." << endl;
                } else {
                    cout << "Account " << accountNumber << " is already active." << endl;
                }
                return;
            }
        }
        cout << "Account not found." << endl;
    }

    int getAccountCount() const {
        return count;
    }
};

void adminMenu(Bank& bank) {
    int choice;
    do {
        cout << "\nAdmin Menu" << endl;
        cout << "1. Add Account" << endl;
        cout << "2. Display Accounts" << endl;
        cout << "3. Deactivate Account" << endl;
        cout << "4. Activate Account" << endl;
        cout << "5. Count Accounts in Bank" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string accountNumber, accountHolder;
                float balance;
                cout << "Enter account number: ";
                cin.ignore(); // Clear newline character from input buffer
                getline(cin, accountNumber);
                cout << "Enter account holder name: ";
                getline(cin, accountHolder);
                cout << "Enter initial balance: ";
                cin >> balance;
                bank.addAccount(Account(accountNumber, accountHolder, balance));
                break;
            }
            case 2:
                bank.displayAccounts();
                break;
            case 3: {
                string accountNumber;
                cout << "Enter account number to deactivate: ";
                cin.ignore();
                getline(cin, accountNumber);
                bank.deactivateAccount(accountNumber);
                break;
            }
            case 4: {
                string accountNumber;
                cout << "Enter account number to activate: ";
                cin.ignore();
                getline(cin, accountNumber);
                bank.activateAccount(accountNumber);
                break;
            }
            case 5:
                cout << "Total accounts in bank: " << bank.getAccountCount() << endl;
                break;
            case 6:
                cout << "Exiting admin menu..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 6);
}

void customerMenu(Bank& bank) {
    int choice;
    do {
        cout << "\nCustomer Menu" << endl;
        cout << "1. Search Account" << endl;
        cout << "2. Deposit Money" << endl;
        cout << "3. Withdraw Money" << endl;
        cout << "4. View Total Balance" << endl; // New option for viewing balance
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string accountNumber;
                cout << "Enter account number to search: ";
                cin.ignore();
                getline(cin, accountNumber);
                bank.searchAccount(accountNumber);
                break;
            }
            case 2: {
                string accountNumber;
                float amount;
                cout << "Enter account number to deposit: ";
                cin.ignore();
                getline(cin, accountNumber);
                cout << "Enter amount to deposit: ";
                cin >> amount;
                bank.depositMoney(accountNumber, amount);
                break;
            }
            case 3: {
                string accountNumber;
                float amount;
                cout << "Enter account number to withdraw from: ";
                cin.ignore();
                getline(cin, accountNumber);
                cout << "Enter amount to withdraw: ";
                cin >> amount;
                bank.withdrawMoney(accountNumber, amount);
                break;
            }
            case 4: {
                string accountNumber;
                cout << "Enter account number to view balance: ";
                cin.ignore();
                getline(cin, accountNumber);
                bank.viewTotalBalance(accountNumber); // Call the viewTotalBalance function
                break;
            }
            case 5:
                cout << "Exiting customer menu..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 5);
}

int main() {
    Bank bank;
    int userType;

    do {
        cout << "Welcome to the Bank Management System" << endl;
        cout << "Select User Type: " << endl;
        cout << "1. Admin" << endl;
        cout << "2. Customer" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> userType;

        switch (userType) {
            case 1:
                adminMenu(bank);
                break;
            case 2:
                customerMenu(bank);
                break;
            case 3:
                cout << "Exiting the system..." << endl;
                break;
            default:
                cout << "Invalid user type selected. Please try again." << endl;
        }
    } while (userType != 3);

    return 0;
}
