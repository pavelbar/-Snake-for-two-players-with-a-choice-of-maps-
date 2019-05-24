#pragma once

#include <string>
using std::string;

class Graph
{
	size_t MAX_X = 0;//стр
	size_t MAX_Y = 0;//столб
public:
	enum ConsoleColor { Black = 0, Blue, Green, Cyan, Red, Magenta, Brown, LightGray, DarkGray, LightBlue, LightGreen, LightCyan, LightRed, LightMagenta, Yellow, White };

	ConsoleColor FOREGROUND = White;
	ConsoleColor BACKGROUND = Black;

	ConsoleColor FOOD_FOREGROUND = LightGreen;
	ConsoleColor FOOD_BACKGROUND = LightGreen;

	ConsoleColor SNAKE_BODY_FOREGROUND = DarkGray;
	ConsoleColor SNAKE_BODY_BACKGROUND = DarkGray;

	ConsoleColor SNAKE_HEAD_FOREGROUND = LightRed;
	ConsoleColor SNAKE_HEAD_BACKGROUND = LightRed;

	ConsoleColor BORDER = LightGray;

	ConsoleColor SPEED = White;
	ConsoleColor SCORE = White;

	ConsoleColor VAL_SPEED = Cyan;
	ConsoleColor VAL_SCORE = Cyan;

	Graph(size_t MAX_X, size_t MAX_Y);
	~Graph();

	void Symbol_to_point(int X, int Y, char symbol, ConsoleColor FOREGROUND, ConsoleColor BACKGROUND);
	void String_to_point(int X, int Y, string str, ConsoleColor FOREGROUND, ConsoleColor BACKGROUND);
	size_t getMaxX();
	size_t getMaxY();

	ConsoleColor getConsoleColor_FOREGROUND();
	ConsoleColor getConsoleColor_BACKGROUND();

	ConsoleColor getConsoleColor_FOOD_FOREGROUND();
	ConsoleColor getConsoleColor_FOOD_BACKGROUND();

	ConsoleColor getConsoleColor_SNAKE_BODY_FOREGROUND();
	ConsoleColor getConsoleColor_SNAKE_BODY_BACKGROUND();

	ConsoleColor getConsoleColor_SNAKE_HEAD_FOREGROUND();
	ConsoleColor getConsoleColor_SNAKE_HEAD_BACKGROUND();

	ConsoleColor getConsoleColor_BORDER();
	ConsoleColor getConsoleColor_SPEED();
	ConsoleColor getConsoleColor_SCORE();
	ConsoleColor getConsoleColor_VAL_SPEED();
	ConsoleColor getConsoleColor_VAL_SCORE();
};

