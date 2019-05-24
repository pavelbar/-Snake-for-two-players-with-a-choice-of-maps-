#pragma once
class Snake
{
public:

	size_t MAX_X = 0;
	size_t MAX_Y = 0;

	size_t length_of_snake = 1;//длина змейки
	size_t D_print_speed = 1;//Cкорость змейки

	//D - delay
	size_t D_delay = 100;//Задержка
	size_t D_count_for_delay = 0;//Счетчик для уменьшения задержки - увеличения скорости змейки

	size_t *p_X_coordinate_of_snake;//массив координат Х змейки
	size_t *p_Y_coordinate_of_snake;//массив координат У змейки

	int delta_x = 0, delta_y = 0;//Предыдущее изменение позиции

	size_t food_x = int(MAX_X / 4);//Координаты положения еды
	size_t food_y = int(MAX_Y / 4);//Координаты положения еды

	bool need_food = true;

	Snake(size_t maxX, size_t maxY);
	~Snake();

	void Generation_of_food_coordinates();
	void Delta_snake();
	void Correction_of_oordinates();
	void Coordinate_transformation_automatically();
	void Coordinate_transformation_by_button(int code);
	size_t getLengthOfSnake();
	size_t getSpeedOfSnake();
	bool getNeedFood();
	void setNeedFood(bool val);
	size_t getFoodX();
	size_t getFoodY();
	void setFoodX(size_t val);
	void setFoodY(size_t val);
	size_t * getX_coordinate_of_snake();
	size_t * getY_coordinate_of_snake();
	size_t getD_Delay();
	int getDelta_x();
	int getDelta_y();
};

