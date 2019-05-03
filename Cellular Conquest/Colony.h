#pragma once
#include <SFML/Graphics.hpp>
class Colony
{
public:
	int attack;
	int defense;
	int numberOfCells;
	sf::Color teamColor;
	Colony();
	Colony(sf::Color teamColor);

};

