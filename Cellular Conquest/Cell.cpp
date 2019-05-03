#include "Cell.h"



Cell::Cell()
{
	xCoord = 0;
	yCoord = 0;
}

Cell::Cell(int xCoord, int yCoord, Colony * myColony)
{
	initialize(xCoord, yCoord, myColony);
}


Cell::~Cell()
{
}

void Cell::initialize(int xCoord, int yCoord, Colony * myColony)
{
	this->xCoord = xCoord;
	this->yCoord = yCoord;
	this->myColony = myColony;
	pixel = sf::RectangleShape(sf::Vector2f(1, 1));
	pixel.setPosition(sf::Vector2f(xCoord, yCoord));
	pixel.setFillColor(myColony->teamColor);
	locked = false;
}

void Cell::joinColony(Colony * myColony)
{
	this->myColony = myColony;
	myColony->numberOfCells++;
	pixel.setFillColor(myColony->teamColor);
	locked = true;
}

void Cell::unlock()
{
	locked = false;
}
