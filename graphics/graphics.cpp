#include <iostream>
#include "graphics.h"
#pragma comment(lib,"graphics.lib")

static int windowWidth;
static int windowHeight;

void drawSquare(int x1, int y1, int size) {
    rectangle(x1, y1, x1 + size, y1 + size); // Рисует квадрат
}

void moveSquare(char key, int& x, int& y, int size) {
    switch (key) {
    case 'd':
        x += size;
        break;
    case 's':
        y += size;
        break;
    case 'w':
        y -= size;
        break;
    case 'a':
        x -= size;
        break;
    }
}

void drawApple(int x, int y, int size) {
    setfillstyle(SOLID_FILL, RED);
    bar(x, y, x + size, y + size); // Рисует яблоко
}

void generateRandomAppleCoordinates(int size, int& appleX, int& appleY) {
    appleX = rand() % (windowWidth - size); 
    appleY = rand() % (windowHeight - size);
}

bool isAppleEaten(int appleX, int appleY, int appleSize, int x, int y, int squareSize) {
    int capybaraCenterX = x + squareSize / 2;
    int capybaraCenterY = y + squareSize / 2;

    int appleCenterX = appleX + appleSize / 2;
    int appleCenterY = appleY + appleSize / 2;

    int distanceX = abs(capybaraCenterX - appleCenterX);
    int distanceY = abs(capybaraCenterY - appleCenterY);

    if (distanceX < (squareSize + appleSize) / 2 && distanceY < (squareSize + appleSize) / 2) {
        return true;
    }

    return false;
}

int main() {
    setlocale(LC_ALL, "ru");
    initwindow(500, 500); 
    windowWidth = getmaxx();
    windowHeight = getmaxy();
    std::cout << "Window size: x=" << windowWidth << " y=" << windowHeight << std::endl;

    srand(time(0));

    int x = 0;
    int y = 0;
    int squareSize = 40;

    int appleX, appleY;
    int appleSize = 20;

    int eatenApples = 0;

    generateRandomAppleCoordinates(appleSize, appleX, appleY);

    while (true) {
        cleardevice();
        drawSquare(x, y, squareSize);
        drawApple(appleX, appleY, appleSize);

        if (kbhit()) { // Проверяет, была ли нажата клавиша на клавиатуре
            char key = getch();
            moveSquare(key, x, y, squareSize);

            if (isAppleEaten(appleX, appleY, appleSize, x, y, squareSize)) {
                generateRandomAppleCoordinates(appleSize, appleX, appleY);
                eatenApples++;
                std::cout << "Количество сьеденных яблок: " << eatenApples << std::endl;
            }
        }

        delay(10);
    }

    getch();
    closegraph();
    return 0;
}
