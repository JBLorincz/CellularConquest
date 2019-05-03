#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GameManager.h"
#include "Cell.h"
#include "Constants.h"
#define up j-1
#define down j+1
#define left i-1
#define right i+1
int main()
{
	//initialize the window
	sf::RenderWindow window(sf::VideoMode(constants::SQUARESIZE,constants::SQUARESIZE),"Cellular Conquest", sf::Style::Titlebar|sf::Style::Close);
	//window.setFramerateLimit(1);
	//initialize the game manager to start the game
	std::vector<Colony> initialColonies;
	initialColonies.push_back(Colony(sf::Color::Red));
	initialColonies.push_back(Colony(sf::Color::Blue));

	GameManager gameManager(initialColonies);

	//place the first cells 
	
	gameManager.cells[0][0].joinColony(&gameManager.colonies.at(0));
	gameManager.cells[constants::SQUARESIZE-1][constants::SQUARESIZE - 1].joinColony(&gameManager.colonies.at(1));
	
	
	gameManager.cells[0][0].unlock();
	gameManager.cells[constants::SQUARESIZE - 1][constants::SQUARESIZE - 1].unlock();
	
	std::vector<Cell*> lockedBuffer;
	int convertedThisTurn = 0;
	
	
	while (window.isOpen())// GAME START
	{

		while (lockedBuffer.size() > 0)
		{
			lockedBuffer.at(0)->locked = false;
			lockedBuffer.erase(lockedBuffer.begin());
		}
		//lockedBuffer.clear();
		//std::cout << convertedThisTurn << std::endl;
		convertedThisTurn = 0;


		//1. handle the logic
		sf::Event newEvent;
		while (window.pollEvent(newEvent))
		{
			if (newEvent.type == sf::Event::Closed)
				window.close();
		}
		//2. draw stuff
		window.clear(sf::Color::Black);

		//check adjacent cells if they can be captured
		for (int i = 0; i < constants::SQUARESIZE; i++)
			for (int j = 0; j < constants::SQUARESIZE; j++)
			{
				if (gameManager.cells[i][j].myColony != &gameManager.nullColony &&gameManager.cells[i][j].locked == false)
				{
					window.draw(gameManager.cells[i][j].pixel);

					bool rightAvailable = 0;
					bool leftAvailable = 0;
					bool upAvailable = 0;
					bool downAvailable = 0;

					if (right < constants::SQUARESIZE)
						rightAvailable = true;

					if (left > 0)
						leftAvailable = true;

					if (up > 0)
						upAvailable = true;

					if (down < constants::SQUARESIZE)
						downAvailable = true;

					if (upAvailable &&gameManager.cells[i][up].myColony != gameManager.cells[i][j].myColony&&gameManager.cells[i][up].locked == false)//if can go up, go up
					{
						gameManager.cells[i][up].joinColony(gameManager.cells[i][j].myColony);
						gameManager.cells[i][up].locked = true;
						lockedBuffer.push_back(&gameManager.cells[i][up]);
						convertedThisTurn++;
					}

					if (downAvailable &&gameManager.cells[i][down].myColony != gameManager.cells[i][j].myColony &&gameManager.cells[i][down].locked == false)//if can go down
					{
						gameManager.cells[i][down].joinColony(gameManager.cells[i][j].myColony);
						gameManager.cells[i][down].locked = true;
						lockedBuffer.push_back(&gameManager.cells[i][down]);
						convertedThisTurn++;

					}

					if (leftAvailable &&gameManager.cells[left][j].myColony != gameManager.cells[i][j].myColony &&gameManager.cells[left][j].locked == false)//if can go left
					{
						gameManager.cells[left][j].joinColony(gameManager.cells[i][j].myColony);
					
						gameManager.cells[left][j].locked = true;
						lockedBuffer.push_back(&gameManager.cells[left][j]);
						convertedThisTurn++;

					}

					if (rightAvailable &&gameManager.cells[right][j].myColony != gameManager.cells[i][j].myColony &&gameManager.cells[right][j].locked == false)//if can go right
					{
						gameManager.cells[right][j].joinColony(gameManager.cells[i][j].myColony);
						gameManager.cells[right][j].locked = true;
						lockedBuffer.push_back(&gameManager.cells[right][j]);
						convertedThisTurn++;
					}
				}

			}

		//3. end the frame
		window.display();


		//4. check for victory
		for (int i = 0; i < gameManager.colonies.size(); i++)
		{
			std::cout << "Colony " << i << " has this number of cells: "<< gameManager.colonies.at(i).numberOfCells<<std::endl;
			if (gameManager.colonies.at(i).numberOfCells >= constants::SQUARESIZE*constants::SQUARESIZE)
			{
				std::cout << "Colony " << i << " won!" << std::endl << "Closing program in 10 seconds.";
				sf::Time t = sf::seconds(10);

				sf::sleep(t);
				window.close();

			}
		}
	}
	return 0;
}