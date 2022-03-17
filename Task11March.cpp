#include <windows.h>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

struct reader {
    string name;
    unsigned int sday{}, smonth{}, syear{};
    reader() { };
    reader(string name, unsigned int sday, unsigned int smonth, unsigned int syear) {
        this->name = name; this->sday = sday; this->smonth = smonth; this->syear = syear;
    }
};

class book {
public:
    string Title;
    vector <string> Authors;
    unsigned int Year{};
    string Publisher;
    unsigned int Pages{};
    book() { };
    book(string &Title, vector <string> &Authors, unsigned int &Year, string &Publisher, unsigned int &Pages) {
        this->Title = Title;
        this->Authors = Authors;
        this->Year = Year;
        this->Publisher = Publisher;
        this->Pages = Pages;
    }
};

class cathalog_book : public book {
public:
    unsigned int ID{}; // Номер книги в каталоге
    unsigned int Quantity{}; // Общее количество экземпляров
    unsigned int Instances{}; // В наличии
    vector <reader> Picked; // Список получивших книгу
    cathalog_book() { };
    cathalog_book(book &basis, unsigned int Quantity, unsigned int Instances) {
        Title = basis.Title; Authors = basis.Authors; Year = basis.Year; Publisher = basis.Publisher; Pages = basis.Pages;
        this->Quantity = Quantity;
        this->Instances = Instances;
    }
};

book *cbook(string Title, vector <string> Authors, unsigned int Year, string Publisher, unsigned int Pages) {
    return new book(Title, Authors, Year, Publisher, Pages); // Создание книги и возвращение указателя
}

void reID(vector <cathalog_book> &Cathalog) {
    for (int i = 0; i < Cathalog.size(); i++) Cathalog[i].ID = i;
}

void vision(vector <int> options);
void booksMenu(vector <book *> &allbooks); // Все книги
void creationMenu(vector <book *> &allbooks); // Создать книгу
void annihilationMenu(vector <book *> &allbooks); // Удалить книгу
void bookInfo(int i, vector <book *> &allbooks); // Информация о book

void logbooksMenu(vector <cathalog_book> &Cathalog); // Книги в каталоге
void attachMenu(vector <cathalog_book> &Cathalog, vector <book *> &allbooks); // Добавить книгу
void wipeMenu(vector <cathalog_book> &Cathalog); // Убрать книгу
void logbookInfo(int ID, vector <cathalog_book> &Cathalog); // Информация о cathalog_book

void IDInfo(vector <cathalog_book> &Cathalog); // Информация по ID
void searchID(vector <cathalog_book> &Cathalog, bool byName); // Поиск ID по названию или автору
void takeBook(vector <cathalog_book> &Cathalog); // Взять книгу
void returnBook(vector <cathalog_book> &Cathalog); // Вернуть книгу

int vyear(int year) { // Дни в феврале
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) return 29;
    else return 28;
}
int fromtodays(int sday, int smonth, int syear, int monthdays[12], int eday, int emonth, int eyear); // Дней в пределах года
int dayspassed(unsigned int eday, unsigned int emonth, unsigned int eyear, vector <cathalog_book> &Cathalog, int i, int j); // Прошло дней

void takenBooks(vector <cathalog_book> &Cathalog); // Взятые книги
void Menu(vector <cathalog_book> &Cathalog, vector <book *> &allbooks);
void startingConditions(vector <cathalog_book> &Cathalog, vector <book *> &allbooks);

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    vector <book *> allbooks;
    vector <cathalog_book> BestCathalog;
    startingConditions(BestCathalog, allbooks);
    Menu(BestCathalog, allbooks);
    return 0;
}

void vision(vector <int> options) {
    string line;
    for (int c = 0; c < options.size(); c++) {
        switch (options[c]) {
        case -1: line = "\n"; break;
        case 0: line = string(25, '-'); break;
        case 1: line = "\n\x1b[93m1)\x1b[0m Все книги"; break;
        case 2: line = "\n\x1b[93m2)\x1b[0m Создать книгу"; break;
        case 3: line = "\n\x1b[93m3)\x1b[0m Удалить книгу"; break;
        case 4: line = "\n\x1b[96m4)\x1b[0m Все книги каталога"; break;
        case 5: line = "\n\x1b[96m5)\x1b[0m Добавить книгу"; break;
        case 6: line = "\n\x1b[96m6)\x1b[0m Убрать книгу"; break;
        case 7: line = "\n\x1b[92m7)\x1b[0m Информация по ID"; break;
        case 8: line = "\n\x1b[92m8)\x1b[0m Поиск по названию"; break;
        case 9: line = "\n\x1b[92m9)\x1b[0m Поиск по автору"; break;
        case 10: line = "\n\x1b[94m10)\x1b[0m Взять книгу"; break;
        case 11: line = "\n\x1b[94m11)\x1b[0m Вернуть книгу"; break;
        case 12: line = "\n\x1b[94m12)\x1b[0m Взятые книги"; break;
        case 13: line = "   * Программа библиотечного каталога *"; break;
        default: line = "\x1b[91mОШИБКА\x1b[0m";
        }
        cout << line;
    }
}

