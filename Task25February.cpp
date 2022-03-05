#include "Canvas.h"
using namespace std;

int main() {
    Graphics StartSettings(vector <Primitive> {
        Primitive(new Line(500, 100, 700, 500), 2),
            Primitive(new Rectangles(100, 180, 400, 400, 1, 255, 255, 255), 4),
            Primitive(new Ellipses(200, 200, 300, 350, 1, 0, 0, 255), 3),
            Primitive(new Rectangles(500, 500, 600, 600, 0, 255, 255, 255), 4),
            Primitive(new Polygons({ {800, 400}, {1000, 300}, {800, 200} }, 3, 1, 0, 0, 255), 5),
            Primitive(new Polygons({ {800, 400}, {1000, 300}, {400, 100}, {100, 400} }, 4, 1, 0, 255, 0), 5)
    });

    Menu DesignSolution;
    DesignSolution.Options(StartSettings);

    return 0;
}
