#include "Canvas.h"
#include <windows.h>
int main()
{
	HWND hwnd = GetConsoleWindow(); // HWND - Handle to a window
	HDC hdc = GetDC(hwnd); // HDC - Handle to device context
	Graphics Settings(vector <Primitive> { 
		Primitive(new Line(500, 100, 700, 500), 2),
		Primitive(new Rectangles(100, 180, 400, 400, 1), 4),
		Primitive(new Ellipses(200, 200, 300, 350, 1), 3),
		Primitive(new Rectangles(500, 500, 600, 600, 0), 4)
	});
	Settings.Add(Primitive(new Polygons(800, 400, 1000, 300, 800, 200, 0), 5));
	Settings.Remove(4);

	Settings.Info();
	system("pause");
	system("cls");
	//Settings.Clear(); // Очищение списка
	Settings.Show(1, hwnd, hdc);
	Settings.Show(2, hwnd, hdc);
	Settings.Show(3, hwnd, hdc);
	Settings.Show(4, hwnd, hdc);
	return 0;
}
