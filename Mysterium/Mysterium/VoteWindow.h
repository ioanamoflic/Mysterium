#pragma once
#include "Window.h"

class VoteWindow: public Window
{
public:

	VoteWindow(sf::RenderWindow&, const std::string&);
	VoteWindow() {};

	void Display(sf::RenderWindow&, bool);

	bool GetIsArrowPressed() const noexcept;
	void SetIsArrowPressed(bool) noexcept;

	void GiveVisionCards(sf::RenderWindow&, bool);
	void GetWinnerSet(sf::RenderWindow&, bool);

private:

	using SpriteTexture = std::pair<std::unique_ptr<sf::Sprite>, std::unique_ptr<sf::Texture>>;
	bool m_isArrowPressed;
	uint16_t m_winner;
	uint16_t voteCounter;

	std::vector<SpriteTexture> m_icons;
	std::vector<sf::Sprite> playerIcons;
	std::vector<uint16_t> m_guessed;
	std::vector<std::tuple<std::unique_ptr<sf::Sprite>, std::unique_ptr<sf::Texture>, bool>> m_visions;
	std::unique_ptr<sf::Sprite> m_backgroundSprite;
	std::unique_ptr<sf::Texture> m_backgroundTexture;

	void Initialize();

	void PlaceVisionCards(uint16_t&, uint16_t&, std::unique_ptr<sf::Texture>&, std::unique_ptr<sf::Sprite>&);
	void PlaceIcon(std::unique_ptr<sf::Texture>&, std::unique_ptr<sf::Sprite>&, const std::string&, const uint16_t&);
	void SetSubTitle(sf::Sprite&, sf::Texture&, const std::string&);
	void AddVisionCards();
	void AddPlayerIcons();
	bool WinChecker();
	void GameEnd(sf::RenderWindow&, bool);
};