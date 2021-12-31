#pragma once

#include ".\SFML\Graphics.hpp"
#include "SFML/Window.hpp"
#include "./SFML/Audio/Music.hpp"
#include "Board.h"

class Window
{
public:
	static const int DEFAULT_PIXEL_NUMBER = 1920 * 1080;
	static const uint16_t WIDTH = 1920, HEIGHT = 1080;

	static const bool LEFT_SIDE = 0, RIGHT_SIDE = 1;
	static const uint16_t NUMBER_OF_PLAYERS = 5, 
						NUMBER_OF_PSYCHICS = 4, 
						TOTAL_CARDS_NUMBER = 18, 
						TOTAL_VISION_CARDS_NUMBER = 84, 
						NUMBER_OF_GHOST_CARDS = 7,
						NUMBER_OF_VISION_CARDS = 7,
						NUMBER_OF_ROUNDS = 7;

	Window(sf::RenderWindow&, const std::string&);
	Window();

	void SetBackground(sf::Sprite&, sf::Texture&, const std::string&);
	void SetTitle(sf::Sprite&, sf::Texture&, const std::string&);
	void SetArrowButton(sf::Sprite&, sf::Texture&, const std::string&, bool);
	bool MakeClickable(sf::Sprite&, const sf::Vector2i&);
	bool MakeBiggerHover(sf::RenderWindow&, sf::Sprite&, const sf::Vector2i&);
	void SetLogo(sf::Sprite&, sf::Texture&, const std::string&);

	std::string m_windowTitle;
	sf::Sprite m_backgroundSprite;
	sf::Texture m_backgroundTexture;
	sf::Vector2u m_windowSize;

	float DEFAULT_SCALE, DEFAULT_SCALE_X, DEFAULT_SCALE_Y;

	float SetDefaultScale(sf::Vector2u& windowSize);
};