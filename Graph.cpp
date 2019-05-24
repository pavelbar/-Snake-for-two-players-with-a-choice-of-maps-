#include "stdafx.h"
#include "Graph.h"
#include <windows.h>
#include <iostream> 

using std::cout;
using std::endl;

Graph::Graph(size_t maxX, size_t maxY)
{
	MAX_X = maxX;//стр
	MAX_Y = maxY;//столб

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((BACKGROUND << 4) | BORDER));
	cout << char(201);//"╔"
	for (int count_column = 1; count_column < MAX_X - 1; count_column++)
		cout << char(205);//"═"
	cout << char(187) << endl;//"╗"

	for (int count_line = 1; count_line < MAX_Y - 1; count_line++)
	{
		for (int count_column = 0; count_column < MAX_X; count_column++)
			if ((count_column == 0) || (count_column == (MAX_X - 1))) cout << char(186);//"║"
			else cout << '\0';//" 
			cout << endl;
	}

	cout << char(200);//"╚"
	for (int count_column = 1; count_column < MAX_X - 1; count_column++)
		cout << char(205);//"═"
	cout << char(188) << endl;//"╝"
	cout.flush();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((Black << 4) | White));
}

void Graph::Symbol_to_point(int X, int Y, char symbol, ConsoleColor FOREGROUND, ConsoleColor BACKGROUND)
{
	COORD coord;
	coord.X = X;
	coord.Y = Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((BACKGROUND << 4) | FOREGROUND));
	cout << symbol;
	cout.flush();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((Black << 4) | White));
}

void Graph::String_to_point(int X, int Y, string str, ConsoleColor FOREGROUND, ConsoleColor BACKGROUND)
{
	COORD coord;
	coord.X = X;
	coord.Y = Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((BACKGROUND << 4) | FOREGROUND));
	cout << str;
	cout.flush();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((Black << 4) | White));
}

size_t Graph::getMaxX() {
	return MAX_X;
}

size_t Graph::getMaxY() {
	return MAX_Y;
}


Graph::ConsoleColor Graph::getConsoleColor_FOREGROUND() {
	return FOREGROUND;
}

Graph::ConsoleColor Graph::getConsoleColor_BACKGROUND() {
	return BACKGROUND;
}

Graph::ConsoleColor Graph::getConsoleColor_FOOD_FOREGROUND() {
	return FOOD_FOREGROUND;
}

Graph::ConsoleColor Graph::getConsoleColor_FOOD_BACKGROUND() {
	return FOOD_BACKGROUND;
}

Graph::ConsoleColor Graph::getConsoleColor_SNAKE_BODY_FOREGROUND() {
	return SNAKE_BODY_FOREGROUND;
}

Graph::ConsoleColor Graph::getConsoleColor_SNAKE_BODY_BACKGROUND() {
	return SNAKE_BODY_BACKGROUND;
}

Graph::ConsoleColor Graph::getConsoleColor_SNAKE_HEAD_FOREGROUND() {
	return SNAKE_HEAD_FOREGROUND;
}

Graph::ConsoleColor Graph::getConsoleColor_SNAKE_HEAD_BACKGROUND() {
	return SNAKE_HEAD_BACKGROUND;
}

Graph::ConsoleColor Graph::getConsoleColor_BORDER() {
	return BORDER;
}

Graph::ConsoleColor Graph::getConsoleColor_SPEED() {
	return SPEED;
}

Graph::ConsoleColor Graph::getConsoleColor_SCORE() {
	return SCORE;
}

Graph::ConsoleColor Graph::getConsoleColor_VAL_SPEED() {
	return VAL_SPEED;
}

Graph::ConsoleColor Graph::getConsoleColor_VAL_SCORE() {
	return VAL_SCORE;
}



Graph::~Graph()
{
}