// Все книги
void booksMenu(vector <book *> &allbooks) {
    vision({ 0, 13, 1, -1, 0 });
    cout << "\x1b[93m   Название - Авторы - Год - Издательство - Страницы\x1b[0m";
    for (int i = 0; i < allbooks.size(); i++) bookInfo(i, allbooks);
    cout << endl;
    system("pause");
}

// Создать книгу
void creationMenu(vector <book *> &allbooks) {
    vision({ 0, 13, 2, -1, 0 });
    string title, publisher, author;
    vector <string> authors;
    unsigned int year, pages, anume;
    cout << "\nНазвание: "; cin >> title;
    cout << "Число авторов: "; cin >> anume;
    for (int i = 0; i < anume; i++) {
        cout << "  " << i << ") Имя: "; cin >> author;
        authors.push_back(author);
    }
    cout << "Год: "; cin >> year;
    cout << "Издательство: "; cin >> publisher;
    cout << "Страницы: "; cin >> pages;
    allbooks.push_back(cbook(title, authors, year, publisher, pages));
}

// Удалить книгу
void annihilationMenu(vector <book *> &allbooks) {
    vision({ 0, 13, 3, -1, 0 });
    cout << "   \x1b[93mНомер\x1b[0m для \x1b[91mудаления\x1b[0m: ";
    int nume;
    cin >> nume;
    delete allbooks[nume];
    allbooks.erase(allbooks.begin() + nume);
}

// Информация о book
void bookInfo(int i, vector <book *> &allbooks) {
    string line;
    cout << "\n" << i << ") " << setw(20) << left;
    cout << allbooks[i]->Title << " | ";

    line = allbooks[i]->Authors[0];
    for (int j = 1; j < allbooks[i]->Authors.size(); j++) {
        line += ", "; line += allbooks[i]->Authors[j];
    }
    cout << setw(30) << left << line;

    cout << " | " << setw(4) << left << allbooks[i]->Year;
    cout << " | " << setw(20) << left << allbooks[i]->Publisher;
    cout << " | " << allbooks[i]->Pages;
}

// Книги в каталоге
void logbooksMenu(vector <cathalog_book> &Cathalog) {
    vision({ 0, 13, 4, -1, 0 });
    cout << "\x1b[96m   ID - Экземпляров - В наличии\x1b[0m";
    string line;
    for (int i = 0; i < Cathalog.size(); i++) {
        cout << "\nID  \x1b[96m" << setw(6) << left << Cathalog[i].ID << "\x1b[0m";
        cout << " | " << setw(4) << left << Cathalog[i].Quantity;
        cout << " | " << setw(4) << left << Cathalog[i].Instances;
    }
    cout << endl;
    system("pause");
}

// Добавить книгу
void attachMenu(vector <cathalog_book> &Cathalog, vector <book *> &allbooks) {
    vision({ 0, 13, 5, -1, 0 });
    cout << "   \x1b[93mНомер\x1b[0m для \x1b[96mдобавления\x1b[0m: "; int nume; cin >> nume;
    cout << "\t\t\t    Всего экземпляров: "; unsigned int quantity; cin >> quantity;
    cout << "\t\t\t    В наличии: "; unsigned int instances; cin >> instances;
    Cathalog.push_back(cathalog_book(*allbooks[nume], quantity, instances));
    reID(Cathalog);
}

// Убрать книгу
void wipeMenu(vector <cathalog_book> &Cathalog) {
    vision({ 0, 13, 6, -1, 0 });
    cout << "   ID для \x1b[91mизъятия\x1b[0m: ";
    int nume;
    cin >> nume;
    Cathalog.erase(Cathalog.begin() + nume);
    reID(Cathalog);
}

