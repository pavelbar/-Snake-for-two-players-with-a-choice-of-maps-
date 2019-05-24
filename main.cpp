#include "stdafx.h"
#include "Graph.h"
#include "Snake.h"
#include <conio.h>//_kbhit
#include "windows.h"//sleep


using namespace std;

void Clear_snake(size_t *X, size_t *Y, size_t len, Graph &gameBoard)
{
	for (size_t i = 0; i < len; i++)
		gameBoard.Symbol_to_point(X[i], Y[i], '\0', gameBoard.getConsoleColor_FOREGROUND(), gameBoard.getConsoleColor_BACKGROUND());
}

void Print_snake(size_t *X, size_t *Y, size_t len, int delta_x, int delta_y, Graph &gameBoard)
{

	if ((delta_x == 0) && (delta_y == 0)) 	gameBoard.Symbol_to_point(X[0], Y[0], char(142), gameBoard.getConsoleColor_SNAKE_HEAD_FOREGROUND(), gameBoard.getConsoleColor_BACKGROUND());
	if ((delta_x == -1) && (delta_y == 0)) 	gameBoard.Symbol_to_point(X[0], Y[0], '<', gameBoard.getConsoleColor_SNAKE_HEAD_FOREGROUND(), gameBoard.getConsoleColor_BACKGROUND());
	if ((delta_x == 1) && (delta_y == 0)) 	gameBoard.Symbol_to_point(X[0], Y[0], '>', gameBoard.getConsoleColor_SNAKE_HEAD_FOREGROUND(), gameBoard.getConsoleColor_BACKGROUND());
	if ((delta_x == 0) && (delta_y == 1)) 	gameBoard.Symbol_to_point(X[0], Y[0], char(194), gameBoard.getConsoleColor_SNAKE_HEAD_FOREGROUND(), gameBoard.getConsoleColor_BACKGROUND());
	if ((delta_x == 0) && (delta_y == -1)) 	gameBoard.Symbol_to_point(X[0], Y[0], '^', gameBoard.getConsoleColor_SNAKE_HEAD_FOREGROUND(), gameBoard.getConsoleColor_BACKGROUND());

	for (size_t i = 1; i < len; i++)
		gameBoard.Symbol_to_point(X[i], Y[i], char(142), gameBoard.getConsoleColor_SNAKE_BODY_FOREGROUND(), gameBoard.getConsoleColor_BACKGROUND()); //* SNAKE_BODY_BACKGROUND
}
void update(Graph &gameBoard, Snake &snake, size_t MAX_X, size_t MAX_Y) {
	gameBoard.String_to_point(1, MAX_Y, "Score: ", gameBoard.getConsoleColor_SCORE(), gameBoard.getConsoleColor_BACKGROUND());
	gameBoard.String_to_point(8, MAX_Y, to_string(snake.getLengthOfSnake()), gameBoard.getConsoleColor_VAL_SCORE(), gameBoard.getConsoleColor_BACKGROUND());
	gameBoard.String_to_point(12, MAX_Y, " | Speed: ", gameBoard.getConsoleColor_SPEED(), gameBoard.getConsoleColor_BACKGROUND());
	gameBoard.String_to_point(22, MAX_Y, to_string(snake.getSpeedOfSnake()), gameBoard.getConsoleColor_VAL_SPEED(), gameBoard.getConsoleColor_BACKGROUND());
}

int main()
{
	const size_t MAX_Y = 21 + 2;//стр
	const size_t MAX_X = 77 + 2;//столб

	Graph gameBoard(MAX_X, MAX_Y);
	Snake snakeOne(MAX_X, MAX_Y);

	update(gameBoard, snakeOne, MAX_X, MAX_Y);
	while (true)
	{
		if (snakeOne.getNeedFood() == true)
		{
			gameBoard.Symbol_to_point(snakeOne.getFoodX(), snakeOne.getFoodY(), '\0', gameBoard.getConsoleColor_FOREGROUND(), gameBoard.getConsoleColor_BACKGROUND());
			snakeOne.Generation_of_food_coordinates();

			gameBoard.Symbol_to_point(snakeOne.getFoodX(), snakeOne.getFoodY(), char(142), gameBoard.getConsoleColor_FOOD_FOREGROUND(), gameBoard.getConsoleColor_BACKGROUND());
			snakeOne.setNeedFood(false);
		}

		Clear_snake(snakeOne.getX_coordinate_of_snake(), snakeOne.getY_coordinate_of_snake(), snakeOne.getLengthOfSnake(), gameBoard);
		if (_kbhit() != 0) {
			snakeOne.Coordinate_transformation_by_button(_getch());//если кнопка нажата
		}
		else {
			snakeOne.Coordinate_transformation_automatically();//если кнопка не нажата
		}
		snakeOne.Correction_of_oordinates();
		Print_snake(snakeOne.getX_coordinate_of_snake(), snakeOne.getY_coordinate_of_snake(), snakeOne.getLengthOfSnake(), snakeOne.getDelta_x(), snakeOne.getDelta_y(), gameBoard);

		snakeOne.Delta_snake();
		update(gameBoard, snakeOne, MAX_X, MAX_Y);

		Sleep(snakeOne.getD_Delay());
	}

	return 0;
}
