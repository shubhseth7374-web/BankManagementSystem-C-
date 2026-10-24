#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
#include <iomanip>

using namespace std;

class Account {
private:
    int accNo;
    string name;
    double balance;

public:
    Account(int a, string n, double b) {
        accNo = a;
        name = n;
        balance = b;
    }

    int getAccNo() { return accNo; }
    string getName() { return name; }
    double getBalance() { return balance; }

    void deposit(double amount) {
        balance += amount;
    }

    bool withdraw(double amount) {
        if (amount > balance) return false;
        balance -= amount;
        return true;
    }
};

class Bank {
private:
    vector<Account> accounts;

    void loadFile() {
        ifstream file("accounts.txt");
        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string a, n, b;
            getline(ss, a, ',');
            getline(ss, n, ',');
            getline(ss, b, ',');
            accounts.push_back(Account(stoi(a), n, stod(b)));
        }
        file.close();
    }

    void saveFile() {
        ofstream file("accounts.txt");
        for (int i = 0; i < accounts.size(); i++) {
            file << accounts[i].getAccNo() << ","
                 << accounts[i].getName() << ","
                 << fixed << setprecision(2) << accounts[i].getBalance() << "\n";
        }
        file.close();
    }

    int find(int accNo) {
        for (int i = 0; i < accounts.size(); i++) {
            if (accounts[i].getAccNo() == accNo) return i;
        }
        return -1;
    }

public:
    Bank() {
        loadFile();
    }

    void createAccount(string name, double amount) {
        int accNo = 1001;
        if (!accounts.empty()) {
            accNo = accounts.back().getAccNo() + 1;
        }
        accounts.push_back(Account(accNo, name, amount));
        saveFile();
        cout << "Account created. Account Number: " << accNo << endl;
    }

    void deposit(int accNo, double amount) {
        int i = find(accNo);
        if (i == -1) {
            cout << "Account not found." << endl;
            return;
        }
        accounts[i].deposit(amount);
        saveFile();
        cout << "Deposit successful. Balance: " << fixed << setprecision(2)
             << accounts[i].getBalance() << endl;
    }

    void withdraw(int accNo, double amount) {
        int i = find(accNo);
        if (i == -1) {
            cout << "Account not found." << endl;
            return;
        }
        if (accounts[i].withdraw(amount)) {
            saveFile();
            cout << "Withdrawal successful. Balance: " << fixed << setprecision(2)
                 << accounts[i].getBalance() << endl;
        } else {
            cout << "Insufficient balance." << endl;
        }
    }

    void checkBalance(int accNo) {
        int i = find(accNo);
        if (i == -1) {
            cout << "Account not found." << endl;
            return;
        }
        cout << "Name: " << accounts[i].getName() << endl;
        cout << "Balance: " << fixed << setprecision(2)
             << accounts[i].getBalance() << endl;
    }

    void showAll() {
        if (accounts.empty()) {
            cout << "No accounts found." << endl;
            return;
        }
        for (int i = 0; i < accounts.size(); i++) {
            cout << accounts[i].getAccNo() << "  "
                 << accounts[i].getName() << "  "
                 << fixed << setprecision(2) << accounts[i].getBalance() << endl;
        }
    }
};

int readInt() {
    int x;
    while (!(cin >> x)) {
        cout << "Invalid input. Try again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return x;
}

double readAmount() {
    double x;
    while (!(cin >> x) || x <= 0) {
        cout << "Enter a positive number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return x;
}

int main() {
    Bank bank;
    int choice;

    do {
        cout << "\n1. Create Account\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Check Balance\n";
        cout << "5. Show All Accounts\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        choice = readInt();

        if (choice == 1) {
            string name;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter name: ";
            getline(cin, name);
            cout << "Enter initial deposit: ";
            double amount = readAmount();
            bank.createAccount(name, amount);
        } else if (choice == 2) {
            cout << "Enter account number: ";
            int accNo = readInt();
            cout << "Enter amount: ";
            double amount = readAmount();
            bank.deposit(accNo, amount);
        } else if (choice == 3) {
            cout << "Enter account number: ";
            int accNo = readInt();
            cout << "Enter amount: ";
            double amount = readAmount();
            bank.withdraw(accNo, amount);
        } else if (choice == 4) {
            cout << "Enter account number: ";
            int accNo = readInt();
            bank.checkBalance(accNo);
        } else if (choice == 5) {
            bank.showAll();
        } else if (choice == 6) {
            cout << "Goodbye!" << endl;
        } else {
            cout << "Invalid choice." << endl;
        }
    } while (choice != 6);

    return 0;
}
