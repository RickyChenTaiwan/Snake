#pragma once
#include <vector>
#include "global.h"
using namespace std;

//Snkae class's header file, declare Snake class only
class Snake {
public:
	Snake(int w = 20, int h = 20); // Constructor
	//declare public member function
	void layout();
	void input();
	void logic();
	bool getOverResult();

private:
	//declare the private member function/variable
	//int getFoodType();
	bool over;
	int width;
	int height;
	int score;
	int nTail;
	int foodType;
	int prevFoodType;
	int count;

	struct snakeLocationStruct:locationStruct {
	}snakeLocation;  //structure variable

	struct foodLocationStruct :locationStruct {
	}foodLocation;  //structure variable

	vector<locationStruct> tail; // define the tail vector with locationStruct data type
	//locationStruct tail[100];  // define the tail array with locationStruct data type

	enum class snakeDirection {STOP = 0, LEFT = 1, RIGHT = 2, UP = 3, DOWN = 4};
	// enum snakeDirection {STOP, LEFT, RIGHT, UP, DOWN};
	snakeDirection dir;
};