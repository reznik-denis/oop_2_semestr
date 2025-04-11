// Reznik_LAB04_V13.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Створити абстрактний базовий клас Array з віртуальними методами складання та поелементної обробки масиву 
// foreach(). Розробити похідні класи AndArray до OrArray (вибір). У першому класі операція додавання 
// реалізується як перетин множин, а поелементна обробка є вилучення квадратного кореня. У другому 
// класі операція додавання реалізується як об'єднання, а поелементна обробка – обчислення логарифму.

#include <iostream>    // для вводу/виводу
#include <vector>      // для використання векторів (динамічні масиви)
#include <cmath>       // для математичних функцій (sqrt, log)
using namespace std;   // Щоб не писати std:: перед кожним cout, string і т.д.

class Array {  // Абстрактний базовий клас
protected:
    vector<double> data;  // поле: масив даних (protected — доступний для нащадків)
    Array(const vector<double>& d) : data(d) {}  //Конструктор: ініціалізує масив даними(передається по посиланню, щоб уникнути копіювання).

public:
    virtual ~Array() {}  //Віртуальний деструктор — обов’язково для базового класу з віртуальними методами.

    const vector<double>& getData() const {  // Гетер для доступу до data
        return data;
    }

    virtual Array* add(const Array* other) const = 0; // Віртуальний метод для операції складання (об'єднання або перетин).
    virtual void foreach() = 0;  // Віртуальний метод для обробки кожного елемента.

   virtual void print() const {   // Метод для виводу елементів
        for (double val : data)
            cout << val << " ";
        cout << endl;
    }
};

class AndArray : public Array {  // Клас перетину та коренів наслідується від Array публічно, що дозволяє викликати базові методи.
public:
    AndArray(const vector<double>& d) : Array(d) {}  // Конструктор передає vec у базовий клас.

    virtual Array* add(const Array* other) const override {  // Метод add: реалізує перетин двох масивів (елементи, які є в обох). 
        vector<double> result;
        const vector<double>& otherData = other->getData();

        for (double val : data) {
            for (double otherVal : otherData) {
                if (val == otherVal) {
                    result.push_back(val);
                    break;
                }
            }
        }

        return new AndArray(result);  //Результат — новий об’єкт типу AndArray.
    }

    virtual void foreach() override { // Метод foreach: змінює кожен елемент на його корінь квадратний.
        for (double& val : data)
            val = sqrt(val);
    }
};

class OrArray : public Array {  // Клас об'єднання та логарифмів
public:
    OrArray(const vector<double>& d) : Array(d) {} // Конструктор

    virtual Array* add(const Array* other) const override {  // Метод add
        vector<double> result = data;  // Копіюємо свій масив
        const vector<double>& otherData = other->getData();

        for (double val : otherData) {
            bool found = false;

            for (double existing : data) {  // Перевіряємо, чи вже є такий елемент у result
                if (val == existing) {
                    found = true;
                    break;
                }
            }

            if (!found) {  // Якщо не знайшли — додаємо
                result.push_back(val);
            }
        }

        return new OrArray(result);  // Повертаємо новий об'єкт з об'єднаним масивом
    }

    virtual void foreach() override {  // Метод foreach: замінює кожен елемент на його натуральний логарифм.
        for (double& val : data)
            val = log(val);
    }
};

// ===============================
// Тестування
// ===============================
int main() {
    vector<double> a = { 1, 2, 3, 4, 5 };
    vector<double> b = { 3, 4, 5, 6, 7 };

    Array* arr1 = new AndArray(a);
    Array* arr2 = new AndArray(b);

    Array* resultAnd = arr1->add(arr2);  // Перетин
    cout << "AndArray result (intersection): ";
    resultAnd->print();

    resultAnd->foreach();  // Корінь
    cout << "After sqrt foreach(): ";
    resultAnd->print();

    delete arr1;
    delete arr2;
    delete resultAnd;

    cout << "\n------------------------\n";

    Array* arr3 = new OrArray(a);
    Array* arr4 = new OrArray(b);

    Array* resultOr = arr3->add(arr4);  // Об'єднання
    cout << "OrArray result (union): ";
    resultOr->print();

    resultOr->foreach();  // Логарифм
    cout << "After log foreach(): ";
    resultOr->print();

    delete arr3;
    delete arr4;
    delete resultOr;

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
