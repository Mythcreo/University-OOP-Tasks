#include <iostream>
#include <vector>
using namespace std;

class base {
public:
	virtual void show() {};
};

template <class T> class Point2D {
protected:
	T x, y;
public:
	Point2D(T x, T y) : x(x), y(y) {};
};


template <class T> class Z {
protected:
	T z;
public:
	Z(T z) : z(z) {};
};

template <class T> class H {
protected:
	T h;
public:
	H(T h) : h(h) {};
};

template <class T> class Point3Dh : public Point2D <T>, public Z <T>, public H <T>, base {
public:
	Point3Dh(T x, T y, T z, T h) : Point2D <T> (x, y), Z <T> (z), H <T> (h) {};
	void show() {
		cout << "(" << this->x << ", " << this->y << ", " << this->z << ", " << this->h << ")" << endl;
	}
};

int main()
{
	Point3Dh <int> one(1, 2, 3, 4);
	Point3Dh <short> two(10, 20, 30, 40);
	Point3Dh <double> three(1.77, 2.77, 3.77, 4.77);
	Point3Dh <float> four(1.5, 2.5, 3.5, 4.5);
	Point3Dh <long> five(100, 200, 300, 400);

	vector <base *> all;

	all.push_back((base *) & one);
	all.push_back((base *) & two);
	all.push_back((base *) & three);
	all.push_back((base *) & four);
	all.push_back((base *) & five);

	for (int i = 0; i < 5; i++) all[i]->show();

	return 0;
}
