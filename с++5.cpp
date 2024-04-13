#include <iostream>
#include <iomanip>

using namespace std;

class BankAccount {
private:
    int accountNumber;
    double balance;
    double interestRate;

public:
    BankAccount(int accountNumber, double initialBalance) : accountNumber(accountNumber), balance(initialBalance), interestRate(0.0) {}

    void deposit(double amount) {
        if (amount < 0) {
            throw invalid_argument("Сумма должна быть неотрицательной");
        }
        balance += amount;
    }

    bool withdraw(double amount) {
        if (amount > 0 && amount <= this->balance) {
            this->balance -= amount;
            cout << "Выведенено: " << amount << endl;
            return true;
        }
        else {
            cout << "Неверная сумма вывода или недостаточный баланс" << endl;
            return false;
        }
    }

    double getBalance() {
        return this->balance;
    }

    double getInterest() {
        return (this->balance * this->interestRate * (1.0 / 12));
    }

    void setInterestRate(double newInterestRate) {
        this->interestRate = newInterestRate;
    }

    int getAccountNumber() {
        return this->accountNumber;
    }

    friend bool transfer(BankAccount& from, BankAccount& to, double amount);
};

    bool transfer(BankAccount& from, BankAccount& to, double amount) {
        if (amount <= 0) {
            cout << "Сумма должна быть положительной" << endl;
            return false;
        }        
        if (from.withdraw(amount)) {
            to.deposit(amount);
            cout << "Перевод выполнен" << endl;
            return true;
        }
        else {
            cout << "Недостаточно средств" << endl;
            return false;
        }
    }

int main() {

    setlocale(0, "");
    double account1AccountBalance, account2AccountBalance, amount;

    cout << "Введите баланс счета отправителя: ";
    while (!(cin >> account1AccountBalance)) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Ошибка! Пожалуйста, введите число: ";
    }

    cout << "Введите баланс счета получателя: ";
    while (!(cin >> account2AccountBalance)) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Ошибка! Пожалуйста, введите число: ";
    }

    cout << "Введите сумму для перевода: ";
    while (!(cin >> amount)) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Ошибка! Пожалуйста, введите число: ";
    }
    BankAccount account1(12345, account1AccountBalance);
    BankAccount account2(67890, account2AccountBalance);

    account1.setInterestRate(0.02);

    cout << "Баланс до перевода:" << endl;
    cout << "Счёт отправителя:" << account1.getBalance() << endl;
    cout << "Счёт получателя:" << account2.getBalance() << endl;

    cout << "Перевод: " << amount << " руб. со счета " << account1.getAccountNumber() << " на счет " << account2.getAccountNumber() << endl;
    transfer(account1, account2, amount);

    cout << "Баланс после перевода:" << endl;
    cout << "Счет отправителя: " << account1.getBalance() << endl;
    cout << "Счет получателя: " << account2.getBalance() << endl;

    return 0;
}