// Информация о cathalog_book
void logbookInfo(int ID, vector <cathalog_book> &Cathalog) {
    string line;
    cout << setw(20) << left << Cathalog[ID].Title << " | ";

    line = Cathalog[ID].Authors[0];
    for (int j = 1; j < Cathalog[ID].Authors.size(); j++) {
        line += ", "; line += Cathalog[ID].Authors[j];
    }
    cout << setw(30) << left << line;

    cout << " | " << Cathalog[ID].Year;
    cout << " | " << setw(20) << left << Cathalog[ID].Publisher;
    cout << " | " << Cathalog[ID].Pages;
}

// Информация по ID
void IDInfo(vector <cathalog_book> &Cathalog) {
    vision({ 0, 13, 7, -1, 0 });
    cout << "   ID для получения информации: ";
    int nume;
    cin >> nume;
    logbookInfo(nume, Cathalog);
    cout << endl;
    system("pause");
}

// Поиск ID по названию или автору
void searchID(vector <cathalog_book> &Cathalog, bool byName) {
    bool atleastone = false;
    if (byName) { // По названию
        vision({ 0, 13, 8, -1, 0 });
        cout << "   Название: "; string title; cin >> title;
        cout << "Совпадения: \n";
        for (int i = 0; i < Cathalog.size(); i++) {
            if (Cathalog[i].Title == title) {
                atleastone = true;
                cout << "ID  \x1b[96m" << Cathalog[i].ID << "\x1b[0m" << endl;
            }
        }
    }
    else { // По автору
        vision({ 0, 13, 9, -1, 0 });
        cout << "   Автор: "; string author; cin >> author;
        cout << "Совпадения: \n";
        for (int i = 0; i < Cathalog.size(); i++) {
            for (int j = 0; j < Cathalog[i].Authors.size(); j++) {
                if (Cathalog[i].Authors[j] == author) {
                    atleastone = true;
                    cout << "ID  \x1b[96m" << Cathalog[i].ID << "\x1b[0m" << endl;
                }
            }
        }
    }
    if (!atleastone) cout << "\x1b[91mНе обнаружено\x1b[0m" << endl;
    system("pause");
}

// Взять книгу
void takeBook(vector <cathalog_book> &Cathalog) {
    vision({ 0, 13, 10, -1, 0 });
    int nume;
    reader zero;
    cout << "   ID книги: "; cin >> nume;
    cout << "\t\t\t    Имя: "; cin >> zero.name;
    cout << "\t\t\t    День: "; cin >> zero.sday;
    cout << "\t\t\t    Месяц: "; cin >> zero.smonth; zero.smonth -= 1;
    cout << "\t\t\t    Год: "; cin >> zero.syear;
    Cathalog[nume].Picked.push_back(zero);
    Cathalog[nume].Instances -= 1;
}

// Вернуть книгу
void returnBook(vector <cathalog_book> &Cathalog) {
    vision({ 0, 13, 11, -1, 0 });
    int nume;
    string name;
    cout << "   ID книги: "; cin >> nume;
    cout << "\t\t\t    Имя: "; cin >> name;
    for (int i = 0; i < Cathalog[nume].Picked.size(); i++) {
        if (Cathalog[nume].Picked[i].name == name) {
            Cathalog[nume].Picked.erase(Cathalog[nume].Picked.begin() + i);
            Cathalog[nume].Instances += 1;
        }
    }
}

// Дней в пределах года
int fromtodays(int sday, int smonth, int syear, int monthdays[12], int eday, int emonth, int eyear) {
    int days = 0;
    for (int m = smonth; m < emonth; m++) {
        if (m != 1) days += monthdays[m];
        else days += vyear(syear);
    }
    return days - sday + eday; // Прошло x дней. Сейчас идёт (x + 1) - ый
}

