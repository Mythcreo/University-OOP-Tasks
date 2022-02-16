#include <iostream>
#include <string>
using namespace std;

const int LNAME = 25;

class STUDENT {	
	char name[LNAME] = {}; // С {} происходит инициализация, иначе могут появится проблемы до присваивания значения
	int age{};
	float grade{};
public: // Для name c char указатели используются во избежание копирования информации
	char *GetName();
	int GetAge() const; // Константные функции. Вносить изменения ими не предполагается
	float GetGrade() const;
	void SetName(char *);
	void SetAge(int);
	void SetGrade(float);
	void Set(char *, int, float);
	void Show();
};

void activeIN(int a, int b, int c, STUDENT &first);

int main() {
	setlocale(LC_ALL, "Russian");
	string choice;
	STUDENT first;

	while (true) {
		cout << "Варианты:\n0 - Завершить\n1 - GetName\n2 - GetAge\n3 - GetGrade" <<
			"\n4 - SetName\n5 - SetAge\n6 - SetGrade\n7 - Set\n8 - Show\n\nВведите число: ";
		cin >> choice;

		if (choice == "0") break;
		else if (choice == "1") first.GetName();
		else if (choice == "2") first.GetAge();
		else if (choice == "3") first.GetGrade();
		else if (choice == "4") activeIN(1, 0, 0, first);
		else if (choice == "5") activeIN(0, 1, 0, first);
		else if (choice == "6") activeIN(0, 0, 1, first);
		else if (choice == "7") activeIN(1, 1, 1, first);
		else if (choice == "8") first.Show();
		else cout << "Неправильное число, повторите.";

		system("pause");
		system("cls");
	}
	return 0;
}

void activeIN(int a, int b, int c, STUDENT &first) { // Ссылочный параметр используется во избежание копирования
	if (a) {
		char line[LNAME];
		cout << "Name: ";
		cin >> line;
		char *in = line; // Передача адреса line указателю
		first.SetName(in);
	}
	if (b) {
		int x;
		cout << "Age: ";
		cin >> x;
		first.SetAge(x);
	}
	if (c) {
		float y;
		cout << "Grade: ";
		cin >> y;
		first.SetGrade(y);
	}
}

// Далее геттеры, получающие информацию из private
char *STUDENT::GetName() {
	cout << name << endl;
	return name;
}
int STUDENT::GetAge() const {
	cout << age << endl;
	return age;
}
float STUDENT::GetGrade() const {
	cout << grade << endl;
	return grade;
}

// Далее сеттеры, меняющие информацию из private
void STUDENT::SetName(char *s) {
	char *p = name;
	while (*s) { // Пока не завершилось слово line, которое ввели
		*p = *s; // Присвоить элементу name значение соответствующего в line
		s++;
		p++; // Переместиться к рассмотрению следующего символа
	}
	*p = '\0'; // В отсутствие символа конца строки выведутся нечитаемые символы после слова
}
void STUDENT::SetAge(int a) { age = a; }
void STUDENT::SetGrade(float g) { grade = g; }
void STUDENT::Set(char *s, int a, float g) {
	SetName(s);
	SetAge(a);
	SetGrade(g);
}
void STUDENT::Show() {
	GetName();
	GetAge();
	GetGrade();
}