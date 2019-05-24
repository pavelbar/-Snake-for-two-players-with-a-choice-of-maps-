#pragma once

#include <string>
using std::string;

class Graph
{
private:
	const int COLOR_BLACK = 0;
	const int COLOR_WHITE = 15;
	size_t MAX_X = 0;//стр
	size_t MAX_Y = 0;//столб
public:

	Graph(size_t MAX_X, size_t MAX_Y, int MCOLOR_BACKGROUND, int MCOLOR_BORDER);
	~Graph();

	void Symbol_to_point(int X, int Y, char symbol, int MCOLOR_FOREGROUND, int MCOLOR_BACKGROUND);
	void String_to_point(int X, int Y, string str, int MCOLOR_FOREGROUND, int MCOLOR_BACKGROUND);
	size_t getMaxX();
	size_t getMaxY();
};

