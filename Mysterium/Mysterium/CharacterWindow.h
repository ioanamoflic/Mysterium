#pragma once
#include "Window.h"

class CharacterWindow :public Window
{
public:
	CharacterWindow(sf::RenderWindow& , const std::string&);
	CharacterWindow();

	void Display(sf::RenderWindow& m_window, bool);
	bool CheckAllPressed() const noexcept;

private:
	void PlaceIconButton(uint16_t&, sf::Texture&, sf::Sprite&, sf::Vector2u&, const float&);

	void SetRedPlayer(uint16_t&, sf::Sprite&, sf::Texture&, const std::string&);
	void SetPurplePlayer(uint16_t&, sf::Sprite&, sf::Texture&, const std::string&);
	void SetGhostPlayer(uint16_t&, sf::Sprite&, sf::Texture&, const std::string&);
	void SetBluePlayer(uint16_t&, sf::Sprite&, sf::Texture&, const std::string&);
	void SetYellowPlayer(uint16_t&, sf::Sprite&, sf::Texture&, const std::string&);

	std::vector<bool> m_charactersPressed;
};
