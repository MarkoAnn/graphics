#include <iostream>
#include "graphics.h"
#pragma comment(lib,"graphics.lib")

static int windowWidth; 
static int windowHeight; 

void drawSquare(int x1, int y1, int size) {
    rectangle(x1, y1, x1 + size, y1 + size);
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
            if (key == 'd') {
                x++;
            }
            else if (key == 's') {
                y++;
            }
            else if (key == 'w') {
                y--;
            }
            else if (key == 'a') {
                x--;
            }
        }

        delay(10);
    }
    getch();
    closegraph();
    return 0;
}
