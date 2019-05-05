#pragma once
#include "Colony.h"
#include <SFML/Graphics.hpp>
#include <cstdlib>
class Cell
{
public:
	
	Colony* myColony;
	int xCoord;
	int yCoord;
	int attack;
	int defense;
	bool locked;

	Cell();
	Cell(int xCoord, int yCoord, Colony* myColony);
	~Cell();

	void initialize(int xCoord, int yCoord, Colony* myColony);
	void joinColony(Colony *myColony);
	void attackCell(Cell* toAttack);
	void unlock();
	sf::RectangleShape pixel;
};

