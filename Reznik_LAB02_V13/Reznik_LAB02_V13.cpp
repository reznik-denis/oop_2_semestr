// Reznik_LAB02_V13.cpp : This file contains the 'main' function. Program execution begins and ends there.
// author Reznik D.O. student of group 222z (online)

//Створити у програмі клас Rahunok, який зберігатиме такі дані: унікальний номер рахунка, суму на рахунку 
// (початкове значення задати при створенні рахунка), нарахування відсотків.
//Додати до класу функції : конструктора з параметрами,
//відображення рахунка, встановлення додаткових відсотків, перерахування грошей з урахуванням відсотків.
//Створити у програмі клас Vkladnyk, який зберігатиме такі дані : серію та номер паспорту, прізвище, ім’я 
// та по батькові.


#include <iostream>   // Підключаємо бібліотеку для вводу/виводу (cin, cout)
#include <string>     // Підключаємо бібліотеку для роботи з рядками (string)
using namespace std;  // Щоб не писати std:: перед кожним cout, string і т.д.

// Базовий клас — Рахунок
class Count {
protected:
    string number;     // Унікальний номер рахунку
    double balance;    // Баланс
    double interest;   // Відсоткова ставка

public:
    // Конструктор
    Count(string num, double bal, double rate = 0.0) {
        number = num;
        balance = bal;
        interest = rate;
    }

    // Деструктор
    ~Count() {}

    // Метод відображення рахунку
    void showCount() const {
        cout << "Account number: " << number << endl;
        cout << "Balance: " << balance << " UAH" << endl;
        cout << "Interest rate: " << interest << "%" << endl;
    }

    // Метод встановлення відсотків
    void setInterest(double rate) {
        interest = rate;
    }

    // Метод нарахування відсотків
    void applyInterest() {
        balance += (balance * interest / 100);
    }
};

// клас Вкладник
class Investor : public Count {
private:
    string passportSeries;
    double passportNumber;
    string lastName;
    string firstName;
    string middleName;

public:
    // Конструктор з параметрами
    Investor(string num, double bal, double rate,
        string pass, double pass_num, string last, string first, string middle)
        : Count(num, bal, rate) // Виклик конструктора базового класу
    {
        passportSeries = pass;
        passportNumber = pass_num;
        lastName = last;
        firstName = first;
        middleName = middle;
    }

    // Деструктор
    ~Investor() {}

    // Метод виводу інформації про вкладника та рахунок
    void showInfo() const {
        cout << "Investor information:\n";
        cout << "Passport: " << passportSeries << passportNumber << endl;
        cout << "Full name: " << lastName << " " << firstName << " " << middleName << endl;
        cout << "\nAccount information:\n";
        showCount();
    }
};

// Головна функція
int main() {
    Investor person("ACC123456", 15000.0, 6.5,
        "BB", 987654, "Ivanenko", "Olha", "Petrovna");

    person.showInfo();

    cout << "\nApplying interest...\n" << endl;
    person.applyInterest();

    cout << "\nUpdated account info:\n" << endl;
    person.showInfo();

    cout << "Enter you new interests: " << endl;
    double new_interests;
    cin >> new_interests;
    person.setInterest(new_interests);
    cout << "\nApplying new interest...\n" << endl;
    person.applyInterest();
    cout << "\nUpdated account info:\n" << endl;
    person.showInfo();

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu