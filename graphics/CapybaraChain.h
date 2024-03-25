#ifndef CAPYBARACHAIN_H
#define CAPYBARACHAIN_H
#include <iostream>
#include "graphics.h"
#include <vector>

#pragma comment(lib,"graphics.lib")

#include <vector>


struct Capybara {
    int x;
    int y;
};

// ����� ��� ���������� �������� �������
class CapybaraChain {
private:
    int currentDirection = 0;
public:
    std::vector<Capybara> capybaras;

    // ����������� ������ CapybaraChain
    CapybaraChain(int startX, int startY) {
        addCapybara(startX, startY);
    }

    // ����� ��� ���������� �������� � �������
    void addCapybara(int startX, int startY) {
        Capybara newCapybara;
        newCapybara.x = startX;
        newCapybara.y = startY;
        capybaras.push_back(newCapybara);
    }

    // ����� ��� ��������� ��������
    void drawCapybara(int size) const {
        for (const Capybara& capybara : capybaras) {
            rectangle(capybara.x, capybara.y, capybara.x + size, capybara.y + size);
        }
    }

    // ����� ��� ����������� ��������
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

    // ����� ��� ����� ����������� �������� ��������
    void changeDirection(char newDirection) {
        if ((currentDirection == 'd' && newDirection == 'a') ||
            (currentDirection == 'a' && newDirection == 'd') ||
            (currentDirection == 'w' && newDirection == 's') ||
            (currentDirection == 's' && newDirection == 'w')) {
            return;
        }

        currentDirection = newDirection;
    }

    // ����� ��� �������� ������������ �������� � ������ ���������
    bool checkCollisionWithOtherCapybara() const {
        Capybara headCapybara = capybaras.front();
        for (size_t i = 1; i < capybaras.size(); ++i) {
            if (headCapybara.x == capybaras[i].x && headCapybara.y == capybaras[i].y) {
                return true;
            }
        }
        return false;
    }

    // ����� ��� ��������, ����� �� �������� ������
    bool isAppleEaten(int appleX, int appleY, int appleSize, int squareSize) const {
        int capybaraCenterX = capybaras.front().x + squareSize / 2;
        int capybaraCenterY = capybaras.front().y + squareSize / 2;

        int appleCenterX = appleX + appleSize / 2;
        int appleCenterY = appleY + appleSize / 2;

        int distanceX = abs(capybaraCenterX - appleCenterX);
        int distanceY = abs(capybaraCenterY - appleCenterY);

        return (distanceX < (squareSize + appleSize) / 2 && distanceY < (squareSize + appleSize) / 2);
    }
    // ����� ��� ��������� ������ ������� � �������
    const std::vector<Capybara>& getCapybaras() const {
        return capybaras;
    }
};
#endif
