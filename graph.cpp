#include "stdafx.h"

#include <windows.h>
#include <iostream> 
#include <conio.h> 

using namespace std;

const int MAX_Y = 22 + 2;//стр
const int MAX_X = 77 + 2;//столб
const int TACT = 70;//задержка

enum ConsoleColor { Black = 0, Blue, Green, Cyan, Red, Magenta, Brown, LightGray, DarkGray, LightBlue, LightGreen, LightCyan, LightRed, LightMagenta, Yellow, White };

ConsoleColor FOREGROUND = White;
ConsoleColor BACKGROUND = Black;

void symbolToPoint(int column, int line, char symbol, ConsoleColor FOREGROUND, ConsoleColor BACKGROUND)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((BACKGROUND << 4) | FOREGROUND));
	cout << symbol;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((Black << 4) | White));
}

void Control(int code, int &X, int &Y, int CUR_X, int CUR_Y)
{
	symbolToPoint(X, Y, '\0', FOREGROUND, BACKGROUND);
	switch (code)
	{
	case 72://up 
		if (Y == 1) Y = CUR_Y - 2;
		else
			Y--;
		break;

	case 80://down 
		if (Y == CUR_Y - 2) Y = 1;
		else
			Y++;
		break;

	case 75://left 
		if (X == 1) X = CUR_X - 2;
		else
			X--;
		break;

	case 77://right 
		if (X == CUR_X - 2) X = 1;
		else
			X++;
		break;

	case 27://ESC
		exit(0);
		break;
	}
	symbolToPoint(X, Y, '*', FOREGROUND, BACKGROUND);
}

void graphBorder(int CUR_X, int CUR_Y)
{
	cout << char(201);//"╔"
	for (int count_column = 1; count_column < CUR_X - 1; count_column++)
		cout <<char(205);//"═"
	cout <<char(187) <<endl;//"╗"
	
	for (int count_line = 1; count_line < CUR_Y - 1; count_line++)
	{
		for (int count_column = 0; count_column < CUR_X; count_column++)
			if ((count_column == 0) || (count_column == (CUR_X-1) )) cout << char(186);//"║"
			else cout << '\0';//" 
		cout << endl;
	}
	
	cout << char(200);//"╚"
	for (int count_column = 1; count_column < CUR_X - 1; count_column++)
		cout << char(205);//"═"
	cout << char(188) <<endl;//"╝"
}

int main()
{
	int CUR_X = MAX_X, CUR_Y = MAX_Y;//Максимальное разрешение
	int X = 1, Y = 1;//Начальное положение точки
	
	graphBorder(CUR_X, CUR_Y);//start
	symbolToPoint(X, Y, '*', FOREGROUND, BACKGROUND);

	while (true)
	{
		Control(_getch(), X, Y, CUR_X, CUR_Y);
		Sleep(TACT);
	}

	return 0;
}
