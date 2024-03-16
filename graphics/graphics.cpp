#include "graphics.h"
#pragma comment(lib,"graphics.lib")
int main()
{
    initwindow(500, 500);
    line(100, 100, 300, 300);

    getch();
    closegraph();
    return 0;
}