#include "Colony.h"
Colony::Colony()
{
	attack = 1;
	defense = 1;
	numberOfCells = 0;
}

Colony::Colony(sf::Color teamColor)
{
	attack = 1;
	defense = 1;
	numberOfCells = 0;
	
	this->teamColor = teamColor;
}
