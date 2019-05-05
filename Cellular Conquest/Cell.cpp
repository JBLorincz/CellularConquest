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
	attack = 0;
	defense = 0;
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
	srand(time(0));
	int neg = 1;
	if (rand() % 2 != 0)
		neg = -1;

	attack = myColony->attack
		+ (rand()% (int)(ceil((double)myColony->attack / 10.0)*neg))
		;

	if (rand() % 2 != 0)
		neg = 1;
	else
		neg = -1;

	defense = myColony->defense 
		+ (rand() % (int)(ceil((double)myColony->defense / 10.0)*neg))
		;

	//std::cout <<"numbercells before: "<< this->myColony->numberOfCells << std::endl;
	//myColony->numberOfCells++;//add 1 to the new colony
	//std::cout << "numbercells after: " << this->myColony->numberOfCells << std::endl<<std::endl;
	pixel.setFillColor(myColony->teamColor);
	locked = true;
}

void Cell::attackCell(Cell * toAttack)
{
	attack++;
	defense++;
	if (attack > toAttack->defense)
	{
		toAttack->joinColony(myColony);
		srand(time(0));
			
			if (rand()%4==0)
				myColony->attack++;
	}
	else
		if (rand() % 2 == 0)
			toAttack->myColony->defense++;
}

void Cell::unlock()
{
	locked = false;
}
