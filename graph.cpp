#include "stdafx.h"

#include <windows.h>
#include <iostream> 
#include <conio.h> 
#include <random>

using namespace std;

const int MAX_Y = 22 + 2;//стр
const int MAX_X = 77 + 2;//столб
const int START_DELAY = 50;//задержка

enum ConsoleColor { Black = 0, Blue, Green, Cyan, Red, Magenta, Brown, LightGray, DarkGray, LightBlue, LightGreen, LightCyan, LightRed, LightMagenta, Yellow, White };

ConsoleColor FOREGROUND = White;
ConsoleColor BACKGROUND = Black;

void Graph_border(int MAX_X, int MAX_Y)
{
	cout << char(201);//"╔"
	for (int count_column = 1; count_column < MAX_X - 1; count_column++)
		cout << char(205);//"═"
	cout << char(187) << endl;//"╗"

	for (int count_line = 1; count_line < MAX_Y - 1; count_line++)
	{
		for (int count_column = 0; count_column < MAX_X; count_column++)
			if ((count_column == 0) || (count_column == (MAX_X - 1))) cout <<char(186);//"║"
			else cout << '\0';//" 
			cout << endl;
	}

	cout << char(200);//"╚"
	for (int count_column = 1; count_column < MAX_X - 1; count_column++)
		cout << char(205);//"═"
	cout << char(188) << endl;//"╝"
}

void Symbol_to_point(int X, int Y, char symbol, ConsoleColor FOREGROUND, ConsoleColor BACKGROUND)
{	
	COORD coord;
	coord.X = X;
	coord.Y = Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((BACKGROUND << 4) | FOREGROUND));
	cout << symbol;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((Black << 4) | White));
}

void Coordinate_transformation_by_button(int code, int &X, int &Y, int &delta_x, int &delta_y)
{
		switch (code)
		{
		case 72://up 
		{
			Y--;
		///	if (Y == 1) Y = MAX_Y - 2;
		///	else
			///	if (Y == MAX_Y - 2) Y = 1;

			delta_x = 0;
			delta_y = -1;
		}
		break;

		case 80://down 
		{
			Y++;
			///if (Y == 1) Y = MAX_Y - 2;
			///else
			///	if (Y == MAX_Y - 2) Y = 1;

			delta_x = 0;
			delta_y = 1;
		}
		break;

		case 75://left 
		{
			X--;
		///	if (X == 1) X = MAX_X - 2;
		///	else
		///		if (X == MAX_X - 2) X = 1;

			delta_x = -1;
			delta_y = 0;
		}
		break;

		case 77://right 
		{
			X++;
		///	if (X == 1) X = MAX_X - 2;
			///else
			///	if (X == MAX_X - 2) X = 1;
			delta_x = 1;
			delta_y = 0;
		}
		break;

		case 27://ESC
			exit(0);
			break;
		}
	
}

void Coordinate_transformation_automatically(int &X, int &Y, int &delta_x, int &delta_y)
{
	X = X + delta_x;
	Y = Y + delta_y;

	///if (Y == 1) Y = MAX_Y - 2;
	///	else
	///		if (Y == MAX_Y - 2) Y = 1;
	///	if (X == 1) X = MAX_X - 2;
	///else
	///	if (X == MAX_X - 2) X = 1;
}

void Correction_of_oordinates (int &X, int &Y)
{
	//zone up (1-77;0)
	if ((X >= 1) && (X <= (MAX_X-2)) && (Y == 0)) Y = (MAX_Y - 2);

	//zone right (78;1-22)
	if ((X == (MAX_X - 1)) && (Y >= 1) && (Y <= (MAX_Y - 2))) X = 1;

	//zone down (1-77;23)
	if ((X >= 1) && (X <= (MAX_X - 2)) && (Y == (MAX_Y - 1))) Y = 1;

	//zone left (0;1-22)
	if ((X == 0) && (Y >= 1) && (Y <= (MAX_Y - 2))) X = (MAX_X - 2);
}

void Generation_of_food_coordinates(int &food_x, int &food_y, int X, int Y)
{
	random_device random_device; 
	mt19937 generator(random_device()); 								
	uniform_int_distribution<int> gen_X(1, (MAX_X - 2)); // Равномерное распределение [a, b]
	uniform_int_distribution<int> gen_Y(1, (MAX_Y - 2)); // Равномерное распределение [a, c]
	int rnd_X = gen_X(generator);
	int rnd_Y = gen_Y(generator);
	while ( (rnd_X == food_x) || (rnd_X == X))
		rnd_X = gen_X(generator);

	while ((rnd_Y == food_y) || (rnd_Y == Y))
		rnd_Y = gen_Y(generator);

	food_x = rnd_X;
	food_y = rnd_Y;
}

int main()
{
	int X = int(MAX_X/2), Y = int(MAX_Y / 2);//Начальное положение точки
	int delta_x = 0, delta_y = 0;//Предыдущее изменение позиции
	int food_x = X, food_y = Y;//Координаты положения еды
	bool need_food = 1;

	Graph_border(MAX_X, MAX_Y);//start

	while (true)
	{
		if (need_food == 1)
		{
			Symbol_to_point(food_x, food_y, '\0', FOREGROUND, BACKGROUND);
			Generation_of_food_coordinates(food_x, food_y, X, Y);
			Symbol_to_point(food_x, food_y, 'F', FOREGROUND, BACKGROUND);
			need_food = 0;
		}
		
		Symbol_to_point(X, Y, '\0', FOREGROUND, BACKGROUND);
		if (_kbhit() != 0) Coordinate_transformation_by_button(_getch(), X, Y, delta_x, delta_y);//если кнопка нажата
		else 
			Coordinate_transformation_automatically(X, Y, delta_x, delta_y);//если кнопка не нажата
		
		Correction_of_oordinates(X, Y);
		Symbol_to_point(X, Y, '*', FOREGROUND, BACKGROUND);

		Sleep(START_DELAY);
	}

	return 0;
}
