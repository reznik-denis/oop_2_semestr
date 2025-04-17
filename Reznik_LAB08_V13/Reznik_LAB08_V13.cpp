// Reznik_LAB08_V13.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Текстовий файл містить розклад на семестр: день тижня, пара, курс, група, аудиторія, дисципліна, вид занять 
// (лекція, практичне, семінар, лабораторне). Конфліктом аудиторій назвемо ситуацію, коли одночасно в одній 
// аудиторії мають проводитися заняття більше ніж однієї групи, причому не лекції для груп одного курсу з 
// однакової дисципліни. Перевірити, чи існує в розкладі конфлікт аудиторій. Якщо існує, то повідомити про 
// всі такі конфлікти (день, пара, які дисципліни й у кого там мають відбутися). 97 У заголовку вказується, 
// що цей документ містить розклад, у підсумковому рядку – загальна кількість записів і кількість різних 
// навчальних груп.

#include <iostream>      // для вводу/виводу
#include <fstream>       // для роботи з файлами
#include <sstream>       // для розбору рядків
#include <vector>        // для використання векторів
#include <string>        // для роботи з рядками
#include <map>           // для словника (ключ -> значення)
#include <set>           // для зберігання унікальних елементів

using namespace std;     // використання стандартного простору імен

// Структура для зберігання інформації про одне заняття
struct Lesson {
    string day;      // День тижня (наприклад, Понеділок)
    int pair;        // Номер пари (1, 2, 3...)
    int course;      // Курс (2, 3, 4...)
    string group;    // Група (наприклад, КІ-21)
    string room;     // Аудиторія (наприклад, 101)
    string subject;  // Назва дисципліни (наприклад, ООП)
    string type;     // Вид заняття (лекція, практика тощо)
};

// Перевірка, чи конфлікт дійсно порушення
bool isRealConflict(const vector<Lesson>& lessons) {
    if (lessons.empty()) return false; // якщо немає занять, то нема що перевіряти

    if (lessons[0].type != "lection") return true; // якщо перше заняття — не лекція, то це точно конфлікт

    string subj = lessons[0].subject;  // дисципліна першого заняття
    int course = lessons[0].course;    // курс першого заняття

    for (const auto& l : lessons) {
        // Якщо хоч одне заняття не є лекцією або дисципліна/курс відрізняється — конфлікт
        if (l.type != "lection" || l.subject != subj || l.course != course)
            return true;
    }

    return false; // якщо всі лекції з однаковим курсом і дисципліною — конфлікту немає
}

int main() {
    ifstream file("rozklad.txt"); // відкриваємо файл для читання
    if (!file.is_open()) {
        cerr << "Error opened file!" << endl; // якщо файл не відкрився — повідомляємо
        return 1;
    }

    vector<Lesson> lessons;         // вектор усіх занять
    set<string> uniqueGroups;       // множина для зберігання унікальних назв груп

    string header;
    getline(file, header);          // читаємо перший рядок (заголовок) і ігноруємо його

    string line;
    while (getline(file, line)) {
        // Пропускаємо непотрібні службові рядки
        if (line.empty() ||
            line.find("Schedule") != string::npos ||
            line.find("All") != string::npos ||
            line.find("Groups") != string::npos)
            continue;

        Lesson l;
        istringstream iss(line);    // розбираємо рядок на частини
        iss >> l.day >> l.pair >> l.course >> l.group >> l.room >> l.subject >> l.type;

        lessons.push_back(l);       // додаємо заняття до списку
        uniqueGroups.insert(l.group); // додаємо групу в множину унікальних
    }

    file.close(); // закриваємо файл

    // Групування за день+пара+аудиторія
    map<string, vector<Lesson>> grouped;
    for (const auto& l : lessons) {
        string key = l.day + "-" + to_string(l.pair) + "-" + l.room;
        grouped[key].push_back(l); // класифікуємо заняття по ключу
    }

    cout << "\n=== Conflicts in schedule ===\n";
    bool found = false; // флаг, чи знайдено конфлікти

    for (const auto& entry : grouped) {
        const string& key = entry.first;  //ключ у форматі "день-пара-аудиторія"
        const vector<Lesson>& group = entry.second; //Отримуємо вектор занять, які проходять в один час і в одній аудиторії.
        if (group.size() > 1 && isRealConflict(group)) {  //Якщо в аудиторії більше ніж одне заняття і функція isRealConflict() підтверджує, що це справжній конфлікт
            found = true;  //Фіксуємо, що знайдено хоча б один конфлікт
            cout << "Conflict in: " << key << "\n"; //Виводимо місце конфлікту 
            for (const auto& l : group) { //Перебираємо всі заняття, які відбуваються в цьому місці та часі.
                cout << "  " << l.pair << " | " << l.group << " | " << l.subject << " | " << l.type << "\n";
            }
            cout << endl;
        }
    }

    if (!found) {
        cout << "Conflicts no exist.\n";
    }

    cout << "\nAll: " << lessons.size()
        << "\nCount of unique groops: " << uniqueGroups.size() << endl;

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
