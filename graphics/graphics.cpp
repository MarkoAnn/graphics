#include <iostream>
#include "graphics.h"
#pragma comment(lib,"graphics.lib")

void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3) {
    line(x1, y1, x2, y2);
    line(x2, y2, x3, y3);
    line(x3, y3, x1, y1);
}


int main() {
    initwindow(500, 500);
    int x1;
    int y1;
    int x2;
    int y2; 
    int x3;
    int y3;
    std::cout << "введите точки треугольника: ";
    std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

    drawTriangle(x1, y1, x2, y2, x3, y3);


    /*
    delay(2000);
    cleardevice();
    setbkcolor(BLACK);
    */

    getch();
    closegraph();
    return 0;
}