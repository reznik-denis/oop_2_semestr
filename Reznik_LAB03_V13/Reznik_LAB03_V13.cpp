// Reznik_LAB03_V13.cpp : This file contains the 'main' function. Program execution begins and ends there.
// author Reznik D.O. student of group 222z (online)

//Необхідно побудувати ієрархію класів відповідно схемі успадкування, 
//наведеній у варіанті завдання.
//Кожен клас повинен містити конструктор ініціалізації, і функцію show для
//виведення значень.
//Функція main повинна ілюструвати ієрархію успадкування..


#include <iostream>   // Підключаємо бібліотеку для вводу/виводу (cin, cout)
#include <string>     // Підключаємо бібліотеку для роботи з рядками (string)
using namespace std;  // Щоб не писати std:: перед кожним cout, string і т.д.

class B {
	int a; // приватне поле
public:
	B() {}; //Конструктор за замовчуванням (нічого не ініціалізує).
	B(int x) {  
		a = x;  //Конструктор з параметром x, ініціалізує a.
	};
	void show_B() {
		cout << "B=   " << a << "\n";  //Метод виводу значення a.
	};
};

class D1 : public B {  //Має своє приватне поле b, і наслідує публічно B.
	int b;
public:
	D1(int x, int y) : B(y) {   //Конструктор: y передається в B(y), x присвоюється b.
		b = x;
	};
	void show_D1() { 
		cout << "D1=  " << b << "\n"; show_B();   //Виводить значення b, потім викликає метод з базового класу B.
	};
};

class D2 : private B {  //Успадкування private, тобто B::show_B() стає приватним у D2.
	int c;
public:
	D2(int x, int y) : B(y) {  //Конструктор: y в B(y), x в c.
		c = x; 
	};
	void show_D2() {
		cout << "D2=  " << c << "\n"; show_B();  //Метод доступний ззовні, може викликати show_B() всередині.
	};
};

class D3 : private B {
	int d;
public:
	D3(int x, int y) : B(y) {
		d = x;
	};
	void show_D3() {
		cout << "D3=  " << d << "\n"; show_B();
	};
};

class D4 : private D1 {  //Успадковує D1, який вже наслідував B.
	int e;
public:
	D4(int x, int y, int c) : D1(y, c) {  //Передає y і c у D1, а x призначає e.
		e = x;
	};
	void show_D4() {
		cout << "D4=  " << e << "\n"; show_D1();  //Виводить e, потім викликає show_D1(), який також виведе b і a.
	};
};

class D5 : public D2, private D3 {  //Успадковує публічно D2, приватно D3.
	int g;
public:
	D5(int x, int y, int z, int i, int j) : D2(y, z), D3(i, j) {  //Ініціалізує D2(y, z) і D3(i, j), g = x.
		g = x;
	};
	void show_D5() {
		cout << "D5=  " << g << "\n"; show_D2(); show_D3();  //Виводить g, потім викликає методи D2 і D3, які також виводять свої c, d, і значення з B.
	};
};

int main() {
	D3 temp(10, 20);
	D4 temp1(100, 200, 300);
	D5 temp2(1, 2, 3, 4, 5);  //Створюємо об’єкти класів з відповідними параметрами конструктора.
	cout << "D3 temp(10, 20);" << endl;
	cout << "D4 temp1(100,200,300);" << endl;
	cout << "D5 temp2(1,2,3,4,5);" <<  endl;  //Коментарі на екран, що створено.
	cout << "\n According to the hierarchy class D3: \n";
	temp.show_D3();  //Вивід даних з D3 (виведе d, а потім a).
	cout << "\n According to the hierarchy class D4\n";
	temp1.show_D4(); //Виведе e, b, a.
	cout << "\n According to the hierarchy class D5\n";
	temp2.show_D5();  //Виведе g, c, a з D2, потім d, a з D3.

	return 0;
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
