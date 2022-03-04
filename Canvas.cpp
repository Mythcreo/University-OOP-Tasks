#include "Canvas.h"
#include <windows.h>
#include <iostream>
#include <vector>
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

Rectangles::Rectangles(int x1, int y1, int x2, int y2, bool color) {
	leftUp.Set(x1, y1); leftDown.Set(x1, y2);
	rightUp.Set(x2, y1); rightDown.Set(x2, y2);
	this->color = color;
}
void Rectangles::Set(int x1, int y1, int x2, int y2, bool color) {
	leftUp.Set(x1, y1); leftDown.Set(x1, y2);
	rightUp.Set(x2, y1); rightDown.Set(x2, y2);
	this->color = color;
}
int Rectangles::GetLUpX() { return leftUp.GetX(); }
int Rectangles::GetLUpY() { return leftUp.GetY(); }
int Rectangles::GetLDownX() { return leftDown.GetX(); }
int Rectangles::GetLDownY() { return leftDown.GetY(); }
int Rectangles::GetRUpX() { return rightUp.GetX(); }
int Rectangles::GetRUpY() { return rightUp.GetY(); }
int Rectangles::GetRDownX() { return rightDown.GetX(); }
int Rectangles::GetRDownY() { return rightDown.GetX(); }

Ellipses::Ellipses(int x1, int y1, int x2, int y2, bool color) {
	leftUp.Set(x1, y1);
	rightDown.Set(x2, y2);
	this->color = color;
}
void Ellipses::Set(int x1, int y1, int x2, int y2, bool color) {
	leftUp.Set(x1, y1);
	rightDown.Set(x2, y2);
	this->color = color;
}
int Ellipses::GetLUpX() { return leftUp.GetX(); }
int Ellipses::GetLUpY() { return leftUp.GetY(); }
int Ellipses::GetRDownX() { return rightDown.GetX(); }
int Ellipses::GetRDownY() { return rightDown.GetX(); }

Polygons::Polygons(int oneX, int oneY, int twoX, int twoY, int threeX, int threeY, bool color) {
	one.Set(oneX, oneY);
	two.Set(twoX, twoY);
	three.Set(threeX, threeY);
}
void Polygons::Set(int oneX, int oneY, int twoX, int twoY, int threeX, int threeY, bool color) {
	one.Set(oneX, oneY);
	two.Set(twoX, twoY);
	three.Set(threeX, threeY);
}
int Polygons::GetOneX() { return one.GetX(); }
int Polygons::GetOneY() { return one.GetY(); }
int Polygons::GetTwoX() { return two.GetX(); }
int Polygons::GetTwoY() { return two.GetY(); }
int Polygons::GetThreeX() { return three.GetX(); }
int Polygons::GetThreeY() { return three.GetY(); }

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
		cout << ++counter << ") ";
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
				<< p->GetRDownX() << ", " << p->GetRDownY() << ")" << endl;
		}
		else if (typenume == 4) { // Для прямоугольника
			Rectangles *p = (Rectangles *)(*itera).GetO();
			cout << "Rectangle (" << p->GetLUpX() << ", " << p->GetLUpY() << ", "
				<< p->GetRDownX() << ", " << p->GetRDownY() << ")" << endl;
		}
		else if (typenume == 5) { // Для многоугольника
			Polygons *p = (Polygons *)(*itera).GetO();
			cout << "Polygon (" << p->GetOneX() << ", " << p->GetOneY() << ", "
				<< p->GetTwoX() << ", " << p->GetTwoY() << ", "
				<< p->GetThreeX() << ", " << p->GetThreeY() << ")" << endl;
		}
	}
}
void Graphics::Show(int nume, HWND &hwnd, HDC &hdc) {
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
		SelectObject(hdc, GetStockObject(WHITE_BRUSH));
		Ellipse(hdc, p->GetLUpX(), p->GetLUpY(), p->GetRDownX(), p->GetRDownY());
	}
	else if (typenume == 4) { // Для прямоугольника
		SelectObject(hdc, GetStockObject(NULL_BRUSH));
		Rectangles *p = (Rectangles *)(*itera).GetO();
		Rectangle(hdc, p->GetLUpX(), p->GetLUpY(), p->GetRDownX(), p->GetRDownY());
	}
	else if (typenume == 5) { // Для многоугольника
		Polygons *p = (Polygons *)(*itera).GetO();
		SelectObject(hdc, GetStockObject(WHITE_BRUSH));
		MoveToEx(hdc, 700, 300, NULL);
		LineTo(hdc, p->GetOneX(), p->GetOneY());
		LineTo(hdc, p->GetTwoX(), p->GetTwoY());
		LineTo(hdc, p->GetThreeX(), p->GetThreeY());
		LineTo(hdc, 700, 300);
	}
	ReleaseDC(hwnd, hdc);
}
void Graphics::Add(Primitive zero) { forms.push_back(zero); }
void Graphics::Remove(int nume) { forms.erase(forms.begin() + nume - 1); }
void Graphics::Clear() { forms.clear(); }
