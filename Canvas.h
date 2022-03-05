#pragma once
#include <windows.h>
#include <iostream>
#include <vector>
using namespace std;

// Класс точки
class Point {
private:
	int x{}, y{};
public:
	Point() {}
	Point(int x, int y);
	void Set(int x, int y);
	int GetX();
	int GetY();
};

// Класс отрезка
class Line {
private:
	Point start, end;
public:
	Line(int x1, int y1, int x2, int y2);
	void Set(int x1, int y1, int x2, int y2);
	int GetSX();
	int GetSY();
	int GetEX();
	int GetEY();
};

// Класс прямоугольника
class Rectangles {
private:
	Point leftUp, leftDown, rightUp, rightDown;
	bool is_fill{};
	int r{}, g{}, b{};
public:
	Rectangles(int x1, int y1, int x2, int y2, bool is_fill, int r, int g, int b);
	void Set(int x1, int y1, int x2, int y2, bool is_fill, int r, int g, int b);
	int GetLUpX();
	int GetLUpY();
	int GetLDownX();
	int GetLDownY();
	int GetRUpX();
	int GetRUpY();
	int GetRDownX();
	int GetRDownY();
	int GetR();
	int GetG();
	int GetB();
	bool GetFill();
};

// Класс эллипса
class Ellipses {
private:
	Point leftUp, rightDown;
	bool is_fill{};
	int r{}, g{}, b{};
public:
	Ellipses(int x1, int y1, int x2, int y2, bool is_fill, int r, int g, int b);
	void Set(int x1, int y1, int x2, int y2, bool is_fill, int r, int g, int b);
	int GetLUpX();
	int GetLUpY();
	int GetRDownX();
	int GetRDownY();
	int GetR();
	int GetG();
	int GetB();
	bool GetFill();
};

// Класс многоугольника
class Polygons {
private:
	POINT *vecpoints;
	int pointsnume{};
	bool is_fill{};
	int r{}, g{}, b{};
public:
	// Ожидается реализация применения bool color, пока не используется
	Polygons(vector <POINT> vec, int pointsnume, bool is_fill, int r, int g, int b);
	void Set(vector <POINT> vec, int pointsnume, bool is_fill, int r, int g, int b);
	POINT *GetVecpoints();
	int GetPointsnume();
	int GetR();
	int GetG();
	int GetB();
	bool GetFill();
};

// Хранится указатель к графическому примитиву вместе с его типом
class Primitive {
private:
	void *object{};
	int type{};
public:
	Primitive() { }
	Primitive(void *object, int type);
	int GetType();
	void *GetO();
};

// При создании средства рисования Graphics вводятся графические примитивы вместе с их типами
// Point - 1, Line - 2, Ellipses - 3, Rectangles - 4, Polygon - 5
class Graphics {
private:
	vector <Primitive> forms;
public:
	Graphics() { }
	Graphics(vector <Primitive> forms);
	void Info();
	void Show(int nume, HWND &hwnd);
	void Add(Primitive zero);
	void Remove(int nume);
	void Clear();
};

void add_figure(int *coord1, int *coord2, int *coord3, int *coord4, bool *is_fill, int *r, int *g, int *b, bool is_not_line);

void Intro(HWND &hwnd, int timedelay, int t1, int t2, int t3, bool start);

class Menu {
public:
	void Options(Graphics &Settings);
};
