// Reznik_LAB04_V13.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Складіть програму на мові С++ (згідно варіанту) для розв’язку наступної задачі, в Створити інтерфейс 
// IFileHandler, що містить чисто віртуальні методи open(), read(), write(), close(). Програму оформити в 
// звіті. Реалізувати клас FileCompressor, що стискає дані перед записом у файл (імітація).

#include <iostream>     // Підключення бібліотеки для вводу/виводу (cout, cerr тощо)
#include <fstream>      // Для роботи з файлами (ifstream, ofstream, fstream)
#include <string>       // Для використання типу string
#include <algorithm>    // Для використання алгоритмів, наприклад std::remove

using namespace std;    // Щоб уникнути постійного написання std::

// Інтерфейс для обробки файлів
class IFileHandler {
public:
    virtual void open(const string& filename) = 0;      // Відкриття файлу
    virtual void write(const string& data) = 0;         // Запис у файл
    virtual void read() = 0;                            // Зчитування з файлу
    virtual void close() = 0;                           // Закриття файлу
    virtual ~IFileHandler() {}                          // Віртуальний деструктор
};

// Клас-реалізація з імітацією стискання (видалення пробілів)
class FileCompressor : public IFileHandler {
private:
    string filename;            // Ім'я файлу
    fstream file;               // Потік для читання/запису

    // Метод "стискання" — видалення пробілів
    string compress(const string& data) {
        string compressed = data;
        // std::remove переміщує всі символи, що не є пробілами, на початок
        compressed.erase(remove(compressed.begin(), compressed.end(), ' '), compressed.end());
        return compressed;
    }

public:
    // Відкриття файлу для читання, запису та додавання
    void open(const string& filename) override {
        this->filename = filename;
        file.open(filename, ios::in | ios::out | ios::app); // читання + запис + дописування в кінець
        if (!file) {
            cerr << "Can't open the file: " << filename << endl;  // Повідомлення про помилку
        }
    }

    // Метод запису стислого тексту у файл
    void write(const string& data) override {
        if (file.is_open()) {
            string compressedData = compress(data);      // Стиснення даних
            file << compressedData << endl;              // Запис у файл
        }
        else {
            cerr << "File doesn't open for write!" << endl; // Якщо файл не відкрито
        }
    }

    // Метод зчитування вмісту файлу
    void read() override {
        if (!file.is_open()) {
            cerr << "File doesn't open for read!" << endl;
            return;
        }

        file.clear();         // Очищення стану потоку (наприклад, після EOF)
        file.seekg(0);        // Почати зчитування з початку файлу

        string line;
        cout << "File data:\n";
        while (getline(file, line)) {   // Зчитування рядків до кінця файлу
            cout << line << endl;
        }
    }

    // Метод закриття файлу
    void close() override {
        if (file.is_open()) {
            file.close();     // Закрити файл
        }
    }
};

// Головна функція
int main() {
    IFileHandler* handler = new FileCompressor();     // Створення об'єкта через інтерфейс

    handler->open("compressed.txt");                  // Відкриття файлу
    handler->write("It is example text for write!");  // Запис тексту (стисненого)
    handler->read();                                  // Зчитування вмісту
    handler->close();                                 // Закриття файлу

    delete handler;                                   // Звільнення пам’яті
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu