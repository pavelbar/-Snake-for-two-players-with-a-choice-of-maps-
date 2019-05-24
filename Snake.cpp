#include "stdafx.h"
#include "Snake.h"
#include <random>
#include <ctime>  

Snake::Snake(size_t maxX, size_t maxY)
{
	MAX_X = maxX;
	MAX_Y = maxY;

	p_X_coordinate_of_snake = new size_t[MAX_X * MAX_Y];//массив координат Х змейки
	p_Y_coordinate_of_snake = new size_t[MAX_X * MAX_Y];//массив координат У змейки

	p_X_coordinate_of_snake[0] = size_t(MAX_X / 2);//Начальное положение змейки
	p_Y_coordinate_of_snake[0] = size_t(MAX_Y / 2);//Начальное положение змейки
	Generation_of_food_coordinates();
}

void Snake::Generation_of_food_coordinates()
{
	std::random_device random_device;
	std::mt19937 generator(random_device());
	std::uniform_int_distribution<int> gen_X(1, (MAX_X - 2)); // Равномерное распределение [a, b]
	std::uniform_int_distribution<int> gen_Y(1, (MAX_Y - 2)); // Равномерное распределение [a, c]
	int rnd_X = gen_X(generator);
	int rnd_Y = gen_Y(generator);

	bool stop = true;

	while (stop)
	{
		rnd_X = gen_X(generator);

		int sum_tmp = 0;
		for (size_t i = 0; i < length_of_snake; i++)
			if (rnd_X != p_X_coordinate_of_snake[i]) sum_tmp++;

		if ((rnd_X != food_x) && (sum_tmp == length_of_snake)) stop = false;
	}

	stop = true;

	while (stop)
	{
		rnd_Y = gen_Y(generator);

		int sum_tmp = 0;
		for (size_t i = 0; i < length_of_snake; i++)
			if (rnd_Y != p_Y_coordinate_of_snake[i]) sum_tmp++;

		if ((rnd_Y != food_y) && (sum_tmp == length_of_snake)) stop = false;
	}

	food_x = rnd_X;
	food_y = rnd_Y;

}

void Snake::Delta_snake()
{
	if ((p_X_coordinate_of_snake[0] == food_x) && (p_Y_coordinate_of_snake[0] == food_y))
	{
		need_food = 1;
		length_of_snake++;


		D_count_for_delay++;
		if (D_count_for_delay == 9)
		{
			D_count_for_delay = 0;
			D_print_speed++;
			if (D_delay >= 20) D_delay = D_delay - 10;
		}
	}
}

void Snake::Coordinate_transformation_automatically()
{
	// Передвигаем тело змейки.
	for (int i = length_of_snake; i >= 1; --i)
	{
		p_X_coordinate_of_snake[i] = p_X_coordinate_of_snake[i - 1];
		p_Y_coordinate_of_snake[i] = p_Y_coordinate_of_snake[i - 1];
	}

	// Передвигаем голову змейки.
	p_X_coordinate_of_snake[0] = p_X_coordinate_of_snake[0] + delta_x;
	p_Y_coordinate_of_snake[0] = p_Y_coordinate_of_snake[0] + delta_y;
}

void Snake::Correction_of_oordinates()
{
	for (size_t i = 0; i < length_of_snake; i++)
	{
		//zone up (1-77;0)
		if ((p_X_coordinate_of_snake[i] >= 1) && (p_X_coordinate_of_snake[i] <= (MAX_X - 2)) && (p_Y_coordinate_of_snake[i] == 0)) p_Y_coordinate_of_snake[i] = (MAX_Y - 2);

		//zone right (78;1-22)
		if ((p_X_coordinate_of_snake[i] == (MAX_X - 1)) && (p_Y_coordinate_of_snake[i] >= 1) && (p_Y_coordinate_of_snake[i] <= (MAX_Y - 2))) p_X_coordinate_of_snake[i] = 1;

		//zone down (1-77;23)
		if ((p_X_coordinate_of_snake[i] >= 1) && (p_X_coordinate_of_snake[i] <= (MAX_X - 2)) && (p_Y_coordinate_of_snake[i] == (MAX_Y - 1))) p_Y_coordinate_of_snake[i] = 1;

		//zone left (0;1-22)
		if ((p_X_coordinate_of_snake[i] == 0) && (p_Y_coordinate_of_snake[i] >= 1) && (p_Y_coordinate_of_snake[i] <= (MAX_Y - 2))) p_X_coordinate_of_snake[i] = (MAX_X - 2);
	}

}

