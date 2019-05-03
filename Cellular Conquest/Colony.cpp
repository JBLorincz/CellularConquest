#include "Colony.h"
Colony::Colony()
{
	attack = 1;
	defense = 1;
	numberOfCells = 1;
}

Colony::Colony(sf::Color teamColor)
{
	Colony();
	this->teamColor = teamColor;
}
