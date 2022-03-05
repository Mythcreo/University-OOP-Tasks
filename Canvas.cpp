#include "Canvas.h"
#include <windows.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include "conio.h"
using namespace std;
Point::Point(int x, int y) {
	this->x = x;
	this->y = y;
}
void Point::Set(int x, int y) {
	this->x = x;
	this->y = y;
}
int Point::GetX() { return x; }
int Point::GetY() { return y; }
Line::Line(int x1, int y1, int x2, int y2) {
	start.Set(x1, y1);
	end.Set(x2, y2);
}
void Line::Set(int x1, int y1, int x2, int y2) {
	start.Set(x1, y1);
	end.Set(x2, y2);
}
int Line::GetSX() { return start.GetX(); }
int Line::GetSY() { return start.GetY(); }
int Line::GetEX() { return end.GetX(); }
int Line::GetEY() { return end.GetY(); }

Rectangles::Rectangles(int x1, int y1, int x2, int y2, bool is_fill, int r, int g, int b) {
	leftUp.Set(x1, y1); leftDown.Set(x1, y2);
	rightUp.Set(x2, y1); rightDown.Set(x2, y2);
	this->is_fill = is_fill;
	this->r = r; this->g = g; this->b = b;
}
void Rectangles::Set(int x1, int y1, int x2, int y2, bool is_fill, int r, int g, int b) {
	leftUp.Set(x1, y1); leftDown.Set(x1, y2);
	rightUp.Set(x2, y1); rightDown.Set(x2, y2);
	this->is_fill = is_fill;
	this->r = r; this->g = g; this->b = b;
}
int Rectangles::GetLUpX() { return leftUp.GetX(); }
int Rectangles::GetLUpY() { return leftUp.GetY(); }
int Rectangles::GetLDownX() { return leftDown.GetX(); }
int Rectangles::GetLDownY() { return leftDown.GetY(); }
int Rectangles::GetRUpX() { return rightUp.GetX(); }
int Rectangles::GetRUpY() { return rightUp.GetY(); }
int Rectangles::GetRDownX() { return rightDown.GetX(); }
int Rectangles::GetRDownY() { return rightDown.GetX(); }
int Rectangles::GetR() { return r; }
int Rectangles::GetG() { return g; }
int Rectangles::GetB() { return b; }
bool Rectangles::GetFill() { return is_fill; }

Ellipses::Ellipses(int x1, int y1, int x2, int y2, bool is_fill, int r, int g, int b) {
	leftUp.Set(x1, y1);
	rightDown.Set(x2, y2);
	this->is_fill = is_fill;
	this->r = r; this->g = g; this->b = b;
}
void Ellipses::Set(int x1, int y1, int x2, int y2, bool is_fill, int r, int g, int b) {
	leftUp.Set(x1, y1);
	rightDown.Set(x2, y2);
	this->is_fill = is_fill;
	this->r = r; this->g = g; this->b = b;
}
int Ellipses::GetLUpX() { return leftUp.GetX(); }
int Ellipses::GetLUpY() { return leftUp.GetY(); }
int Ellipses::GetRDownX() { return rightDown.GetX(); }
int Ellipses::GetRDownY() { return rightDown.GetX(); }
int Ellipses::GetR() { return r; }
int Ellipses::GetG() { return g; }
int Ellipses::GetB() { return b; }
bool Ellipses::GetFill() { return is_fill; }

Polygons::Polygons(vector <POINT> vec, int pointsnume, bool is_fill, int r, int g, int b) {
	vecpoints = new POINT[vec.size()];
	for (int i = 0; i < vec.size(); i++) {
		vecpoints[i] = vec[i];
	}
	this->pointsnume = pointsnume;
	this->is_fill = is_fill;
	this->r = r; this->g = g; this->b = b;
}
void Polygons::Set(vector <POINT> vec, int pointsnume, bool is_fill, int r, int g, int b) {
	vecpoints = new POINT[vec.size()];
	for (int i = 0; i < vec.size(); i++) {
		vecpoints[i] = vec[i];
	}
	this->pointsnume = pointsnume;
	this->is_fill = is_fill;
	this->r = r; this->g = g; this->b = b;
}

POINT *Polygons::GetVecpoints() { return vecpoints; }
int Polygons::GetPointsnume() { return pointsnume; }
int Polygons::GetR() { return r; }
int Polygons::GetG() { return g; }
int Polygons::GetB() { return b; }
bool Polygons::GetFill() { return is_fill; }

