/*#include <iostream>


 int main()
{
	while (true)
		std::cout << "Hello World!";
}*/
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GameManager.h"
#include "Cell.h"
#define up j-1
#define down j+1
#define left i-1
#define right i+1
int main()
{
	 const int SQUARESIZE = 500;
	//initialize the window
	sf::RenderWindow window(sf::VideoMode(SQUARESIZE,SQUARESIZE),"Cellular Conquest", sf::Style::Titlebar|sf::Style::Close);

	//initialize the game manager to start the game
	std::vector<Colony> initialColonies;
	initialColonies.push_back(Colony(sf::Color::Red));
	initialColonies.push_back(Colony(sf::Color::Blue));
	GameManager gameManager(initialColonies);

	//place the first cells 
	gameManager.cells[0][0].joinColony(&gameManager.colonies.at(0));
	gameManager.cells[499][499].joinColony(&gameManager.colonies.at(1));
	//std::vector<Cell*> cellBuffer;
	int convertedThisTurn = 0;
	while (window.isOpen())
	{
		for (int i = 0; i < 500; i++)
			for (int j = 0; j < 500; j++)
				gameManager.cells[i][j].locked = false;
		std::cout << convertedThisTurn<<std::endl;
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
		for (int i = 0; i < 500; i++)
			for (int j = 0; j < 500; j++)
			{
				if (gameManager.cells[i][j].myColony != &gameManager.nullColony &&gameManager.cells[i][j].locked==false)
				{
					window.draw(gameManager.cells[i][j].pixel);

					bool rightAvailable = 0;
					bool leftAvailable = 0;
					bool upAvailable = 0;
					bool downAvailable = 0;

					if (right < 500)
						rightAvailable = true;

					if (left > 0)
						leftAvailable = true;

					if (up > 0)
						upAvailable = true;

					if (down < 500)
						downAvailable = true;

					if (upAvailable &&gameManager.cells[i][up].myColony != gameManager.cells[i][j].myColony&&gameManager.cells[i][up].locked == false)//if can go up, go up
					{
						//cellBuffer.push_back(new Cell(i, up, gameManager.cells[i][j].myColony));
						gameManager.cells[i][up].joinColony(gameManager.cells[i][j].myColony);
						gameManager.cells[i][up].locked = true;
						convertedThisTurn++;
					}
					if (downAvailable &&gameManager.cells[i][down].myColony != gameManager.cells[i][j].myColony &&gameManager.cells[i][down].locked == false)//if can go down
					{
						//cellBuffer.push_back(Cell(i, down, gameManager.cells[i][j].myColony));
						gameManager.cells[i][down].joinColony(gameManager.cells[i][j].myColony);
						gameManager.cells[i][down].locked = true;
						convertedThisTurn++;

					}
					if (leftAvailable &&gameManager.cells[left][j].myColony != gameManager.cells[i][j].myColony &&gameManager.cells[left][j].locked == false)//if can go left
					{
						//cellBuffer.push_back(Cell(left, j, gameManager.cells[i][j].myColony));
						gameManager.cells[left][j].joinColony(gameManager.cells[i][j].myColony);
						gameManager.cells[left][j].locked = true;
						convertedThisTurn++;

					}
					if (rightAvailable &&gameManager.cells[right][j].myColony != gameManager.cells[i][j].myColony &&gameManager.cells[right][j].locked == false)//if can go right
					{
						//cellBuffer.push_back(Cell(right, j, gameManager.cells[i][j].myColony));
						gameManager.cells[right][j].joinColony(gameManager.cells[i][j].myColony);
						gameManager.cells[right][j].locked = true;
						convertedThisTurn++;
					}
						//cellBuffer.push_back(Cell(i + 1, j, gameManager.cells[i][j].myColony));
				}

			}
			
		//3. end the frame
		window.display();
		//4. add new cells
		//for (Cell* c : cellBuffer)
		//{
			//gameManager.cells[c.xCoord][c.yCoord].joinColony(c.myColony);

		//}
	}
	return 0;
}