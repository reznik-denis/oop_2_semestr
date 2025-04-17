// Reznik_LAB06_V13.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Для розробки шаблонів класів можна використати результати виконання практичної роботи  No5. 
// При тестуванні шаблонів класів необхідно створювати об'єкти з різними допустимими значеннями 
// параметрів шаблону (наприклад, компоненти масива можуть бути цілими, дійсними або комплексними числами).


#include <iostream> // Підключаємо бібліотеку для введення/виведення
#include <complex> // Для роботи з комплексними числами
using namespace std; // Щоб не писати std:: перед cout, endl тощо

// Оголошення класу IntArray для роботи з масивом цілих чисел
template <typename T> class Array {
private:
    T* m_array;     // Вказівник на динамічний масив
    int m_size;       // Розмір масиву

public:
    // Конструктор за замовчуванням або з параметром
    Array(int size = 0) : m_size(size) {
        m_array = new T[size]; // Виділення пам’яті під масив
    }

    // Деструктор — викликається при видаленні об'єкта
    ~Array() {
        delete[] m_array; // Звільнення пам’яті, виділеної під масив
    }

    // Копіювальний конструктор — створює копію масиву
    Array(const Array& other) : m_size(other.m_size) {
        m_array = new T[m_size]; // Виділення нової пам’яті
        for (int i = 0; i < m_size; ++i) {
            m_array[i] = other.m_array[i]; // Копіюємо значення
        }
    }

    // Оператор присвоєння =
    Array& operator=(const Array& other) {
        if (this != &other) { // Перевірка на самоприсвоєння
            delete[] m_array; // Видаляємо старий масив
            m_size = other.m_size;
            m_array = new T[m_size]; // Виділяємо новий
            for (int i = 0; i < m_size; ++i) {
                m_array[i] = other.m_array[i]; // Копіюємо елементи
            }
        }
        return *this; // Повертаємо посилання на поточний об'єкт
    }

    // Дружній оператор виводу <<
    friend ostream& operator<<(ostream& out, const Array& arr) {
        for (int i = 0; i < arr.m_size; ++i) {
            out << arr.m_array[i] << " "; // Виводимо елементи масиву
        }
        return out;
    }

    // Оператор доступу до елементів масиву []
    T& operator[](int index) {
        return m_array[index]; // Повертає посилання на елемент
    }

    // Перевантаження оператора +=
    Array& operator+=(const Array& other) {
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
    Array& operator-=(const Array& other) {
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
    // Тестування з double
    cout << "\n--- Testing with double ---\n";
    // Перевірка конструктора
    Array <double>arr1(5); // Створюємо масив з 5 елементів
    Array <double>arr2(5); // Створюємо ще один масив з 5 елементів

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
    Array <double>arr3;
    arr3 = arr1; // arr3 має бути копією arr1
    cout << "arr3 (after arr3 = arr1): " << arr3 << endl;

    // Перевірка копіювального конструктора
    Array <double>arr4 = arr2; // створюємо копію arr2
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

    // Тестування з int
    cout << "\n--- Testing with int ---\n";
    Array<int> intArr1(3), intArr2(3);
    intArr1[0] = 1; intArr1[1] = 2; intArr1[2] = 3;
    intArr2[0] = 4; intArr2[1] = 5; intArr2[2] = 6;
    cout << "intArr1: " << intArr1 << endl;
    cout << "intArr2: " << intArr2 << endl;

    intArr1 += intArr2;
    cout << "intArr1 += intArr2: " << intArr1 << endl;

    intArr1 -= intArr2;
    cout << "intArr1 -= intArr2: " << intArr1 << endl;

    // Тестування з комплексними числами
    cout << "\n--- Testing with complex ---\n";
    Array<complex<double>> compArr1(2), compArr2(2);
    compArr1[0] = { 1.0, 2.0 }; compArr1[1] = { 3.0, 4.0 };
    compArr2[0] = { 0.5, -1.0 }; compArr2[1] = { 2.0, 2.0 };

    cout << "compArr1: " << compArr1 << endl;
    cout << "compArr2: " << compArr2 << endl;

    compArr1 += compArr2;
    cout << "compArr1 += compArr2: " << compArr1 << endl;

    compArr1 -= compArr2;
    cout << "compArr1 -= compArr2: " << compArr1 << endl;

    return 0; // Завершення програми
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu