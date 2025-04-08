// Reznik_Lab01_V13.cpp : This file contains the 'main' function. Program execution begins and ends there.
// author Reznik D.O. student of group 222z (online)

//Складіть програму на мові С++ (згідно варіанту) для розв’язку наступної задачі, в програмі використувати 
// закриті члени классу, констукотри, диструтори, гетери, сетери та методи для введення та 
// виведення інформації.Ппрограму оформити в звіті.
//Написати клас  CD, який містить  наступні поля :
//-Name  – назва диска;
//Date –  дата запису диска(структура: month, year - місяць, рік);
//Theme – тема;
//SIZE – розмір;


#include <iostream>   // Підключаємо бібліотеку для вводу/виводу (cin, cout)
#include <string>     // Підключаємо бібліотеку для роботи з рядками (string)
using namespace std;  // Щоб не писати std:: перед кожним cout, string і т.д.

// Структура для дати
struct Date {
    int month;  // Місяць запису
    int year;   // Рік запису
};

// Клас CD
class CD {
private:
    string name;   // Назва диска
    Date date;     // Дата запису (структура)
    string theme;  // Тема диска
    double size;   // Розмір диска в МБ

public:
    // Конструктор за замовчуванням
    CD() {
        name = "Unknown";     // Встановлюємо значення за замовчуванням
        date.month = 1;
        date.year = 2000;
        theme = "General";
        size = 0.0;
        cout << "Build object CD" << endl;  // Повідомлення про створення
    }

    // Конструктор з параметрами
    CD(string n, int m, int y, string t, double s) {
        name = n;         // Присвоюємо передані значення полям об'єкта
        date.month = m;
        date.year = y;
        theme = t;
        size = s;
        cout << "Build object CD with parameters" << endl; // Повідомлення
    }

    // Деструктор
    ~CD() {
        cout << "Object is delete" << endl; // Повідомлення про видалення
    }

    // Сетери (методи для встановлення значень)
    void setName(string n) { name = n; }
    void setDate(int m, int y) { date.month = m; date.year = y; }
    void setTheme(string t) { theme = t; }
    void setSize(double s) { size = s; }

    // Гетери (методи для отримання значень)
    string getName() const { return name; }
    Date getDate() const { return date; }
    string getTheme() const { return theme; }
    double getSize() const { return size; }

    // Метод для введення даних
    void input() {
        cout << "Enter name CD: ";     // Просимо ввести назву
        getline(cin, name);            // Зчитуємо назву з пробілами

        cout << "Enter month: ";       // Введення місяця
        cin >> date.month;

        cout << "Enter year: ";        // Введення року
        cin >> date.year;

        cin.ignore();                  // Чистимо буфер після cin (для getline)
        cout << "Enter theme: ";       // Введення теми
        getline(cin, theme);

        cout << "Enter size (MB): ";   // Введення розміру
        cin >> size;
        cin.ignore();                  // Чистимо буфер
    }

    // Метод для виведення інформації
    void display() const {
        cout << "information about CD:" << endl;    // Заголовок
        cout << "Name: " << name << endl;           // Вивід назви
        cout << "Date: " << date.month << "/" << date.year << endl; // Дата
        cout << "Theme: " << theme << endl;         // Тема
        cout << "Size: " << size << " МБ" << endl;  // Розмір з одиницею
    }
};

// Головна функція
int main() {
    CD disk1;          // Створюємо об'єкт з конструктором за замовчуванням
    disk1.input();     // Викликаємо метод для введення інформації
    disk1.display();   // Виводимо інформацію про об'єкт

    cout << "\nCreate new CD with parameters\n";  // Повідомлення
    CD disk2("My Music", 5, 2022, "Music", 700.0); // Створення об'єкта з параметрами
    disk2.display();  // Виведення інформації про другий диск

    return 0;  // Завершення програми
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
