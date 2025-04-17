// Reznik_LAB07_V13.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Варіант 13
//Картотека в бюро обміну квартир організована як лінійний список.
//Відомості про кожну квартиру містять :
//• кількість кімнат;
//• поверх;
//• площа;
//• адреса.
//Скласти програму, яка забезпечує :
//• початкове формування картотеки;
//• введення заявки на обмін;
//• пошук в картотеці відповідного варіанту : при рівності кількості кімнат та
//поверху і відмінності площ в межах 10 % виводиться відповідна картка і видаляється із списку, в іншому 
// випадку заявка, що поступила, включається в список;
//• виведення всього списку.
//Програма повинна забезпечувати діалог за допомогою меню і контроль помилок при введенні.


#include <iostream>      // Підключення бібліотеки для введення/виведення (cin, cout)
#include <list>          // Підключення бібліотеки з контейнером std::list
#include <string>        // Для роботи з рядками (std::string)
#include <iomanip>       // Для форматування виводу (наприклад, setprecision)
#include <cmath>         // Для математичних операцій (fabs)

using namespace std;     // Щоб не писати std:: перед кожним cin, cout, string і т.д.

// Структура, яка описує квартиру
struct Apartment {
    int rooms;        // Кількість кімнат у квартирі
    int floor;        // Поверх, на якому знаходиться квартира
    double area;      // Площа квартири в квадратних метрах
    string address;   // Адреса квартири
};

// Функція для виводу даних про квартиру
void printApartment(const Apartment& apt) {
    cout << "Rooms: " << apt.rooms
        << ", Floor: " << apt.floor
        << ", Square: " << fixed << setprecision(2) << apt.area //вивід площі з 2 знаками після коми.
        << ", Address: " << apt.address << endl;
}

// Функція додавання квартири до списку
void addApartment(list<Apartment>& catalog) {
    Apartment apt;  //Оголошення нового об’єкта Apartment для введення.
    cout << "Enter count rooms: ";
    while (!(cin >> apt.rooms) || apt.rooms <= 0) {  //Запит і перевірка введення кількості кімнат. Відхиляються нульові та від’ємні значення.
        cout << "Error! Enter positive count: ";
        cin.clear(); cin.ignore(1000, '\n');
    }

    cout << "Enter Floor: ";
    while (!(cin >> apt.floor) || apt.floor <= 0) {  // Аналогічна перевірка для поверху
        cout << "Error! Enter positive count: ";
        cin.clear(); cin.ignore(1000, '\n');
    }

    cout << "Enter square (m²): ";
    while (!(cin >> apt.area) || apt.area <= 0) {
        cout << "Error! Enter positive count: ";
        cin.clear(); cin.ignore(1000, '\n');
    }

    cout << "Enter address: ";
    cin.ignore();                 // Щоб прибрати залишки символів після попередніх cin
    getline(cin, apt.address);   // Зчитуємо повну адресу з пробілами

    catalog.push_back(apt);  //Додаємо квартиру до списку
    cout << "Apartment add to catalog.\n";
}

// Функція для введення заявки і пошуку відповідної квартири
void processRequest(list<Apartment>& catalog) {
    Apartment request;
    //Введення параметрів заявки
    cout << "Enter count rooms in apply: ";
    cin >> request.rooms;
    cout << "Enter floor in apply: ";
    cin >> request.floor;
    cout << "Enter square you want: ";
    cin >> request.area;

    // Пошук відповідної квартири
    for (auto it = catalog.begin(); it != catalog.end(); ++it) {
        if (it->rooms == request.rooms && it->floor == request.floor) {  //Порівнюємо кількість кімнат і поверх.
            double diff = fabs(it->area - request.area) / request.area;  //Обчислення різниці площі (у %) — допускається до 10%.
            if (diff <= 0.10) {
                cout << "Find expectable apartment:\n";
                printApartment(*it);
                catalog.erase(it);
                cout << "Apartment delete from catalog. Change OK.\n";
                return;
            }
        }
    }

    // Якщо не знайдено – додаємо заявку як нову квартиру
    cout << "Apartment not find. Your apply add to catalog.\n";
    cout << "Enter address to apply: ";
    cin.ignore();                    // Очищення буфера вводу
    getline(cin, request.address);  // Введення адреси
    catalog.push_back(request);     // Додаємо заявку як нову квартиру
}

// Виведення всіх квартир
void printCatalog(const list<Apartment>& catalog) {
    if (catalog.empty()) {
        cout << "Catalog is empty.\n";
        return;
    }
    cout << "\nApartment's catalog:\n";
    for (const auto& apt : catalog) {  //Цикл по всіх квартирах
        printApartment(apt);
    }
    cout << endl;
}

// Меню
void menu() {
    list<Apartment> catalog; // Створення списку квартир
    int choice;
    //Меню з діалогом
    do {
        cout << "\n=== Menu ===\n";
        cout << "1. Add apartment to catalog\n";
        cout << "2. Enter apply to change\n";
        cout << "3. Show catalog\n";
        cout << "4. Exit\n";
        cout << "Your choice: ";
        cin >> choice;
        //Реалізація вибору
        switch (choice) {
        case 1:
            addApartment(catalog);
            break;
        case 2:
            processRequest(catalog);
            break;
        case 3:
            printCatalog(catalog);
            break;
        case 4:
            cout << "End program.\n";
            break;
        default:
            cout << "Wrong choice. Try again.\n";
        }
    } while (choice != 4); // Повторювати, поки не вибрано вихід
}

int main() {
    menu();  //Запуск меню
    return 0;
}

//fabs — це функція з бібліотеки <cmath>, яка означає "floating-point absolute", тобто модуль (абсолютне 
// значення) для чисел з плаваючою комою (float, double, long double).

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu