#include "GameManager.h"



GameManager::GameManager(std::vector<Colony> colonies)
{
	nullColony = Colony(sf::Color::Black);
	nullColony.attack = 0;
	nullColony.defense = 0;
	for (Colony c : colonies)
		this->colonies.push_back(c);

	cells = new Cell*[constants::SQUARESIZE];
	for (int i = 0; i < constants::SQUARESIZE; i++)
	{
		cells[i] = new Cell[constants::SQUARESIZE];
	}

	//now all the cells exist, lets set em up.
	for (int i = 0; i < constants::SQUARESIZE; i++)
		for (int j = 0; j < constants::SQUARESIZE; j++)
	{
			cells[i][j].initialize(i, j, &nullColony);
	}
}


GameManager::~GameManager()
{
}
