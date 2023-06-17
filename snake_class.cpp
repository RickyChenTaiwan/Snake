#include <Windows.h>
#include <iostream>
#include <conio.h> // console io (input/output)
#include "snake_class.h"
#include "global.h"
using namespace std;
// "define" is a macro definition command. "#" represent preprocess command => #define 'identification symbol' 'string'
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

//call class Snake's Constructor Snake (think as initialization)
//Note: the Constructor name Snake should be the same as class name (Snake)
Snake::Snake(int w, int h) {
	width = w;
	height = h;
	foodType = getFoodType();
	prevFoodType = foodType;
	over = false;
	snakeLocation.x = width / 2;
	snakeLocation.y = height / 2;
	foodLocation.x = rand() % width;
	foodLocation.y = rand() % height;
	score = 0;
	nTail = 0;
	dir = snakeDirection::STOP;
	//calculate the legth of tail when snake eat food each time
	count = 1;

	//set location struct into tail variable as first vector element
	locationStruct newTail = { -1, -1 };
	tail.push_back(newTail);
	//fill_n(tail, 100, newTail); // using array container as tail
}

bool Snake::getOverResult() {
	return over;
}

void Snake::layout() {
	//reduce flicker phenomenon
	COORD coord;
	coord.X = 0;
	coord.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

	//system("cls"); 
	//upper horizontal line
	for (int u = 0; u < width + 2; u++) {
		cout << "#";
	}
	cout << endl;

	//two side walls
	for (int i = 0; i < height; i++) 
	{
		for (int j = 0; j < width + 2; j++)
		{
			if (j == 0) {
				cout << "#";
			}

			if (i == snakeLocation.y and j == snakeLocation.x){
				cout << "0"; //snake head
			}
			else if (i == foodLocation.y and j == foodLocation.x) {
				switch (foodType) {
					case 1:
						cout << "F";
						break;
					case 2:
						cout << "Q";
						break;
					case 3:
						cout << "*";
						break;
					default:
						cout << "F";
				}
			}
			else
			{
				//draw snake's tail
				bool drawTail = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tail[k].x == j and tail[k].y == i)
					{
						// 1-F => o,  2 - Q => @, 3 - * => +
						switch (prevFoodType) {
						case 1:
							cout << "o";
							break;
						case 2:
							cout << "@";
							break;
						case 3:
							cout << "+";
							break;
						default:
							cout << "o";
						}
						drawTail = true;
					}
				}
				if (!drawTail)
					cout << " ";
			}
			if (j == width -1){
				cout << "#";
			}
		}
		cout << endl; // endl, "\n"
	}

	////bottom horizontal line
	for (int b = 0; b < width + 2; b++) {
		cout << "#";
	}
	cout << endl;
	cout << "Score: " << score << endl;
}

void Snake::input() 
{
	if (_kbhit()) // if keyboard is pressed or not
	{
		switch (_getch())  //get character from keyboard
		{                  // w: up, a: left, s: down, d: right
		//case 'a':
		case KEY_LEFT:
			dir = snakeDirection::LEFT;
			break;
			//case 'd':
		case KEY_RIGHT:
			dir = snakeDirection::RIGHT;
			break;
		case KEY_UP:
			dir = snakeDirection::UP;
			break;
		case KEY_DOWN:
			dir = snakeDirection::DOWN;
			break;
		case 'q':
			over = true;
			break;
		}
	}
}

void Snake::logic()
{
	//see more detail in this part
	auto prevX = tail[0].x;   //output 0 in first round, data type is int
	auto prevY = tail[0].y;   //output 0 in first round, data type is int
	int prev2X, prev2Y;
	tail[0].x = snakeLocation.x;  // output the location of snake head in first round
	tail[0].y = snakeLocation.y;  // output the location of snake head in first round

	//nTail is 0 in first round
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tail[i].x;
		prev2Y = tail[i].y;
		tail[i].x = prevX;
		tail[i].y = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (dir)
	{
	case snakeDirection::LEFT:
		snakeLocation.x--;
		break;
	case snakeDirection::RIGHT:
		snakeLocation.x++;
		break;
	case snakeDirection::UP:
		snakeLocation.y--;
		break;
	case snakeDirection::DOWN:
		snakeLocation.y++;
		break;
	}
	// game over if snake hit the wall
	/*if (snakeLocation.x > width || snakeLocation.x < 0 || snakeLocation.y > height || snakeLocation.y < 0)
		over = true;*/

	// game not over if snake hit wall
	if (snakeLocation.x >= width) snakeLocation.x = 0; else if (snakeLocation.x < 0) snakeLocation.x = width - 1;
	if (snakeLocation.y >= height) snakeLocation.y = 0; else if (snakeLocation.y < 0) snakeLocation.y = height - 1;

	// game over if snake hit self-tail
	for (int i = 0; i < nTail; i++) {
		if (tail[i].x == snakeLocation.x and tail[i].y == snakeLocation.y)
			over = true;
	}

	// when snake head hit food
	if (snakeLocation.x == foodLocation.x and snakeLocation.y == foodLocation.y)
	{
		switch (foodType) {
		case 1:
			//increase score
			score += 10;
			//increase the tail number of tail
			nTail += 1;
			count = 1;
			break;
		case 2:
			//increase score
			score += 20;
			//increase the tail number of tail
			nTail += 2;
			count = 2;
			break;
		case 3:
			//increase score
			score += 30;
			//increase the tail number of tail
			nTail += 3;
			count = 3;
			break;
		default:
			score += 10;
			nTail += 1;
			count = 1;
		}
		//score += 10;
		//nTail++;
		
		//add length of snake tail dynamically
		for (int i = 0; i < count; i++) {
			locationStruct newTail = { -1, -1 };
			tail.push_back(newTail);
		}

		//generate another fruit location
		foodLocation.x = rand() % width;
		foodLocation.y = rand() % height;

		//record previous food type
		prevFoodType = foodType;

		//random fppd type
		foodType = getFoodType();
	}
}