#include "Cell.h"
#include "iostream"


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

void Cell::initialize(int xCoord, int yCoord, Colony * newColony)
{
	this->xCoord = xCoord;
	this->yCoord = yCoord;
	myColony = newColony;
	pixel = sf::RectangleShape(sf::Vector2f(1, 1));
	pixel.setPosition(sf::Vector2f(xCoord, yCoord));
	pixel.setFillColor(myColony->teamColor);
	locked = false;
}

void Cell::joinColony(Colony * newColony)
{
	newColony->numberOfCells++;
	myColony->numberOfCells--;//subtract its colonies cells by 1 cuz its leaving
	
	
	myColony = newColony;//assign new colony
	//std::cout <<"numbercells before: "<< this->myColony->numberOfCells << std::endl;
	//myColony->numberOfCells++;//add 1 to the new colony
	//std::cout << "numbercells after: " << this->myColony->numberOfCells << std::endl<<std::endl;
	pixel.setFillColor(myColony->teamColor);
	locked = true;
}

void Cell::unlock()
{
	locked = false;
}