void Snake::Coordinate_transformation_by_button(int code)
{

	switch (code)
	{
	case 72://up 
	{
		delta_x = 0;
		delta_y = -1;

		// Передвигаем тело змейки.
		for (size_t i = length_of_snake; i >= 1; --i)
		{
			p_X_coordinate_of_snake[i] = p_X_coordinate_of_snake[i - 1];
			p_Y_coordinate_of_snake[i] = p_Y_coordinate_of_snake[i - 1];
		}

		// Передвигаем голову змейки.
		p_X_coordinate_of_snake[0] = p_X_coordinate_of_snake[0] + delta_x;
		p_Y_coordinate_of_snake[0] = p_Y_coordinate_of_snake[0] + delta_y;
	}
	break;

	case 80://down 
	{
		delta_x = 0;
		delta_y = 1;

		// Передвигаем тело змейки.
		for (size_t i = length_of_snake; i >= 1; --i)
		{
			p_X_coordinate_of_snake[i] = p_X_coordinate_of_snake[i - 1];
			p_Y_coordinate_of_snake[i] = p_Y_coordinate_of_snake[i - 1];
		}

		// Передвигаем голову змейки.
		p_X_coordinate_of_snake[0] = p_X_coordinate_of_snake[0] + delta_x;
		p_Y_coordinate_of_snake[0] = p_Y_coordinate_of_snake[0] + delta_y;
	}
	break;

	case 75://left 
	{
		delta_x = -1;
		delta_y = 0;

		// Передвигаем тело змейки.
		for (size_t i = length_of_snake; i >= 1; --i)
		{
			p_X_coordinate_of_snake[i] = p_X_coordinate_of_snake[i - 1];
			p_Y_coordinate_of_snake[i] = p_Y_coordinate_of_snake[i - 1];
		}

		// Передвигаем голову змейки.
		p_X_coordinate_of_snake[0] = p_X_coordinate_of_snake[0] + delta_x;
		p_Y_coordinate_of_snake[0] = p_Y_coordinate_of_snake[0] + delta_y;
	}
	break;

	case 77://right 
	{
		delta_x = 1;
		delta_y = 0;

		// Передвигаем тело змейки.
		for (size_t i = length_of_snake; i >= 1; --i)
		{
			p_X_coordinate_of_snake[i] = p_X_coordinate_of_snake[i - 1];
			p_Y_coordinate_of_snake[i] = p_Y_coordinate_of_snake[i - 1];
		}

		// Передвигаем голову змейки.
		p_X_coordinate_of_snake[0] = p_X_coordinate_of_snake[0] + delta_x;
		p_Y_coordinate_of_snake[0] = p_Y_coordinate_of_snake[0] + delta_y;
	}
	break;

	case 27://ESC
		exit(0);
		break;
	}
}

size_t Snake::getLengthOfSnake()
{
	return  length_of_snake;
}

size_t Snake::getSpeedOfSnake()
{
	return D_print_speed;
}

bool Snake::getNeedFood()
{
	return need_food;
}

void Snake::setNeedFood(bool val)
{
	need_food = val;
}

size_t Snake::getFoodX()
{
	return food_x;
}

size_t Snake::getFoodY()
{
	return food_y;
}

void Snake::setFoodX(size_t val)
{
	food_x = val;
}

void Snake::setFoodY(size_t val)
{
	food_y = val;
}

size_t * Snake::getX_coordinate_of_snake()
{
	return p_X_coordinate_of_snake;
}

size_t * Snake::getY_coordinate_of_snake()
{
	return p_Y_coordinate_of_snake;
}

size_t Snake::getD_Delay()
{
	return D_delay;
}

int Snake::getDelta_x()
{
	return delta_x;
}

int Snake::getDelta_y()
{
	return delta_y;
}

Snake::~Snake()
{
	delete[] p_X_coordinate_of_snake;
	delete[] p_Y_coordinate_of_snake;
}
