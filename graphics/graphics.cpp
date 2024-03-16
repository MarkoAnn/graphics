#include "graphics.h"
#pragma comment(lib,"graphics.lib")

int main() {
    initwindow(500, 500);

    // Рисуем линию
    line(100, 100, 300, 300);
    // Ждем две секунды
    delay(2000);
    // Очищаем экран и устанавливаем фон черным
    cleardevice();
    setbkcolor(BLACK);

    getch();
    closegraph();
    return 0;
}