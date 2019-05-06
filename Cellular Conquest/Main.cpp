#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GameManager.h"
#include "Cell.h"
#include "Constants.h"
#include <random>
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
	//initialColonies.at(1).attack+=3;
	//initialColonies.at(1).defense += 3;
	initialColonies.push_back(Colony(sf::Color::Green));
	//initialColonies.at(2).attack += 2;
	//initialColonies.at(2).defense += 2;
	initialColonies.push_back(Colony(sf::Color::Yellow));
	//initialColonies.at(3).attack += 1;
	//initialColonies.at(3).defense += 1;
	GameManager gameManager(initialColonies);
	//place the first cells 
	
	srand(time(0));
		int x = std::rand()%constants::SQUARESIZE;
		int y = std::rand() % constants::SQUARESIZE;
		std::cout << x << " " << y << std::endl;
		sf::Time t = sf::seconds(1);
		sf::sleep(t);
	gameManager.cells[x][y].joinColony(&gameManager.colonies.at(0));
	gameManager.cells[x][y].unlock();
	
	//srand(time(0));
	int a = std::rand() % constants::SQUARESIZE;
	int b = std::rand() % constants::SQUARESIZE;
	std::cout << a << " " << b << std::endl;
	 t = sf::seconds(1);
	sf::sleep(t);
	 gameManager.cells[a][b].joinColony(&gameManager.colonies.at(1));
	 gameManager.cells[a][b].unlock();
	 
	// srand(time(0));
	 int c = std::rand() % constants::SQUARESIZE;
	 int d = std::rand() % constants::SQUARESIZE;
	 std::cout << c << " " << d << std::endl;
	  t = sf::seconds(1);
	 sf::sleep(t);
	 gameManager.cells[c][d].joinColony(&gameManager.colonies.at(2));
	 gameManager.cells[c][d].unlock();

	// srand(time(0));
	 int e = std::rand() % constants::SQUARESIZE;
	 int f = std::rand() % constants::SQUARESIZE;
	  t = sf::seconds(1);
	 sf::sleep(t);
	 std::cout << e << " " << f << std::endl;
	 gameManager.cells[e][f].joinColony(&gameManager.colonies.at(3));
	 gameManager.cells[e][f].unlock();
	
	std::vector<Cell*> lockedBuffer;
	int convertedThisTurn = 0;
	
	while (window.isOpen())// GAME START
	{
		gameManager.nullColony.attack = 0;
		gameManager.nullColony.defense = 0;

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

		for (int i=0; i < constants::SQUARESIZE; i++)
			for (int j=0; j < constants::SQUARESIZE; j++)
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

					if (left >= 0)
						leftAvailable = true;

					if (up >= 0)
						upAvailable = true;

					if (down < constants::SQUARESIZE)
						downAvailable = true;

					if (upAvailable &&gameManager.cells[i][up].myColony != gameManager.cells[i][j].myColony&&gameManager.cells[i][up].locked == false)//if can go up, go up
					{
						gameManager.cells[i][j].attackCell(&gameManager.cells[i][up]);
						lockedBuffer.push_back(&gameManager.cells[i][up]);
						convertedThisTurn++;
					}

					if (downAvailable &&gameManager.cells[i][down].myColony != gameManager.cells[i][j].myColony &&gameManager.cells[i][down].locked == false)//if can go down
					{
						gameManager.cells[i][j].attackCell(&gameManager.cells[i][down]);
						lockedBuffer.push_back(&gameManager.cells[i][down]);
						convertedThisTurn++;

					}

					if (leftAvailable &&gameManager.cells[left][j].myColony != gameManager.cells[i][j].myColony &&gameManager.cells[left][j].locked == false)//if can go left
					{
						gameManager.cells[i][j].attackCell(&gameManager.cells[left][j]);
						lockedBuffer.push_back(&gameManager.cells[left][j]);
						convertedThisTurn++;

					}

					if (rightAvailable &&gameManager.cells[right][j].myColony != gameManager.cells[i][j].myColony &&gameManager.cells[right][j].locked == false)//if can go right
					{
						gameManager.cells[i][j].attackCell(&gameManager.cells[right][j]);
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
				 t = sf::seconds(10);

				sf::sleep(t);
				window.close();

			}
		}
		
	}
	return 0;
}