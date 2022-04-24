#pragma once
#include "Tile.h"

class Button
{
public:
	unordered_map<string, sf::Sprite> allButtons;
	unordered_map<string, sf::Sprite> allDigits;

	sf::Sprite drawSmileyFaceButton(const sf::Vector2f& position);
	sf::Sprite drawSadFaceButton(const sf::Vector2f& position);
	sf::Sprite drawWinnerFaceButton(const sf::Vector2f& position);

	sf::Sprite drawTest1Button(const sf::Vector2f& position);
	sf::Sprite drawTest2Button(const sf::Vector2f& position);
	sf::Sprite drawTest3Button(const sf::Vector2f& position);
	sf::Sprite drawDebugButton(const sf::Vector2f& position);
	sf::Sprite drawOnesDigits(const sf::Vector2f& position, int ones);
	sf::Sprite drawTensDigits(const sf::Vector2f& position, int tens);
	sf::Sprite drawHundredsDigits(const sf::Vector2f& position, int hundreds);
	sf::Sprite drawNegativeDigits(const sf::Vector2f& position);
};