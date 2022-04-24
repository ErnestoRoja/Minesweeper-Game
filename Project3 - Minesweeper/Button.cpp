#include "Button.h"

// Loads the happy face sprite and assigns it to the position of the face button.
sf::Sprite Button::drawSmileyFaceButton(const sf::Vector2f& position)
{
	sf::Sprite smileyFaceButton(TextureManager::GetTexture("face_happy"));
	smileyFaceButton.setPosition(position);
	allButtons["smileyFaceButton"] = smileyFaceButton;

	return smileyFaceButton;
}

// Loads the sad face sprite and assigns it to the position of face button.
sf::Sprite Button::drawSadFaceButton(const sf::Vector2f& position)
{
	sf::Sprite sadFaceButton(TextureManager::GetTexture("face_lose"));
	sadFaceButton.setPosition(position);
	allButtons["sadFaceButton"] = sadFaceButton;

	return sadFaceButton;
}

// Loads the winner face sprite and assigns it to the position of face button.
sf::Sprite Button::drawWinnerFaceButton(const sf::Vector2f& position)
{
	sf::Sprite winnerFaceButton(TextureManager::GetTexture("face_win"));
	winnerFaceButton.setPosition(position);
	allButtons["winnerFaceButton"] = winnerFaceButton;

	return winnerFaceButton;
}

// Loads the test1 sprite and assigns it to the test1 button.
sf::Sprite Button::drawTest1Button(const sf::Vector2f& position)
{
	sf::Sprite test1Button(TextureManager::GetTexture("test_1"));
	test1Button.setPosition(position);
	allButtons["test1Button"] = test1Button;

	return test1Button;
}

// Loads the test2 sprite and assigns it to the test2 button.
sf::Sprite Button::drawTest2Button(const sf::Vector2f& position)
{
	sf::Sprite test2Button(TextureManager::GetTexture("test_2"));
	test2Button.setPosition(position);
	allButtons["test2Button"] = test2Button;

	return test2Button;
}

// Loads the test3 sprite and assigns it to the test3 button.
sf::Sprite Button::drawTest3Button(const sf::Vector2f& position)
{
	sf::Sprite test3Button(TextureManager::GetTexture("test_3"));
	test3Button.setPosition(position);
	allButtons["test3Button"] = test3Button;

	return test3Button;
}

// Loads the debug sprite and assigns it to the debug button.
sf::Sprite Button::drawDebugButton(const sf::Vector2f& position)
{
	sf::Sprite debugButton(TextureManager::GetTexture("debug"));
	debugButton.setPosition(position);
	allButtons["debugButton"] = debugButton;

	return debugButton;
}

// Loads the ones digits of the digits sprite and assigns its position. 
sf::Sprite Button::drawOnesDigits(const sf::Vector2f& position, int ones)
{
	sf::Sprite onesDigits(TextureManager::GetTexture("digits"));
	onesDigits.setTextureRect(sf::IntRect(21 * ones, 0, 21, 32));
	onesDigits.setPosition(position); 
	allDigits["onesDigits"] = onesDigits;
	
	return onesDigits;
}

// Loads the tens digits of the digits sprite and assigns its position. 
sf::Sprite Button::drawTensDigits(const sf::Vector2f& position, int tens)
{
	sf::Sprite tensDigits(TextureManager::GetTexture("digits"));
	tensDigits.setTextureRect(sf::IntRect(21 * tens, 0, 21, 32));
	tensDigits.setPosition(position);
	allDigits["tensDigits"] = tensDigits;

	return tensDigits;
}

// Loads the hundreds digits of the digits sprite and assigns its position. 
sf::Sprite Button::drawHundredsDigits(const sf::Vector2f& position, int hundreds)
{
	sf::Sprite hundredsDigits(TextureManager::GetTexture("digits"));
	hundredsDigits.setTextureRect(sf::IntRect(21 * hundreds, 0, 21, 32));
	hundredsDigits.setPosition(position);
	allDigits["hundredsDigits"] = hundredsDigits;

	return hundredsDigits;
}

// Loads the negative of the digits sprite and assigns its position. 
sf::Sprite Button::drawNegativeDigits(const sf::Vector2f& position)
{
	sf::Sprite negativeDigits(TextureManager::GetTexture("digits"));
	negativeDigits.setTextureRect(sf::IntRect(21 * 10, 0, 21, 32));
	negativeDigits.setPosition(position);
	allDigits["negativeDigits"] = negativeDigits;

	return negativeDigits;
}