// Прошло дней
int dayspassed(unsigned int eday, unsigned int emonth, unsigned int eyear, vector <cathalog_book> &Cathalog, int i, int j) {
    int monthdays[12] = { 31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int sday = Cathalog[i].Picked[j].sday, smonth = Cathalog[i].Picked[j].smonth, syear = Cathalog[i].Picked[j].syear;

    int days = 0;
    if (syear == eyear) days += fromtodays(sday, smonth, syear, monthdays, eday, emonth, eyear); // Первый и последний год
    else {
        for (int cyear = syear; cyear <= eyear; cyear++) {
            if (cyear == syear) { // Первый и не последний год
                days += fromtodays(sday, smonth, syear, monthdays, 31, 11, eyear) + 1;
            }
            else if (cyear == eyear) { // Последний год
                days += fromtodays(1, 0, eyear, monthdays, eday, emonth, eyear);
            }
            else { // Не первый и не последний год
                days += fromtodays(1, 0, cyear, monthdays, 31, 11, eyear) + 1;
            }
        }
    }
    return days;
}

// Взятые книги
void takenBooks(vector <cathalog_book> &Cathalog) {
    vision({ 0, 13, 12, -1, 0 });
    struct tm stime;
    time_t seconds = time(0);
    localtime_s(&stime, &seconds);
    unsigned int eday = stime.tm_mday, emonth = stime.tm_mon, eyear = stime.tm_year + 1900;
    cout << "   Настоящая дата: \x1b[96m";
    if (eday < 10) cout << "0";
    cout << eday << ".";
    if (emonth < 10) cout << "0";
    cout << emonth + 1 << ".";
    cout << eyear << "\x1b[0m";

    for (int i = 0; i < Cathalog.size(); i++) {
        for (int j = 0; j < Cathalog[i].Picked.size(); j++) {
            cout << "\nID  \x1b[96m" << setw(8) << left << Cathalog[i].ID << "\x1b[0m";
            cout << " | Имя: " << setw(16) << left << Cathalog[i].Picked[j].name;

            cout << " | Дата: ";
            if (Cathalog[i].Picked[j].sday < 10) cout << "0";
            cout << Cathalog[i].Picked[j].sday << ".";
            if (Cathalog[i].Picked[j].smonth < 10) cout << "0";
            cout << Cathalog[i].Picked[j].smonth + 1 << ".";
            cout << Cathalog[i].Picked[j].syear;

            cout << " | Прошло дней: ";
            int days = dayspassed(eday, emonth, eyear, Cathalog, i, j);
            // В течение года - размытое понятие: 365 или 366
            if (days < 365) cout << "\x1b[92m";
            else cout << "\x1b[91m";
            cout << days << "\x1b[0m";
        }
    }
    cout << endl;
    system("pause");
}

void Menu(vector <cathalog_book> &Cathalog, vector <book *> &allbooks) {
    string choice;
    bool work = true;
    while (true) {
        vision({ 0, 13, 1, 2, 3, -1, 0, 4, 5, 6, -1, 0, 7, 8, 9, -1, 0, 10, 11, 12, -1, 0 });
        cout << "   Выбор: ";
        cin >> choice;
        if (!all_of(choice.begin(), choice.end(), isdigit)) break; // Является ли значение числовым
        system("cls");
        switch (stoi(choice)) {
        case 1: booksMenu(allbooks); break;
        case 2: creationMenu(allbooks); break;
        case 3: annihilationMenu(allbooks); break;
        case 4: logbooksMenu(Cathalog); break;
        case 5: attachMenu(Cathalog, allbooks); break;
        case 6: wipeMenu(Cathalog); break;
        case 7: IDInfo(Cathalog); break;
        case 8: searchID(Cathalog, 1); break;
        case 9: searchID(Cathalog, 0); break;
        case 10: takeBook(Cathalog); break;
        case 11: returnBook(Cathalog); break;
        case 12: takenBooks(Cathalog); break;
        default: work = false;
        }
        if (!work) break;
        system("cls");
    }
}

void startingConditions(vector <cathalog_book> &Cathalog, vector <book *> &allbooks) {
    allbooks.push_back(cbook("Книга_о_Земле", { "Житель_Земли", "Житель_Нибиру" }, 2022, "Альфа", 1200));
    allbooks.push_back(cbook("Книга_о_Марсе", { "Житель_Марса" }, 2017, "Бета", 1500));
    allbooks.push_back(cbook("Книга_о_Венере", { "Житель_Венеры" }, 2021, "Гамма", 700));
    allbooks.push_back(cbook("Книга_о_Нептуне", { "Житель_Нептуна" }, 3020, "Дельта", 400));
    allbooks.push_back(cbook("Книга_о_Юпитере", { "Житель_Юпитера", "Житель_Сатурна" }, 1804, "Эпсилон", 9000));

    Cathalog.push_back(cathalog_book(*allbooks[0], 50, 50));
    Cathalog.push_back(cathalog_book(*allbooks[2], 100, 100));
    Cathalog.push_back(cathalog_book(*allbooks[3], 100, 20));
    reID(Cathalog);

    Cathalog[1].Picked.push_back(reader("HumanNumberOne", 1, 2, 2022));
    Cathalog[2].Picked.push_back(reader("HumanNumberOne", 5, 7, 2020));
}
