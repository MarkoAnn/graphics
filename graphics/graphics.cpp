#include <iostream>
#include "CapybaraChain.h"

#include "graphics.h"

#include <vector>

#pragma comment(lib,"graphics.lib")
const int WINDOW_WIDTH = 500;
const int WINDOW_HEIGHT = 500;
const int SQUARE_SIZE = 20;
const int APPLE_SIZE = 10;
const int GAME_DURATION_SECONDS = 60;


enum GameMode {
    ENDLESS_MODE, // Бесконечный режим
    TIMED_MODE, // Режим с ограниченным временем
};

// Инициализация игры и ввод режима игры
GameMode initializeGame() {
    initwindow(WINDOW_WIDTH, WINDOW_HEIGHT); // Инициализация графического окна
    std::cout << "Window size: x=" << WINDOW_WIDTH << " y=" << WINDOW_HEIGHT << std::endl; // Вывод размера окна в консоль

    srand(time(0)); // Инициализация генератора случайных чисел

    int selectedMode;
    std::cout << "Выберите режим игры (1 - Бесконечный, 2 - Ограниченное время): ";
    std::cin >> selectedMode; // Считывание выбранного режима игры

    return (selectedMode == 2) ? TIMED_MODE : ENDLESS_MODE; // Возвращаем выбранный режим игры
}

// Структура для представления капибары


// Функция для рисования яблока
void drawApple(int x, int y, int size) {
    setfillstyle(SOLID_FILL, RED);
    bar(x, y, x + size, y + size);
}

// Функция для генерации случайных координат для яблока
void generateRandomAppleCoordinates(int size, int& appleX, int& appleY) {
    appleX = rand() % (WINDOW_WIDTH - size);
    appleY = rand() % (WINDOW_HEIGHT - size);
}

// Функция для увеличения счетчика съеденных яблок
void increaseEatenApplesCounter(int& eatenApples) {
    eatenApples++;
    std::cout << "Количество съеденных яблок: " << eatenApples << std::endl;
}

// Функция для отображения оставшегося времени игры
void displayTime(int remainingTime) {
    char timeText[50];
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    setcolor(WHITE);
    sprintf_s(timeText, sizeof(timeText), "Оставшееся время: %d секунд", remainingTime);
    outtextxy(10, 10, timeText);
}

int main() {
    setlocale(LC_ALL, "ru");

    // Инициализация игры и выбор режима
    GameMode mode = initializeGame();

    // Создание объекта CapybaraChain с начальными координатами (0, 0)
    CapybaraChain capybaraChain(0, 0);

    // Инициализация координат яблока и счётчика съеденных яблок
    int appleX = 0;
    int appleY = 0;
    int eatenApples = 0;

    // Вычисление времени завершения игры
    int endTime = time(0) + GAME_DURATION_SECONDS;

    // Направление движения капибары (по умолчанию - вправо)
    char currentDirection = 'd';

    // Главный игровой цикл
    while (true) {
        // Обработка нажатий клавиш для изменения направления капибары
        if (kbhit()) {
            char key = getch();
            switch (key) {
            case 'd':
            case 's':
            case 'w':
            case 'a':
                currentDirection = key;
                capybaraChain.changeDirection(key);
                break;
            }
        }

        // Очистка экрана
        cleardevice();

        // Перемещение и отрисовка капибары
        capybaraChain.move(currentDirection, SQUARE_SIZE);
        capybaraChain.drawCapybara(SQUARE_SIZE);

        // Отрисовка яблока
        drawApple(appleX, appleY, APPLE_SIZE);

        // Проверка столкновения капибары с границами экрана
        const Capybara& headCapybara = capybaraChain.getCapybaras().front();
        if (headCapybara.x < 0 || headCapybara.x + SQUARE_SIZE > WINDOW_WIDTH ||
            headCapybara.y < 0 || headCapybara.y + SQUARE_SIZE > WINDOW_HEIGHT) {
            std::cout << "Игра окончена! Капибара врезалась в стену." << std::endl;
            break;
        }

        // Проверка столкновения капибары с другой капибарой
        if (capybaraChain.checkCollisionWithOtherCapybara()) {
            std::cout << "Игра окончена! Капибара врезалась в другую капибару." << std::endl;
            break;
        }

        // Проверка, съела ли капибара яблоко
        if (capybaraChain.isAppleEaten(appleX, appleY, APPLE_SIZE, SQUARE_SIZE)) {
            generateRandomAppleCoordinates(APPLE_SIZE, appleX, appleY);
            increaseEatenApplesCounter(eatenApples);
            capybaraChain.addCapybara(capybaraChain.getCapybaras().back().x, capybaraChain.getCapybaras().back().y);
        }

        
        if (time(0) >= endTime) {
            std::cout << "Игра окончена! Количество съеденных яблок: " << eatenApples << std::endl;
            break;
        }

        
        if (mode == TIMED_MODE) {
            int remainingTime = (endTime - time(0) > 0) ? (endTime - time(0)) : 0;
            displayTime(remainingTime);
        }

        // Задержка перед обновлением экрана
        delay(100);
    }

    // Ожидание нажатия клавиши перед закрытием окна
    getch();
    // Закрытие графического окна
    closegraph();

    return 0;
}