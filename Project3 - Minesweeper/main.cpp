#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include <algorithm>
#include <sstream>
#include "Random.h"
#include "Tile.h"
#include "Board.h"
using namespace std;

vector<int> readData(const string& filename)
{
	ifstream file(filename);
	vector<int> configData;
	if (file.is_open())
	{
		string line = "";
		while (getline(file, line))
		{
			string tempNumber = "";
			unsigned int data = 0;
			
			stringstream inputString(line);
			getline(inputString, tempNumber); // temp string for data
			data = stoi(tempNumber);

			configData.push_back(data);
		}
	}
	return configData;
}


int main()
{
	vector<int> config = readData("boards/config.cfg");
	unsigned int COLUMNS = 0;
	unsigned int ROWS = 0;
	unsigned int MINES = 0;

	for (unsigned int i = 0; i < config.size(); i++)
	{
		cout << config.at(i) << endl;
	}

	COLUMNS = config[0];
	ROWS = config[1];
	MINES = config[2];

	Board gameBoard(COLUMNS, ROWS);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Minesweeper");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
		gameBoard.drawBoard(window);
        window.display();
    }

    // Clear out any textures before the program ends
    TextureManager::Clear();
    return 0;
}


// sf::Sprite button(TextureManager::GetTexture("button"));