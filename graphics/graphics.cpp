#include <iostream>
#include "graphics.h"
#include <vector>

#pragma comment(lib,"graphics.lib")

const int WINDOW_WIDTH = 500;
const int WINDOW_HEIGHT = 500;
const int SQUARE_SIZE = 20;
const int APPLE_SIZE = 10;
const int GAME_DURATION_SECONDS = 60;
int currentDirection = 0;
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

struct Capybara {
    int x;
    int y;
};

std::vector<Capybara> capybaras; // Вектор для хранения капибар

// Функция для добавления капибары в вектор
void addCapybara(int startX, int startY) {
    Capybara newCapybara;
    newCapybara.x = startX;
    newCapybara.y = startY;
    capybaras.push_back(newCapybara);
}

// Функция для рисования капибары
void drawCapybara(int size) {
    for (const Capybara& capybara : capybaras) { // Перебираем все капибары в векторе
        rectangle(capybara.x, capybara.y, capybara.x + size, capybara.y + size); // Рисуем капибару
    }
}


// Функция для перемещения капибары
void moveCapybara(int size, char currentDirection) {
    if (!capybaras.empty()) {
        for (int i = capybaras.size() - 1; i > 0; --i) { // Обходим капибар с конца, итерируемся от последнего до второго
            capybaras[i].x = capybaras[i - 1].x;
            capybaras[i].y = capybaras[i - 1].y; // Каждой капибаре ставим координаты предыдущей
        }

        Capybara& headCapybara = capybaras.front(); // Получаем ссылку на главную капибару
        switch (currentDirection) { // Перемещаем капибару в зависимости от текущего направления
        case 'd':
            headCapybara.x += size;
            break;
        case 's':
            headCapybara.y += size;
            break;
        case 'w':
            headCapybara.y -= size;
            break;
        case 'a':
            headCapybara.x -= size;
            break;
        }
    }
}
void changeDirection(int newDirection) {
    // Нельзя развернуться на 180 градусов - приведет к незамедлительному поражению
    if ((currentDirection == 0 && newDirection == 1) ||
        (currentDirection == 1 && newDirection == 0) ||
        (currentDirection == 2 && newDirection == 3) ||
        (currentDirection == 3 && newDirection == 2)) {
        return;
    }

    currentDirection = newDirection;
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

    addCapybara(0, 0); // Добавляем капибару в вектор с начальными координатами

    int appleX = 0;
    int appleY = 0;
    int eatenApples = 0;
    int endTime = time(0) + GAME_DURATION_SECONDS; // Вычисление времени завершения игры
    char currentDirection = 'd'; // По умолчанию капибара начинает движение вправо

    while (true) {
        cleardevice(); // Очистка экрана
        drawCapybara(SQUARE_SIZE); // Рисуем капибару
        drawApple(appleX, appleY, APPLE_SIZE); // Рисуем яблоко

        if (mode == TIMED_MODE && time(0) >= endTime) { // Если режим игры - ограниченное время и время истекло
            std::cout << "Игра окончена! Количество съеденных яблок: " << eatenApples << std::endl; // Выводим сообщение о завершении игры
            break; // Завершаем игровой цикл
        }

        moveCapybara(SQUARE_SIZE, currentDirection); // Перемещаем капибару
        drawCapybara(SQUARE_SIZE); // Перерисовываем капибару после перемещения

        Capybara& headCapybara = capybaras.front(); // Получаем ссылку на главную капибару

        if (headCapybara.x < 0 || headCapybara.x + SQUARE_SIZE > WINDOW_WIDTH ||
            headCapybara.y < 0 || headCapybara.y + SQUARE_SIZE > WINDOW_HEIGHT) {
            std::cout << "Игра окончена! Капибара врезалась в стену." << std::endl;
            break;
        }

        bool gameOver = false;
        for (size_t i = 1; i < capybaras.size(); ++i) {
            if (headCapybara.x == capybaras[i].x && headCapybara.y == capybaras[i].y) {
                std::cout << "Игра окончена! Капибара врезалась в другую капибару." << std::endl;
                gameOver = true;
                break;
            }
        }

        if (gameOver) {
            break;
        }

        if (isAppleEaten(appleX, appleY, APPLE_SIZE, capybaras.front().x, capybaras.front().y, SQUARE_SIZE)) { // Если съедено яблоко
            generateRandomAppleCoordinates(APPLE_SIZE, appleX, appleY); // Генерируем новые координаты для яблока
            eatenApples++; // Увеличиваем счетчик съеденных яблок
            std::cout << "Количество съеденных яблок: " << eatenApples << std::endl; // Выводим количество съеденных яблок в консоль
            addCapybara(capybaras.back().x, capybaras.back().y); // Добавляем новый элемент в вектор capybaras
        }

        if (kbhit()) { // Если произошло нажатие клавиши
            char key = getch(); // Считываем нажатую клавишу
            switch (key) {
            case 'd':
            case 's':
            case 'w':
            case 'a':
                currentDirection = key; // Обновляем текущее направление движения
                break;
            }
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