#include <iostream>
#include <Windows.h>
#include "snake_class.h" // import header file

int main()
{
    int width = 20;
    int height = 20;
    //foodType 1 => F, 2 => Q, 3 => *
    Snake snakeObj(width, height); // (think as initialization)
    //Snake snakeObj;
    while (!snakeObj.getOverResult()) {
        snakeObj.layout();
        snakeObj.input();
        snakeObj.logic();
        Sleep(100);
    }
    return 0;
}