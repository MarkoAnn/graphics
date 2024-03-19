#include <iostream>
#include "graphics.h"
#pragma comment(lib,"graphics.lib")

const int WINDOW_WIDTH = 500;
const int WINDOW_HEIGHT = 500;
const int SQUARE_SIZE = 20;
const int APPLE_SIZE = 10;
const int GAME_DURATION_SECONDS = 60;

// Перечисление для режимов игры
enum GameMode {
    ENDLESS_MODE, // Бесконечный режим
    TIMED_MODE, // Режим с ограниченным временем
};

// Функция для инициализации игры и ввода режима игры
GameMode initializeGame() {
    initwindow(WINDOW_WIDTH, WINDOW_HEIGHT); // Инициализация графического окна
    std::cout << "Window size: x=" << WINDOW_WIDTH << " y=" << WINDOW_HEIGHT << std::endl; // Вывод размера окна в консоль

    srand(time(0)); // Инициализация генератора случайных чисел

    int selectedMode;
    std::cout << "Выберите режим игры (1 - Бесконечный, 2 - Ограниченное время): ";
    std::cin >> selectedMode; // Считывание выбранного режима игры

    return (selectedMode == 2) ? TIMED_MODE : ENDLESS_MODE; // Возвращаем выбранный режим игры
}

void drawSquare(int x, int y, int size) {
    rectangle(x, y, x + size, y + size); // Рисуем квадрат
}

void moveSquare(char key, int& x, int& y, int size) {
    switch (key) { // Перемещаем квадрат в зависимости от нажатой клавиши
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
    bar(x, y, x + size, y + size); // Рисуем яблоко
}

void generateRandomAppleCoordinates(int size, int& appleX, int& appleY) {
    appleX = rand() % (WINDOW_WIDTH - size);
    appleY = rand() % (WINDOW_HEIGHT - size); // Генерируем случайные координаты для яблока
}

bool isAppleEaten(int appleX, int appleY, int appleSize, int x, int y, int squareSize) {
    int capybaraCenterX = x + squareSize / 2;
    int capybaraCenterY = y + squareSize / 2;

    int appleCenterX = appleX + appleSize / 2;
    int appleCenterY = appleY + appleSize / 2;

    int distanceX = abs(capybaraCenterX - appleCenterX);
    int distanceY = abs(capybaraCenterY - appleCenterY);

    return (distanceX < (squareSize + appleSize) / 2 && distanceY < (squareSize + appleSize) / 2); // Проверяем, съедено ли яблоко
}

void displayTime(int remainingTime) {
    char timeText[50];
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2); // Устанавливаем стиль текста
    setcolor(WHITE); // Устанавливаем цвет текста
    sprintf_s(timeText, sizeof(timeText), "Оставшееся время: %d секунд", remainingTime); // Форматируем строку времени
    outtextxy(10, 10, timeText); // Выводим текст на экран
}

int main() {
    setlocale(LC_ALL, "ru");
    GameMode mode = initializeGame(); // Инициализация игры и ввод режима игры

    int x = 0;
    int y = 0;
    int appleX = 0;
    int appleY = 0;
    int eatenApples = 0;
    int endTime = time(0) + GAME_DURATION_SECONDS; // Вычисление времени завершения игры

    while (true) {
        cleardevice(); // Очистка экрана
        drawSquare(x, y, SQUARE_SIZE); // Рисуем квадрат
        drawApple(appleX, appleY, APPLE_SIZE); // Рисуем яблоко

        if (mode == TIMED_MODE && time(0) >= endTime) { // Если режим игры - ограниченное время и время истекло
            std::cout << "Игра окончена! Количество съеденных яблок: " << eatenApples << std::endl; // Выводим сообщение о завершении игры
            break; // Завершаем игровой цикл
        }

        if (kbhit()) { // Если произошло нажатие клавиши
            char key = getch(); // Считываем нажатую клавишу
            moveSquare(key, x, y, SQUARE_SIZE); // Перемещаем квадрат в соответствии с нажатой клавишей

            if (isAppleEaten(appleX, appleY, APPLE_SIZE, x, y, SQUARE_SIZE)) { // Если съедено яблоко
                generateRandomAppleCoordinates(APPLE_SIZE, appleX, appleY); // Генерируем новые координаты для яблока
                eatenApples++; // Увеличиваем счетчик съеденных яблок
                std::cout << "Количество съеденных яблок: " << eatenApples << std::endl; // Выводим количество съеденных яблок в консоль
            }

            while (kbhit()) // Ждем отпускания клавиши
                getch();
        }

        if (mode == TIMED_MODE) { // Если режим игры - ограниченное время
            int remainingTime = (endTime - time(0) > 0) ? (endTime - time(0)) : 0; // Вычисляем оставшееся время игры
            displayTime(remainingTime); // Отображаем оставшееся время на экране
        }

        delay(100); // Задержка перед обновлением экрана
    }

    getch(); // Ожидаем нажатия клавиши перед закрытием окна
    closegraph(); // Закрываем графическое окно
    return 0; // Возвращаем значение 0, указывающее на успешное завершение программы
}