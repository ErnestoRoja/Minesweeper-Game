#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include <algorithm>
#include <sstream>
#include "Random.h"
#include "TextureManager.h"
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
			getline(inputString, tempNumber); // temp string columns
			data = stoi(tempNumber);

			configData.push_back(data);
		}
	}
	return configData;
}


int main()
{
	vector<int> config = readData("boards/config.cfg");

	for (unsigned int i = 0; i < config.size(); i++)
	{
		cout << config.at(i) << endl;
	}

    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    // Clear out any textures before the program ends
    TextureManager::Clear();
    return 0;
}


// sf::Sprite button(TextureManager::GetTexture("button"));