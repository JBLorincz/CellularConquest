#include "GameManager.h"



GameManager::GameManager(std::vector<Colony> colonies)
{
	nullColony = Colony(sf::Color::Black);

	for (Colony c : colonies)
		this->colonies.push_back(c);

	cells = new Cell*[500];
	for (int i = 0; i < 500; i++)
	{
		cells[i] = new Cell[500];
	}

	//now all the cells exist, lets set em up.
	for (int i = 0; i < 500; i++)
		for (int j = 0; j < 500; j++)
	{
			cells[i][j].initialize(i, j, &nullColony);
	}
}


GameManager::~GameManager()
{
}
