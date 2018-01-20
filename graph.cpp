// graph.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream> 
#include <conio.h> 
#include <windows.h>

using namespace std;

const int MAX_X = 21 + 2;//стр
const int MAX_Y = 76 + 2;//столб


void graph(int **pMas, int &quality, int &CUR_X, int &CUR_Y)
{
	// 0 - "   "
	// 1 - "═"
	// 2 - "║"
	// 7 - "↓"
	// 8 - "↑"
	// 9 - "←"
	// 10 - "→"

	// 3 - "╚"
	// 4 - "╝"

	// 5 - "╔"
	// 6 - "╗"
	system("cls");

	for (int count_row = 0; count_row < CUR_X; count_row++)
	{
		for (int count_column = 0; count_column < CUR_Y; count_column++)
		{
			if (pMas[count_row][count_column] == 0) cout << '\0';//" "
			if (pMas[count_row][count_column] == 7) cout << '*';
				
			if (quality == 1)
			{
				if (pMas[count_row][count_column] == 1) cout << char(205);//"═"
				if (pMas[count_row][count_column] == 2) cout << char(186);//"║"
				if (pMas[count_row][count_column] == 3) cout << char(200);//"╚"
				if (pMas[count_row][count_column] == 4) cout << char(188);//"╝"
				if (pMas[count_row][count_column] == 5) cout << char(201);//"╔"
				if (pMas[count_row][count_column] == 6) cout << char(187);//"╗"
			}
		}
		cout << endl;
	}
}

void Control(int code, int **pMas, int &X, int &Y, int &quality, int &CUR_X, int &CUR_Y)
{
	pMas[X][Y] = 0;//" "
	switch (code)

	{
	case 32://space
		if (quality == 1) quality--;
		else
			quality++;
		break;

	case 72://up 
		if (X == 1) X = CUR_X-2;
		else
		X--;
		break;

	case 80://down 
		if (X == CUR_X - 2) X = 1;
		else
		X++;
		break;

	case 75://left 
		if (Y == 1) Y = CUR_Y - 2;
		else
		Y--;
		break;

	case 77://right 
		if (Y == CUR_Y - 2) Y = 1;
		else
		Y++;
		break;
	}
	pMas[X][Y] = 7;
	graph(pMas, quality, CUR_X, CUR_Y);
}

int main()
{
	int CUR_X = MAX_X;
	int CUR_Y = MAX_Y;
	int quality_graphics = 1;
	cout << "Press space twice to change the quality of the graphics.";
	cout <<endl <<"Press any key to start." << endl;
	system("pause");
	int X = 1;
	int Y = 1;
	
	//создание
	int **pMas = new int*[CUR_X]; //стр
	for (int i = 0; i < CUR_X; i++)
		pMas[i] = new int[CUR_Y]; //столб
										
	for (int count_row = 0; count_row < CUR_X; count_row++)
		for (int count_column = 0; count_column < CUR_Y; count_column++)
			pMas[count_row][count_column] = 0; 
	//заполнение 
	// 0 - "   "
	// 1 - "═"
	// 2 - "║"
	// 7 - "↓"
	// 8 - "↑"
	// 9 - "←"
	// 10 - "→"

	// 3 - "╚"
	// 4 - "╝"

	// 5 - "╔"
	// 6 - "╗"

	pMas[X][Y] = 7;//*
	pMas[CUR_X - 1][0] = 3;//╚
	pMas[CUR_X - 1][CUR_Y - 1] = 4;//╝
	pMas[0][0] = 5; //╔
	pMas[0][CUR_Y - 1] = 6; //╗


	for (int count_column = 1; count_column < CUR_Y-1; count_column++)
	{
		pMas[0][count_column] = 1;
		pMas[CUR_X-1][count_column] = 1;
	}

	for (int count_row = 1; count_row < CUR_X-1; count_row++)
	{
		pMas[count_row][0] = 2;//║
		pMas[count_row][CUR_Y - 1] = 2;//║
	}


	graph(pMas, quality_graphics, CUR_X, CUR_Y);
	while (true)
	{
		while (_getch())
			Control(_getch(), pMas, X, Y, quality_graphics, CUR_X, CUR_Y);
		Sleep(40);
		
	}

	for (int count = 0; count < CUR_X; count++)
		delete[]pMas[count];
	return 0;
}