// Reznik_LAB08_V13.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <set>

using namespace std;

// Структура для зберігання інформації про одне заняття
struct Lesson {
    string day;      // День тижня
    int pair;        // Пара
    int course;      // Курс
    string group;    // Група
    string room;     // Аудиторія
    string subject;  // Дисципліна
    string type;     // Вид занять
};

// Перевірка, чи конфлікт дійсно порушення
bool isRealConflict(const vector<Lesson>& lessons) {
    if (lessons.empty()) return false;

    if (lessons[0].type != "lection") return true;

    string subj = lessons[0].subject;
    int course = lessons[0].course;

    for (const auto& l : lessons) {
        if (l.type != "lection" || l.subject != subj || l.course != course)
            return true;
    }

    return false;
}

int main() {
    ifstream file("rozklad.txt");
    if (!file.is_open()) {
        cerr << "Error opened file!" << endl;
        return 1;
    }

    vector<Lesson> lessons;
    set<string> uniqueGroups;

    string header;
    getline(file, header); // Пропускаємо заголовок

    string line;
    while (getline(file, line)) {
        if (line.empty() ||
            line.find("Schedule") != string::npos ||
            line.find("All") != string::npos ||
            line.find("Groups") != string::npos)
            continue;

        Lesson l;
        istringstream iss(line);
        iss >> l.day >> l.pair >> l.course >> l.group >> l.room >> l.subject >> l.type;

        lessons.push_back(l);
        uniqueGroups.insert(l.group);
    }

    file.close();

    // Групування за день+пара+аудиторія
    map<string, vector<Lesson>> grouped;
    for (const auto& l : lessons) {
        string key = l.day + "-" + to_string(l.pair) + "-" + l.room;
        grouped[key].push_back(l);
    }

    cout << "\n=== Conflicts in schedule ===\n";
    bool found = false;

    for (const auto& entry : grouped) {
        const string& key = entry.first;
        const vector<Lesson>& group = entry.second;
        if (group.size() > 1 && isRealConflict(group)) {
            found = true;
            cout << "Conflict in: " << key << "\n";
            for (const auto& l : group) {
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
