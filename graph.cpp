// graph.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream> 
#include <conio.h> 

using namespace std;

const int MAX_X = 10 + 2;//стр
const int MAX_Y = 10 + 2;//столб

void Control(int code, int **pMas, int *pXandY)
{
	int result = 0;
	pMas[pXandY[0]][pXandY[1]] = 0;//" "
	switch (code)

	{
	case 72://up 
		if (pXandY[0] == 1) pXandY[0] = MAX_X-2;
		else
		pXandY[0]--;
		break;

	case 80://down 
		if (pXandY[0] == MAX_X - 2) pXandY[0] = 1;
		else
		pXandY[0]++;
		break;

	case 75://left 
		if (pXandY[1] == 1) pXandY[1] = MAX_Y - 2;
		else
		pXandY[1]--;
		break;

	case 77://right 
		if (pXandY[1] == MAX_Y - 2) pXandY[1] = 1;
		else
		pXandY[1]++;
		break;
	}
	pMas[pXandY[0]][pXandY[1]] = 7;//*

}

void graph(int **pMas)
{
	// 0 - " "
	// 1 - "═"
	// 2 - "║"
	// 7 - "*"

	// 3 - "╚"
	// 4 - "╝"

	// 5 - "╔"
	// 6 - "╗"
	system("cls");

	for (int count_row = 0; count_row < MAX_X; count_row++)
	{
		for (int count_column = 0; count_column < MAX_Y; count_column++)
		{
			if (pMas[count_row][count_column] == 0) cout <<'\0';//" "
			if (pMas[count_row][count_column] == 1) cout << '-';//"═"
			if (pMas[count_row][count_column] == 2) cout << '|';//"║"
			if (pMas[count_row][count_column] == 3) cout << '|';//"╚"
			if (pMas[count_row][count_column] == 4) cout << '|';//"╝"
			if (pMas[count_row][count_column] == 5) cout << '|';//"╔"
			if (pMas[count_row][count_column] == 6) cout << '|';//"╗"
			if (pMas[count_row][count_column] == 7) cout << '*';//"*"
		}
		cout << endl;
	}
	
	/*
	cout << endl;
	cout << endl;
	for (int count_row = 0; count_row < MAX_X; count_row++)
	{
		for (int count_column = 0; count_column < MAX_Y; count_column++)
			cout  << pMas[count_row][count_column] << "   ";
		cout << endl;
	}
	*/
}


int main()
{
	int *pXandY = new int[2]; //стр
	pXandY[0] = 1;//x
	pXandY[1] = 1;//y
	
	//создание
	int **pMas = new int*[MAX_X]; //стр
	for (int i = 0; i < MAX_X; i++)
		pMas[i] = new int[MAX_Y]; //столб
										
	for (int count_row = 0; count_row < MAX_X; count_row++)
		for (int count_column = 0; count_column < MAX_Y; count_column++)
			pMas[count_row][count_column] = 0; 
	//заполнение 
	// 0 - "   "
	// 1 - "═"
	// 2 - "║"
	// 7 - "*"

	// 3 - "╚"
	// 4 - "╝"

	// 5 - "╔"
	// 6 - "╗"

	pMas[pXandY[0]][pXandY[1]] = 7;//*
	pMas[MAX_X - 1][0] = 3;//╚
	pMas[MAX_X - 1][MAX_Y - 1] = 4;//╝
	pMas[0][0] = 5; //╔
	pMas[0][MAX_Y - 1] = 6; //╗


	for (int count_column = 1; count_column < MAX_Y-1; count_column++)
	{
		pMas[0][count_column] = 1;
		pMas[MAX_X-1][count_column] = 1;
	}

	for (int count_row = 1; count_row < MAX_X-1; count_row++)
	{
		pMas[count_row][0] = 2;//║
		pMas[count_row][MAX_Y - 1] = 2;//║
	}

	while (true)
	{
		Control(_getch(), pMas, pXandY);
		graph(pMas);
	}

	for (int count = 0; count < MAX_X; count++)
		delete[]pMas[count];
	return 0;
}