Primitive::Primitive(void *object, int type) {
	this->object = object;
	this->type = type;
}
int Primitive::GetType() { return type; }
void *Primitive::GetO() { return object; }

Graphics::Graphics(vector <Primitive> forms) {
	this->forms = forms;
}
void Graphics::Info() {
	int typenume, counter = 0;
	for (vector <Primitive>::iterator itera = forms.begin(); itera != forms.end(); itera++) {
		cout << "\x1b[96m" << ++counter << ")\x1b[0m ";
		typenume = (*itera).GetType(); // Тип графического примитива
		if (typenume == 1) { // Для точки
			Point *p = (Point *)(*itera).GetO();
			cout << "Point (" << p->GetX() << ", " << p->GetY() << ")" << endl;
		}
		else if (typenume == 2) { // Для отрезка
			Line *p = (Line *)(*itera).GetO();
			cout << "Line (" << p->GetSX() << ", " << p->GetSY() << ", "
				<< p->GetEX() << ", " << p->GetEY() << ")" << endl;
		}
		else if (typenume == 3) { // Для эллипса
			Ellipses *p = (Ellipses *)(*itera).GetO();
			cout << "Ellipse (" << p->GetLUpX() << ", " << p->GetLUpY() << ", "
				<< p->GetRDownX() << ", " << p->GetRDownY()
				<< ").   Цвета RGB(" << p->GetR() << ", " << p->GetG() << ", " << p->GetB() << ").   Закраска: " << p->GetFill() << endl;
		}
		else if (typenume == 4) { // Для прямоугольника
			Rectangles *p = (Rectangles *)(*itera).GetO();
			cout << "Rectangle (" << p->GetLUpX() << ", " << p->GetLUpY() << ", "
				<< p->GetRDownX() << ", " << p->GetRDownY()
				<< ").   Цвета RGB(" << p->GetR() << ", " << p->GetG() << ", " << p->GetB() << ").   Закраска: " << p->GetFill() << endl;
		}
		else if (typenume == 5) { // Для многоугольника	
			Polygons *p = (Polygons *)(*itera).GetO();
			POINT zero;
			cout << "Polygon (";
			zero = p->GetVecpoints()[0];
			cout << zero.x << ", " << zero.y;
			for (int i = 1; i < p->GetPointsnume(); i++) {
				zero = p->GetVecpoints()[i];
				cout << ", " << zero.x << ", " << zero.y;
			}
			cout << ").   Цвета RGB(" << p->GetR() << ", " << p->GetG() << ", " << p->GetB()
				 << ").   Закраска: " << p->GetFill() << endl;
		}
	}
}
void Graphics::Show(int nume, HWND &hwnd) {
	HDC hdc = GetDC(hwnd); // HDC - Handle to device context
	vector <Primitive>::iterator itera = forms.begin() + nume - 1;
	int typenume = (*itera).GetType();
	SelectObject(hdc, GetStockObject(WHITE_PEN));
	if (typenume == 2) { // Для отрезка
		Line *p = (Line *)(*itera).GetO();
		MoveToEx(hdc, p->GetSX(), p->GetSY(), NULL);
		LineTo(hdc, p->GetEX(), p->GetEY());
	}
	else if (typenume == 3) { // Для эллипса
		Ellipses *p = (Ellipses *)(*itera).GetO();
		SelectObject(hdc, GetStockObject(DC_PEN)); // Выбор пера
		SetDCPenColor(hdc, RGB(p->GetR(), p->GetG(), p->GetB())); // Установка цвета контура
		SetDCBrushColor(hdc, RGB(p->GetR(), p->GetG(), p->GetB())); // Установка цвета закраски
		if (p->GetFill()) SelectObject(hdc, GetStockObject(DC_BRUSH)); // Выбор кисти
		else SelectObject(hdc, GetStockObject(NULL_BRUSH)); // Отключение закраски
		Ellipse(hdc, p->GetLUpX(), p->GetLUpY(), p->GetRDownX(), p->GetRDownY());
	}
	else if (typenume == 4) { // Для прямоугольника
		Rectangles *p = (Rectangles *)(*itera).GetO();
		SelectObject(hdc, GetStockObject(DC_PEN)); // Выбор пера
		SetDCPenColor(hdc, RGB(p->GetR(), p->GetG(), p->GetB())); // Установка цвета контура
		SetDCBrushColor(hdc, RGB(p->GetR(), p->GetG(), p->GetB())); // Установка цвета закраски
		if (p->GetFill()) SelectObject(hdc, GetStockObject(DC_BRUSH)); // Выбор кисти
		else SelectObject(hdc, GetStockObject(NULL_BRUSH)); // Отключение закраски
		Rectangle(hdc, p->GetLUpX(), p->GetLUpY(), p->GetRDownX(), p->GetRDownY());
	}
	else if (typenume == 5) { // Для многоугольника
		Polygons *p = (Polygons *)(*itera).GetO();
		SelectObject(hdc, GetStockObject(DC_PEN)); // Выбор пера
		SetDCPenColor(hdc, RGB(p->GetR(), p->GetG(), p->GetB())); // Установка цвета контура
		SetDCBrushColor(hdc, RGB(p->GetR(), p->GetG(), p->GetB())); // Установка цвета закраски
		if (p->GetFill()) SelectObject(hdc, GetStockObject(DC_BRUSH)); // Выбор кисти
		//else SelectObject(hdc, GetStockObject(NULL_BRUSH)); // Отключение закраски
		Polygon(hdc, p->GetVecpoints(), p->GetPointsnume());
	}
	ReleaseDC(hwnd, hdc);
}
void Graphics::Add(Primitive zero) { forms.push_back(zero); }
void Graphics::Remove(int nume) { forms.erase(forms.begin() + nume - 1); }
void Graphics::Clear() { forms.clear(); }

