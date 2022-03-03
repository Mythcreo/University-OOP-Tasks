#pragma once
#include <windows.h>
#include <iostream>
#include <vector>
using namespace std;

// ����� �����
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

// ����� �������
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

// ����� ��������������
class Rectangles {
private:
	Point leftUp, leftDown, rightUp, rightDown;
	bool color{};
public:
	Rectangles(int x1, int y1, int x2, int y2, bool color);
	void Set(int x1, int y1, int x2, int y2, bool color);
	int GetLUpX();
	int GetLUpY();
	int GetLDownX();
	int GetLDownY();
	int GetRUpX();
	int GetRUpY();
	int GetRDownX();
	int GetRDownY();
};

// ����� �������
class Ellipses {
private:
	Point leftUp, rightDown;
	bool color{};
public:
	Ellipses(int x1, int y1, int x2, int y2, bool color);
	void Set(int x1, int y1, int x2, int y2, bool color);
	int GetLUpX();
	int GetLUpY();
	int GetRDownX();
	int GetRDownY();
};

// ����� ��������������
class Polygons {
private:
	Point one, two, three;
	bool color{};
public:
	Polygons(int oneX, int oneY, int twoX, int twoY, int threeX, int threeY, bool color);
	void Set(int oneX, int oneY, int twoX, int twoY, int threeX, int threeY, bool color);
	int GetOneX();
	int GetOneY();
	int GetTwoX();
	int GetTwoY();
	int GetThreeX();
	int GetThreeY();
};

// �������� ��������� � ������������ ��������� ������ � ��� �����
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

// ��� �������� �������� ��������� Graphics �������� ����������� ��������� ������ � �� ������
// Point - 1, Line - 2, Ellipses - 3, Rectangles - 4, Polygon - 5
class Graphics {
private:
	vector <Primitive> forms;
public:
	Graphics() { }
	Graphics(vector <Primitive> forms);
	void Info();
	void Show(int nume);
	void Add(Primitive zero);
	void Remove(int nume);
	void Clear();
};