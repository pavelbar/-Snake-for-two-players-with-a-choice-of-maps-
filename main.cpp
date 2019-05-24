#include "stdafx.h"
#include "Graph.h"
#include "Snake.h"
#include <conio.h>//_kbhit
#include "windows.h"//sleep
#include "iostream"


using namespace std;

enum ConsoleColor { Black = 0, Blue, Green, Cyan, Red, Magenta, Brown, LightGray, DarkGray, LightBlue, LightGreen, LightCyan, LightRed, LightMagenta, Yellow, White };

//===COLOR SETTINGS ZONE===
ConsoleColor BORDER = LightGray; //Graph
ConsoleColor BACKGROUND = Black; //Graph
ConsoleColor FOREGROUND = White; //Graph

ConsoleColor SPEED = White;    //main
ConsoleColor SCORE = White;    //main
ConsoleColor VAL_SPEED = Cyan; //main
ConsoleColor VAL_SCORE = Cyan; //main

ConsoleColor SNAKEONE_BODY_FOREGROUND = DarkGray; //Snake1
ConsoleColor SNAKEONE_BODY_BACKGROUND = DarkGray; //Snake1
ConsoleColor SNAKEONE_HEAD_FOREGROUND = LightRed; //Snake1
ConsoleColor SNAKEONE_HEAD_BACKGROUND = LightRed; //Snake1

ConsoleColor SNAKETWO_BODY_FOREGROUND = LightMagenta; //Snake2
ConsoleColor SNAKETWO_BODY_BACKGROUND = LightMagenta; //Snake2
ConsoleColor SNAKETWO_HEAD_FOREGROUND = Yellow; //Snake2
ConsoleColor SNAKETWO_HEAD_BACKGROUND = Yellow; //Snake2
//===END COLOR SETTINGS ZONE===


void Clear_snake(size_t *X, size_t *Y, size_t len, Graph &gameBoard)
{
	for (size_t i = 0; i < len; i++)
		gameBoard.Symbol_to_point(X[i], Y[i], '\0', FOREGROUND, BACKGROUND);
}

void Print_snake(size_t *X, size_t *Y, size_t len, int delta_x, int delta_y, Graph &gameBoard, Snake &snake)
{

	if ((delta_x == 0) && (delta_y == 0)) 	gameBoard.Symbol_to_point(X[0], Y[0], char(142), snake.get_SNAKE_HEAD_FOREGROUND(), BACKGROUND);
	if ((delta_x == -1) && (delta_y == 0)) 	gameBoard.Symbol_to_point(X[0], Y[0], '<', snake.get_SNAKE_HEAD_FOREGROUND(), BACKGROUND);
	if ((delta_x == 1) && (delta_y == 0)) 	gameBoard.Symbol_to_point(X[0], Y[0], '>', snake.get_SNAKE_HEAD_FOREGROUND(), BACKGROUND);
	if ((delta_x == 0) && (delta_y == 1)) 	gameBoard.Symbol_to_point(X[0], Y[0], char(194), snake.get_SNAKE_HEAD_FOREGROUND(), BACKGROUND);
	if ((delta_x == 0) && (delta_y == -1)) 	gameBoard.Symbol_to_point(X[0], Y[0], '^', snake.get_SNAKE_HEAD_FOREGROUND(), BACKGROUND);

	for (size_t i = 1; i < len; i++)
		gameBoard.Symbol_to_point(X[i], Y[i], char(142), snake.get_SNAKE_BODY_FOREGROUND(), BACKGROUND); //* SNAKE_BODY_BACKGROUND
}
void info(Graph &gameBoard, Snake &snakeOne, Snake &snakeTwo, size_t MAX_X, size_t MAX_Y, string mode) {
	gameBoard.String_to_point(1, MAX_Y, "Snake 1:", snakeOne.get_SNAKE_HEAD_FOREGROUND(), BACKGROUND);
	gameBoard.String_to_point(13, MAX_Y, "Score: ", SCORE, BACKGROUND);
	gameBoard.String_to_point(21, MAX_Y, to_string(snakeOne.getLengthOfSnake()), VAL_SCORE, BACKGROUND);
	gameBoard.String_to_point(25, MAX_Y, " | Speed: ", SPEED, BACKGROUND);
	gameBoard.String_to_point(35, MAX_Y, to_string(snakeOne.getSpeedOfSnake()), VAL_SPEED, BACKGROUND);
	if (mode == "2") {
		gameBoard.String_to_point(1, MAX_Y + 1, "Snake 2:", snakeTwo.get_SNAKE_HEAD_FOREGROUND(), BACKGROUND);
		gameBoard.String_to_point(13, MAX_Y + 1, "Score: ", SCORE, BACKGROUND);
		gameBoard.String_to_point(21, MAX_Y + 1, to_string(snakeTwo.getLengthOfSnake()), VAL_SCORE, BACKGROUND);
		gameBoard.String_to_point(25, MAX_Y + 1, " | Speed: ", SPEED, BACKGROUND);
		gameBoard.String_to_point(35, MAX_Y + 1, to_string(snakeTwo.getSpeedOfSnake()), VAL_SPEED, BACKGROUND);
	}
}

