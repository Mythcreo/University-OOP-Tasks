#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
using namespace std;
class Employee {
private:
    static int count;

    string organisation{};
    string position{};
    double experience{};

    string name{};
    char gender{};
    int age{};
    double salary{};
    double allsalary{};
public:
    Employee(string n, char g, int a, string o, string p, double e, double s, double as) { // Конструктор
        name = n; gender = g; age = a;
        organisation = o;
        position = p;
        experience = e;
        salary = s;
        allsalary = as;

        count++;
    }
    void addSalary() { allsalary += salary; }

    void operator()(string p) { position = p; }
    void operator[](int s) { salary = s; }
    
    static int GetCount() { return count; }
    string GetName() { return name; };
    char GetGender() { return gender; };
    int GetAge() { return age; };
    string GetOrganisation() { return organisation; };
    string GetPosition() { return position; }
    double GetExperience() { return experience; };
    double GetSalary() { return salary; };
    double GetAllsalary() { return allsalary; };
    void GetInfo() {
        cout << "Name: " << GetName() << endl;
        cout << "Gender: " << GetGender() << endl;
        cout << "Age: " << GetAge() << endl;
        cout << "Organisation: " << GetOrganisation() << endl;
        cout << "Position: " << GetPosition() << endl;
        cout << "Experience: " << GetExperience() << endl;
        cout << "Salary: " << GetSalary() << endl;
        cout << "Accumulated salary: " << GetAllsalary() << endl;
    }

    void SetSalary(double plussalary) { salary += plussalary; };
};

int Employee::count = 0;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    vector <Employee> all = {
        Employee("Хороший Человек Иванович", 'm', 38, "Good Place", "Учитель", 15, 35000, 0),
        Employee("Плохой Человек Алексеевич", 'm', 25, "Bad Place", "Бухгалтер", 2, 190000, 0) };
    int numeOne, numeTwo; double salary;
    string choice, newrole; 
    while (true) {
        cout << "\t***Система учёта сотрудников***" << endl;
        cout << "Варианты:\n1 - Вывести информацию обо всех сотрудниках\n2 - Изменить должность" << 
            "\n3 - Установить зарплату\n4 - Вывести информацию о сотруднике\n5 - Начислить зарплату" <<
            "\n6 - Сравнить зарплату\n7 - Вывести число сотрудников" << "\n0 - Завершить работу" << endl;
        cout << "Выбор: "; cin >> choice;
        if (choice == "0") break;
        else if (choice == "1") {
            for (int i = 0; i < all[0].GetCount(); i++) {
                cout << "\nКод сотрудника в системе: " << i << endl;
                all[i].GetInfo();
                cout << endl;
            }
        }
        else if (choice == "6") {
            cout << "Код первого сотрудника: "; cin >> numeOne;
            cout << "Код второго сотрудника: "; cin >> numeTwo;
            cout << "Заплата №" << numeOne << " = " << all[numeOne].GetSalary() << " и";
            if (all[numeOne].GetSalary() > all[numeTwo].GetSalary()) cout << " > ";
            else cout << " < ";
            cout << "зарплаты №" << numeTwo << " = " << all[numeTwo].GetSalary() << endl;
        }
        else if (choice == "7") cout << "Количество сотрудников: " << all[0].GetCount() << endl;
        else {
            if (choice != "2" && choice != "3" && choice != "4" && choice != "5") {
                cout << "\nВарианта не предусмотрено, повторите попытку" << endl;
                continue;
            }
            cout << "Код сотрудника: "; cin >> numeOne;
            if (choice == "2") {
                cout << "Новая должность "; cin >> newrole;
                all[numeOne](newrole);
            }
            else if (choice == "3") {
                cout << "Установить зарплату: "; cin >> salary;
                all[numeOne][salary];
            }
            else if (choice == "4") all[numeOne].GetInfo();
            else all[numeOne].addSalary();
        }
        system("pause");
        system("cls");
    }
    return 0;
}
