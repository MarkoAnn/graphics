#include <iostream>
#include "graphics.h"
#pragma comment(lib,"graphics.lib")

static int windowWidth;
static int windowHeight;

void drawSquare(int x1, int y1, int size) {
    rectangle(x1, y1, x1 + size, y1 + size);
}

void moveSquare(char key, int& x, int& y) {
    switch (key) {
    case 'd':
        x++;
        break;
    case 's':
        y++;
        break;
    case 'w':
        y--;
        break;
    case 'a':
        x--;
        break;
    default:
        break;
    }
}

int main() {
    initwindow(500, 500);
    windowWidth = getmaxx();
    windowHeight = getmaxy();
    std::cout << "graphic window size: x=" << windowWidth << " y=" << windowHeight << std::endl;
    int x = 0;
    int y = 0;
    int size = 45;

    while (true) {
        cleardevice();
        drawSquare(x, y, size);
        if (kbhit()) {
            char key = getch();
            moveSquare(key, x, y);
        }

        delay(10);
    }
    getch();
    closegraph();
    return 0;
}