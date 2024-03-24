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
struct Capybara {
    int x;
    int y;
};

// Класс для управления цепочкой капибар
class CapybaraChain {
private:
public:
    std::vector<Capybara> capybaras;

    // Конструктор класса CapybaraChain
    CapybaraChain(int startX, int startY) {
        addCapybara(startX, startY);
    }

    // Метод для добавления капибары в цепочку
    void addCapybara(int startX, int startY) {
        Capybara newCapybara;
        newCapybara.x = startX;
        newCapybara.y = startY;
        capybaras.push_back(newCapybara);
    }

    // Метод для отрисовки капибары
    void drawCapybara(int size) const {
        for (const Capybara& capybara : capybaras) {
            rectangle(capybara.x, capybara.y, capybara.x + size, capybara.y + size);
        }
    }

    // Метод для перемещения капибары
    void move(char currentDirection, int size) {
        if (!capybaras.empty()) {
            for (int i = capybaras.size() - 1; i > 0; --i) {
                capybaras[i].x = capybaras[i - 1].x;
                capybaras[i].y = capybaras[i - 1].y;
            }

            Capybara& headCapybara = capybaras.front();
            switch (currentDirection) {
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

    // Метод для смены направления движения капибары
    void changeDirection(char newDirection) {
        if ((currentDirection == 'd' && newDirection == 'a') ||
            (currentDirection == 'a' && newDirection == 'd') ||
            (currentDirection == 'w' && newDirection == 's') ||
            (currentDirection == 's' && newDirection == 'w')) {
            return;
        }

        currentDirection = newDirection;
    }

    // Метод для проверки столкновения капибары с другой капибарой
    bool checkCollisionWithOtherCapybara() const {
        Capybara headCapybara = capybaras.front();
        for (size_t i = 1; i < capybaras.size(); ++i) {
            if (headCapybara.x == capybaras[i].x && headCapybara.y == capybaras[i].y) {
                return true;
            }
        }
        return false;
    }

    // Метод для проверки, съела ли капибара яблоко
    bool isAppleEaten(int appleX, int appleY, int appleSize, int squareSize) const {
        int capybaraCenterX = capybaras.front().x + squareSize / 2;
        int capybaraCenterY = capybaras.front().y + squareSize / 2;

        int appleCenterX = appleX + appleSize / 2;
        int appleCenterY = appleY + appleSize / 2;

        int distanceX = abs(capybaraCenterX - appleCenterX);
        int distanceY = abs(capybaraCenterY - appleCenterY);

        return (distanceX < (squareSize + appleSize) / 2 && distanceY < (squareSize + appleSize) / 2);
    }
    // Метод для получения списка капибар в цепочке
    const std::vector<Capybara>& getCapybaras() const {
        return capybaras;
    }
};

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