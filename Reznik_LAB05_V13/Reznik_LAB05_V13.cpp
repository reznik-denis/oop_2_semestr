// Reznik_LAB05_V13.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Вашого варіанта. Клас, що розробляється, повинен містити наступні елементи: приховані і відкриті поля, 
// конструктори, перевантажені операції. У програмі має виконуватися перевірка всіх розроблених елементів класу.
//Описати клас для роботи з масивами чисел.Реалізувати можливість виконання узгоджених масивів комбінованих 
// операцій присвоювання(+=, -=).

#include <iostream> // Підключаємо бібліотеку для введення/виведення
using namespace std; // Щоб не писати std:: перед cout, endl тощо

// Оголошення класу IntArray для роботи з масивом цілих чисел
class IntArray {
private:
    int* m_array;     // Вказівник на динамічний масив
    int m_size;       // Розмір масиву

public:
    // Конструктор за замовчуванням або з параметром
    IntArray(int size = 0) : m_size(size) {
        m_array = new int[size]; // Виділення пам’яті під масив
    }

    // Деструктор — викликається при видаленні об'єкта
    ~IntArray() {
        delete[] m_array; // Звільнення пам’яті, виділеної під масив
    }

    // Копіювальний конструктор — створює копію масиву
    IntArray(const IntArray& other) : m_size(other.m_size) {
        m_array = new int[m_size]; // Виділення нової пам’яті
        for (int i = 0; i < m_size; ++i) {
            m_array[i] = other.m_array[i]; // Копіюємо значення
        }
    }

    // Оператор присвоєння =
    IntArray& operator=(const IntArray& other) {
        if (this != &other) { // Перевірка на самоприсвоєння
            delete[] m_array; // Видаляємо старий масив
            m_size = other.m_size;
            m_array = new int[m_size]; // Виділяємо новий
            for (int i = 0; i < m_size; ++i) {
                m_array[i] = other.m_array[i]; // Копіюємо елементи
            }
        }
        return *this; // Повертаємо посилання на поточний об'єкт
    }

    // Дружній оператор виводу <<
    friend ostream& operator<<(ostream& out, const IntArray& arr) {
        for (int i = 0; i < arr.m_size; ++i) {
            out << arr.m_array[i] << " "; // Виводимо елементи масиву
        }
        return out;
    }

    // Оператор доступу до елементів масиву []
    int& operator[](int index) {
        return m_array[index]; // Повертає посилання на елемент
    }

    // Перевантаження оператора +=
    IntArray& operator+=(const IntArray& other) {
        if (m_size != other.m_size) {
            cout << "Error: arrays must be the same size!" << endl;
            return *this; // Не змінюємо нічого, якщо розміри не збігаються
        }
        for (int i = 0; i < m_size; ++i) {
            m_array[i] += other.m_array[i]; // Додаємо елементи
        }
        return *this; // Повертаємо поточний об'єкт
    }

    // Перевантаження оператора -=
    IntArray& operator-=(const IntArray& other) {
        if (m_size != other.m_size) {
            cout << "Error: arrays must be the same size!" << endl;
            return *this;
        }
        for (int i = 0; i < m_size; ++i) {
            m_array[i] -= other.m_array[i]; // Віднімаємо елементи
        }
        return *this;
    }
};


int main() {
    // Перевірка конструктора
    IntArray arr1(5); // Створюємо масив з 5 елементів
    IntArray arr2(5); // Створюємо ще один масив з 5 елементів

    // Перевірка оператора []
    // Заповнюємо arr1 значеннями 1 2 3 4 5
    for (int i = 0; i < 5; ++i) {
        arr1[i] = i + 1;
        arr2[i] = i * 2; // Заповнюємо arr2 значеннями 0 2 4 6 8 10
    }

    // Виводимо обидва масиви
    cout << "Initial arr1: " << arr1 << endl;
    cout << "Initial arr2: " << arr2 << endl;

    // Перевірка оператора присвоєння =
    IntArray arr3;
    arr3 = arr1; // arr3 має бути копією arr1
    cout << "arr3 (after arr3 = arr1): " << arr3 << endl;

    // Перевірка копіювального конструктора
    IntArray arr4 = arr2; // створюємо копію arr2
    cout << "arr4 (copy of arr2): " << arr4 << endl;

    // Перевірка оператора +=
    arr1 += arr2; // кожен елемент arr1 = arr1 + arr2
    cout << "arr1 (after arr1 += arr2): " << arr1 << endl;

    // Перевірка оператора -=
    arr1 -= arr2; // повертаємо arr1 до попереднього стану
    cout << "arr1 (after arr1 -= arr2): " << arr1 << endl;

    // Перевірка доступу до окремого елемента через []
    cout << "arr1[2] = " << arr1[2] << endl;
    arr1[2] = 100; // зміна одного елемента
    cout << "arr1 (after arr1[2] = 100): " << arr1 << endl;

    return 0; // Завершення програми
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu