#include "stdafx.h"
#include "Graph.h"
#include <windows.h>
#include <iostream> 

using std::cout;
using std::endl;

Graph::Graph(size_t maxX, size_t maxY, int MCOLOR_BACKGROUND, int MCOLOR_BORDER)
{
	MAX_X = maxX;//стр
	MAX_Y = maxY;//столб

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((MCOLOR_BACKGROUND << 4) | MCOLOR_BORDER));
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
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((COLOR_BLACK << 4) | COLOR_WHITE));
}

void Graph::Symbol_to_point(int X, int Y, char symbol, int MCOLOR_FOREGROUND, int MCOLOR_BACKGROUND)
{
	COORD coord;
	coord.X = X;
	coord.Y = Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((MCOLOR_BACKGROUND << 4) | MCOLOR_FOREGROUND));
	cout << symbol;
	cout.flush();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((COLOR_BLACK << 4) | COLOR_WHITE));
}

void Graph::String_to_point(int X, int Y, string str, int MCOLOR_FOREGROUND, int MCOLOR_BACKGROUND)
{
	COORD coord;
	coord.X = X;
	coord.Y = Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((MCOLOR_BACKGROUND << 4) | MCOLOR_FOREGROUND));
	cout << str;
	cout.flush();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((COLOR_BLACK << 4) | COLOR_WHITE));
}

size_t Graph::getMaxX() {
	return MAX_X;
}

size_t Graph::getMaxY() {
	return MAX_Y;
}

Graph::~Graph()
{
}
