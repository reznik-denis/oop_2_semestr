// Reznik_LAB10_V13.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>      // Підключаємо бібліотеку для вводу-виводу
#include <thread>        // Підключаємо бібліотеку для роботи з потоками
#include <mutex>         // Забезпечує потокобезпеку при виведенні.

using namespace std;     // Щоб не писати std:: перед cout, thread тощо

// Масив із 15 цілих чисел
int arr[15] = { 3, 5, 7, 2, 8, 10, 12, 14, 1, 0, 6, 4, 9, 11, 13 };

mutex mtx; // М’ютекс для синхронізації доступу до cout

// Потік T0 – виводить елементи з парними індексами
void printEvenIndexElements() {
    lock_guard<mutex> lock(mtx); // Блокуємо доступ до cout
    cout << "Even indexes: " << endl;
    for (int i = 0; i < 15; i += 2) {          // Проходимо по парних індексах (0, 2, 4, ...)
        cout << "Index " << i << ": " << arr[i] << endl;                 // Виводимо відповідний елемент масиву
    }
}

// Потік T1 – виводить квадрати елементів з непарними індексами
void printOddIndexSquares() {
    lock_guard<mutex> lock(mtx); // Блокуємо доступ до cout
    cout << "Squire odd indexes: " << endl;
    for (int i = 1; i < 15; i += 2) {           // Проходимо по непарних індексах (1, 3, 5, ...)
        cout << "Index " << i << ": " << arr[i] << "^2 = " << arr[i] * arr[i] << endl;         // Виводимо квадрат значення відповідного елемента
    }
}

int main() {
    // Створення двох потоків, які виконують відповідні функції
    thread t0(printEvenIndexElements);         // Потік t0 виконує функцію для парних індексів
    thread t1(printOddIndexSquares);           // Потік t1 виконує функцію для непарних індексів

    // Очікування завершення обох потоків (main не завершується раніше за них)
    t0.join();                                 // Очікуємо завершення потоку t0
    t1.join();                                 // Очікуємо завершення потоку t1

    return 0;                                  // Завершення програми
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
