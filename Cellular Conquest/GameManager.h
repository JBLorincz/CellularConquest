#pragma once
#include <vector>
#include "Colony.h"
#include "Cell.h"
class GameManager
{
public:
	GameManager(std::vector<Colony> colonies);
	std::vector<Colony> colonies;
	Colony nullColony;//the colony for uncontested cells

	Cell** cells;

	~GameManager();
};

