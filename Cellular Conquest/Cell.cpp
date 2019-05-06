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

	int neg = 1;
	if (rand() % 2 != 0)
		neg = -1;

	attack = myColony->attack
		+ (rand()% (int)(ceil((double)myColony->attack /10)*neg))
		;

	if (rand() % 2 != 0)
		neg = 1;
	else
		neg = -1;

	defense = myColony->defense 
		+ (rand() % (int)(ceil((double)myColony->defense/10)*neg))
		;

	
	pixel.setFillColor(myColony->teamColor);
	locked = true;
}

void Cell::attackCell(Cell * toAttack)
{
	
	if(rand()%2==0)
	attack++;


	if(toAttack->myColony->defense==0)
		toAttack->joinColony(myColony);

	if (attack+myColony->attack
	 > toAttack->defense+toAttack->myColony->defense)//if toAttack is losing a cell
	{
			
			if (rand()%2==0)
				myColony->attack++;

				toAttack->myColony->defense++;

			toAttack->joinColony(myColony);
	}
	
	else //if toAttack sucessfully defended
	{
		toAttack->defense++;

		if (rand() % 2 == 0)
		toAttack->myColony->defense++;

		if (rand() % 1000 == 0)
		{
			
			toAttack->myColony->attack *= 2;
			
			toAttack->myColony->defense *= 2;
		}
	}
}

void Cell::unlock()
{
	locked = false;
}