void add_figure(int *coord1, int *coord2, int *coord3, int *coord4, bool *is_fill, int *r, int *g, int *b, bool is_not_line) {
	cout << "Координаты первой точки: ";
	cin >> *coord1 >> *coord2;
	cout << "Координаты второй точки: ";
	cin >> *coord3 >> *coord4;
	if (is_not_line) {
		cout << "RGB цвета: ";
		cin >> *r >> *g >> *b;
		cout << "Фигура закрашена? (1 | 0): ";
		cin >> *is_fill;
	}
}

void Menu::Options(Graphics &Settings) {
	setlocale(LC_ALL, "Russian");
	HWND hwnd = GetConsoleWindow(); // HWND - Handle to a window

	// Закоментировать для отключения вступительного эффекта
	Intro(hwnd, 2500, 10, 10, 100, true);

	string choice;
	int item, itemNumbers;
	while (true)
	{
		// Повторение методов в функции Show
		cout << string(90, '-') << "\n\t\t\t\t\x1b[93mAlternative Paint Options\x1b[0m\n"
			<< string(90, '-') << endl;
		cout << "\x1b[96m0)\x1b[0m Выход\n";
		cout << "\x1b[96m1)\x1b[0m Нарисовать фигуры\n";
		cout << "\x1b[96m2)\x1b[0m Показать информацию о списке\n";
		cout << "\x1b[96m3)\x1b[0m Добавить фигуру\n";
		cout << "\x1b[96m4)\x1b[0m Убрать фигуру\n";
		cout << "\x1b[96m5)\x1b[0m Очищение списка\n";
		cout << "Выбор: "; cin >> choice; cout << endl;

		if (choice == "0") break;
		else if (choice == "1") {
			vector <int> numbers; // Хранятся номера элементов в списке для рисования
			Settings.Info(); // Для выбора фигур намного удобнее, когда не отдельно
			cout << "Число фигур: ";
			cin >> itemNumbers;
			for (int i = 0; i < itemNumbers; i++) {
				cout << "\x1b[96m" << i + 1 << "\x1b[0m) Номер элемента: ";
				cin >> item;
				numbers.push_back(item);
			}
			system("cls");
			cout << "Клавиша 'p' для обновления...\nEscape для завершения...\n";
			char iKey = 0;
			while (iKey != 27) {
				if (_kbhit()) {
					iKey = _getch();
					switch (iKey) {
					case 112:
						for (int i = 0; i < itemNumbers; i++) {
							Settings.Show(numbers[i], hwnd);
						}
						break;
					}
				}
			}
		}
		else if (choice == "2") {
			Settings.Info();
		}
		else if (choice == "3") {
			cout << "\x1b[96m0)\x1b[0m Отрезок\n";
			cout << "\x1b[96m1)\x1b[0m Прямоугольник\n";
			cout << "\x1b[96m2)\x1b[0m Эллипс\n";
			cout << "\x1b[96m3)\x1b[0m Многоугольник\n";
			int choice_figure, coord1, coord2, coord3, coord4, r, g, b;
			bool is_fill;
			cout << "Выбор: "; cin >> choice_figure; cout << endl;
			if (choice_figure == 0) {
				add_figure(&coord1, &coord2, &coord3, &coord4, &is_fill, &r, &g, &b, 0);
				Settings.Add(Primitive(new Line(coord1, coord2, coord3, coord4), 2));
			}
			else if (choice_figure == 1) {
				add_figure(&coord1, &coord2, &coord3, &coord4, &is_fill, &r, &g, &b, 1);
				Settings.Add(Primitive(new Rectangles(coord1, coord2, coord3, coord4, is_fill, r, g, b), 4));
			}
			else if (choice_figure == 2) {
				add_figure(&coord1, &coord2, &coord3, &coord4, &is_fill, &r, &g, &b, 1);
				Settings.Add(Primitive(new Ellipses(coord1, coord2, coord3, coord4, is_fill, r, g, b), 3));
			}
			else if (choice_figure == 3) {
				int count_points, counter = 0;
				vector <POINT> points;
				cout << "Число вершин: ";
				cin >> count_points;
				for (int i = 0; i < count_points; i++) {
					POINT a;
					int x, y;
					cout << "Точка " << ++counter << ". Введите x и y: ";
					cin >> a.x >> a.y;
					points.push_back(a);
				}
				cout << "RGB цвета: ";
				cin >> r >> g >> b;
				cout << "Фигура закрашена? (1 | 0): ";
				bool is_fill;
				cin >> is_fill;
				Settings.Add(Primitive(new Polygons(points, count_points, is_fill, r, g, b), 5));
			}
		}
		else if (choice == "4") {
			cout << "Номер элемента для удаления: ";
			cin >> item;
			Settings.Remove(item);
		}
		else if (choice == "5") {
			Settings.Clear();
		}
		system("pause");
		system("cls");
		Intro(hwnd, 400, 25, 25, 25, false);
	}
}