int main()
{

	const size_t MAX_Y = 21 + 2;//стр
	const size_t MAX_X = 77 + 2;//столб
	string mode = " ";

	while (true) {
		cout << endl << "-> Select mode:";
		cout << endl << "1. One player";
		cout << endl << "2. Two players";
		cout << endl << endl << "-> Input: ";
		cin >> mode;
		if ((mode == "1") || (mode == "2")) {
			break;
		}
		else {
			cout << endl << "-> !!!Incorrect input";
		}
	}
	system("cls");

	Graph gameBoard(MAX_X, MAX_Y, BACKGROUND, BORDER);

	Snake snakeOne(MAX_X, MAX_Y);
	snakeOne.set_SNAKE_BODY_BACKGROUND(SNAKEONE_BODY_FOREGROUND);
	snakeOne.set_SNAKE_BODY_FOREGROUND(SNAKEONE_BODY_BACKGROUND);
	snakeOne.set_SNAKE_HEAD_BACKGROUND(SNAKEONE_HEAD_FOREGROUND);
	snakeOne.set_SNAKE_HEAD_FOREGROUND(SNAKEONE_HEAD_BACKGROUND);

	Snake snakeTwo(MAX_X, MAX_Y);
	snakeTwo.set_SNAKE_BODY_BACKGROUND(SNAKETWO_BODY_FOREGROUND);
	snakeTwo.set_SNAKE_BODY_FOREGROUND(SNAKETWO_BODY_BACKGROUND);
	snakeTwo.set_SNAKE_HEAD_BACKGROUND(SNAKETWO_HEAD_FOREGROUND);
	snakeTwo.set_SNAKE_HEAD_FOREGROUND(SNAKETWO_HEAD_BACKGROUND);

	info(gameBoard, snakeOne, snakeTwo, MAX_X, MAX_Y, mode);
	while (true)
	{
		if (snakeOne.getNeedFood() == true)
		{
			gameBoard.Symbol_to_point(snakeOne.getFoodX(), snakeOne.getFoodY(), '\0', FOREGROUND, BACKGROUND);
			snakeOne.Generation_of_food_coordinates();

			gameBoard.Symbol_to_point(snakeOne.getFoodX(), snakeOne.getFoodY(), char(142), snakeOne.get_SNAKE_HEAD_FOREGROUND(), BACKGROUND);
			snakeOne.setNeedFood(false);
		}
		if (mode == "2") {
			if (snakeTwo.getNeedFood() == true)
			{
				gameBoard.Symbol_to_point(snakeTwo.getFoodX(), snakeTwo.getFoodY(), '\0', FOREGROUND, BACKGROUND);
				snakeTwo.Generation_of_food_coordinates();

				gameBoard.Symbol_to_point(snakeTwo.getFoodX(), snakeTwo.getFoodY(), char(142), snakeTwo.get_SNAKE_HEAD_FOREGROUND(), BACKGROUND);
				snakeTwo.setNeedFood(false);
			}
		}

		Clear_snake(snakeOne.getX_coordinate_of_snake(), snakeOne.getY_coordinate_of_snake(), snakeOne.getLengthOfSnake(), gameBoard);
		if (mode == "2") {
			Clear_snake(snakeTwo.getX_coordinate_of_snake(), snakeTwo.getY_coordinate_of_snake(), snakeTwo.getLengthOfSnake(), gameBoard);
		}


		if (_kbhit() != 0) {
			int code = _getch();

			if (code == 72)//up
			{
				snakeOne.Coordinate_transformation_by_button("up");
			}

			if (code == 87 || code == 119)//w
			{
				if (mode == "2") {
					snakeTwo.Coordinate_transformation_by_button("up");
				}
			}

			if (code == 80)//down
			{
				snakeOne.Coordinate_transformation_by_button("down");
			}

			if (code == 83 || code == 115)//s
			{
				if (mode == "2") {
					snakeTwo.Coordinate_transformation_by_button("down");
				}
			}

			if (code == 75)//left
			{
				snakeOne.Coordinate_transformation_by_button("left");
			}

			if (code == 65 || code == 97)//a
			{
				if (mode == "2") {
					snakeTwo.Coordinate_transformation_by_button("left");
				}
			}

			if (code == 77)//right
			{
				snakeOne.Coordinate_transformation_by_button("right");
			}

			if (code == 68 || code == 100)//d
			{
				if (mode == "2") {
					snakeTwo.Coordinate_transformation_by_button("right");
				}
			}

			if (code == 27)//ESC
				snakeOne.Coordinate_transformation_by_button("esc");

		}
		else {
			//если кнопка не нажата
			snakeOne.Coordinate_transformation_automatically();
			if (mode == "2") {
				snakeTwo.Coordinate_transformation_automatically();
			}
		}
		snakeOne.Correction_of_oordinates();
		if (mode == "2") {
			snakeTwo.Correction_of_oordinates();
		}

		Print_snake(snakeOne.getX_coordinate_of_snake(), snakeOne.getY_coordinate_of_snake(), snakeOne.getLengthOfSnake(), snakeOne.getDelta_x(), snakeOne.getDelta_y(), gameBoard, snakeOne);
		if (mode == "2") {
			Print_snake(snakeTwo.getX_coordinate_of_snake(), snakeTwo.getY_coordinate_of_snake(), snakeTwo.getLengthOfSnake(), snakeTwo.getDelta_x(), snakeTwo.getDelta_y(), gameBoard, snakeTwo);
		}

		snakeOne.Delta_snake();
		if (mode == "2") {
			snakeTwo.Delta_snake();
		}

		gameBoard.Symbol_to_point(snakeOne.getFoodX(), snakeOne.getFoodY(), char(142), snakeOne.get_SNAKE_HEAD_FOREGROUND(), BACKGROUND);
		if (mode == "2") {
			gameBoard.Symbol_to_point(snakeTwo.getFoodX(), snakeTwo.getFoodY(), char(142), snakeTwo.get_SNAKE_HEAD_FOREGROUND(), BACKGROUND);
		}

		info(gameBoard, snakeOne, snakeTwo, MAX_X, MAX_Y, mode);

		
		if (mode == "2") {
			Sleep((snakeOne.getD_Delay()+ snakeTwo.getD_Delay())/2);
		}
		else {
			Sleep(snakeOne.getD_Delay());
		}
	}

	return 0;
}
