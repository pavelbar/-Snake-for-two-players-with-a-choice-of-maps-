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
			if ((count_column == 0) || (count_column == (MAX_X - 1))) cout << char(186);//"║"
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

void Coordinate_transformation_by_button(int code, int *X, int *Y, int len, int &delta_x, int &delta_y)
{
	switch (code)
	{
	case 72://up 
	{
		for (int i = 0; i < len; i++)
		Y[i]--;
		delta_x = 0;
		delta_y = -1;
	}
	break;

	case 80://down 
	{
		for (int i = 0; i < len; i++)
		Y[i]++;
		delta_x = 0;
		delta_y = 1;
	}
	break;

	case 75://left 
	{
		for (int i = 0; i < len; i++)
		X[i]--;
		delta_x = -1;
		delta_y = 0;
	}
	break;

	case 77://right 
	{
		for (int i = 0; i < len; i++)
		X[i]++;
		delta_x = 1;
		delta_y = 0;
	}
	break;

	case 27://ESC
		exit(0);
		break;
	}
}

void Coordinate_transformation_automatically(int *X, int *Y, int len, int &delta_x, int &delta_y)
{
	for (int i = 0; i < len; i++)
	{
		X[i] = X[i] + delta_x;
		Y[i] = Y[i] + delta_y;
	}
}

void Correction_of_oordinates(int *X, int *Y, int len)
{
	for (int i = 0; i < len; i++)
	{
		//zone up (1-77;0)
		if ((X[i] >= 1) && (X[i] <= (MAX_X - 2)) && (Y[i] == 0)) Y[i] = (MAX_Y - 2);

		//zone right (78;1-22)
		if ((X[i] == (MAX_X - 1)) && (Y[i] >= 1) && (Y[i] <= (MAX_Y - 2))) X[i] = 1;

		//zone down (1-77;23)
		if ((X[i] >= 1) && (X[i] <= (MAX_X - 2)) && (Y[i] == (MAX_Y - 1))) Y[i] = 1;

		//zone left (0;1-22)
		if ((X[i] == 0) && (Y[i] >= 1) && (Y[i] <= (MAX_Y - 2))) X[i] = (MAX_X - 2);
	}
}

void Generation_of_food_coordinates(int &food_x, int &food_y, int *X, int *Y, int len)
{
	random_device random_device;
	mt19937 generator(random_device());
	uniform_int_distribution<int> gen_X(1, (MAX_X - 2)); // Равномерное распределение [a, b]
	uniform_int_distribution<int> gen_Y(1, (MAX_Y - 2)); // Равномерное распределение [a, c]
	int rnd_X = gen_X(generator);
	int rnd_Y = gen_Y(generator);
	
	bool stop = true;

	while (stop)
	{
		rnd_X = gen_X(generator);

		int sum_tmp = 0;
		for (int i = 0; i < len; i++)
			if (rnd_X != X[i]) sum_tmp++;

		if ((rnd_X != food_x) && (sum_tmp == len)) stop = false;
	}

	stop = true;

	while (stop)
	{
		rnd_Y = gen_Y(generator);

		int sum_tmp = 0;
		for (int i = 0; i < len; i++)
			if (rnd_Y != Y[i]) sum_tmp++;

		if ((rnd_Y != food_y) && (sum_tmp == len)) stop = false;
	}

	food_x = rnd_X;
	food_y = rnd_Y;
}

void Clear_snake(int *X, int *Y, int len, ConsoleColor FOREGROUND, ConsoleColor BACKGROUND)
{
	for (int i = 0; i <len; i++)
		Symbol_to_point(X[i], Y[i], '\0', FOREGROUND, BACKGROUND);
}

void Print_snake(int *X, int *Y, int len, ConsoleColor FOREGROUND, ConsoleColor BACKGROUND)
{
	for (int i = 0; i <len; i++)
		Symbol_to_point(X[i], Y[i], '*', FOREGROUND, BACKGROUND);
}

void Delta_snake(int *X, int *Y, int food_x, int food_y, bool &need_food, int & length_of_snake)
{
	if ((X[0] == food_x) && (Y[0] == food_y))
	{
		need_food = 1;
		length_of_snake++;
	}
}

int main()
{
	int *p_X_coordinate_of_snake = new int[MAX_X * MAX_Y];//массив координат Х змейки
	int *p_Y_coordinate_of_snake = new int[MAX_X * MAX_Y];//массив координат У змейки
	int length_of_snake = 1;//длина змейки

	p_X_coordinate_of_snake[0] = int(MAX_X / 2);//Начальное положение змейки
	p_Y_coordinate_of_snake[0] = int(MAX_Y / 2);//Начальное положение змейки
	///int X = int(MAX_X / 2), Y = int(MAX_Y / 2);//Начальное положение точки
	int delta_x = 0, delta_y = 0;//Предыдущее изменение позиции
	int food_x = int(MAX_X / 2), food_y = int(MAX_Y / 2);//Координаты положения еды
	bool need_food = true;

	Graph_border(MAX_X, MAX_Y);//start

	while (true)
	{
		if (need_food == true)
		{
			Symbol_to_point(food_x, food_y, '\0', FOREGROUND, BACKGROUND);
			Generation_of_food_coordinates(food_x, food_y, p_X_coordinate_of_snake, p_Y_coordinate_of_snake, length_of_snake);
			Symbol_to_point(food_x, food_y, 'F', FOREGROUND, BACKGROUND);
			need_food = false;
		}

		Clear_snake(p_X_coordinate_of_snake, p_Y_coordinate_of_snake, length_of_snake, FOREGROUND, BACKGROUND);
		if (_kbhit() != 0) Coordinate_transformation_by_button(_getch(), p_X_coordinate_of_snake, p_Y_coordinate_of_snake, length_of_snake, delta_x, delta_y);//если кнопка нажата
		else
			Coordinate_transformation_automatically(p_X_coordinate_of_snake, p_Y_coordinate_of_snake, length_of_snake, delta_x, delta_y);//если кнопка не нажата

		Correction_of_oordinates(p_X_coordinate_of_snake, p_Y_coordinate_of_snake, length_of_snake);
		Print_snake(p_X_coordinate_of_snake, p_Y_coordinate_of_snake, length_of_snake, FOREGROUND, BACKGROUND);

		Delta_snake(p_X_coordinate_of_snake, p_Y_coordinate_of_snake, food_x, food_y, need_food, length_of_snake);

		Sleep(START_DELAY);
	}

	delete[] p_X_coordinate_of_snake;
	delete[] p_Y_coordinate_of_snake;
	return 0;
}
