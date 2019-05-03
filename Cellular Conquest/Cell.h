#pragma once
#include "Colony.h"
#include <SFML/Graphics.hpp>
class Cell
{
public:
	
	Colony* myColony;
	int xCoord;
	int yCoord;
	bool locked;

	Cell();
	Cell(int xCoord, int yCoord, Colony* myColony);
	~Cell();

	void initialize(int xCoord, int yCoord, Colony* myColony);
	void joinColony(Colony *myColony);
	void unlock();
	sf::RectangleShape pixel;
};