void Intro(HWND &hwnd, int timedelay, int t1, int t2, int t3, bool start) {
	HDC hdc = GetDC(hwnd); // HDC - Handle to device context
	for (int i = 150; i < 800; i += t1) {
		SelectObject(hdc, GetStockObject(DC_PEN));
		this_thread::sleep_for(chrono::milliseconds(10)); // Пауза на определённое время, нужны include <chrono> и <thread>
		SelectObject(hdc, GetStockObject(DC_BRUSH));
		SetDCBrushColor(hdc, RGB(0, 255, 0));
		SetDCPenColor(hdc, RGB(0, 255, 0));
		Rectangle(hdc, i, 130, i + 300, 100);
	}
	for (int i = 150; i < 500; i += t2) {
		SelectObject(hdc, GetStockObject(DC_PEN));
		this_thread::sleep_for(chrono::milliseconds(25));
		SelectObject(hdc, GetStockObject(DC_BRUSH));
		SetDCBrushColor(hdc, RGB(0, 0, 255));
		SetDCPenColor(hdc, RGB(0, 0, 255));
		Rectangle(hdc, i, 130, i + 300, 100);
	}
	for (int i = 150; i < 170; i += t3) {
		SelectObject(hdc, GetStockObject(DC_PEN));
		this_thread::sleep_for(chrono::milliseconds(150));
		SelectObject(hdc, GetStockObject(DC_BRUSH));
		SetDCBrushColor(hdc, RGB(255, 0, 0));
		SetDCPenColor(hdc, RGB(255, 0, 0));
		Rectangle(hdc, i, 130, i + 300, 100);
	}
	if (start) {
		for (int i = 400; i < 550; i += 10) {
			SelectObject(hdc, GetStockObject(WHITE_PEN));
			this_thread::sleep_for(chrono::milliseconds(20));
			SelectObject(hdc, GetStockObject(NULL_BRUSH));
			Ellipse(hdc, i, 190, i + 300, 460);
		}
		for (int i = 30; i < 300; i += 10) {
			SelectObject(hdc, GetStockObject(WHITE_PEN));
			this_thread::sleep_for(chrono::milliseconds(20));
			SelectObject(hdc, GetStockObject(NULL_BRUSH));
			Ellipse(hdc, 360, i + 140, 880, i + 230);
		}
	}
	cout << "\n\t\t\t\t\t    Alternative Paint Project";
	this_thread::sleep_for(chrono::milliseconds(timedelay));
	system("cls");
}
