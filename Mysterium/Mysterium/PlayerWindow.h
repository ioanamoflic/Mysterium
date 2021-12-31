#pragma once
#include "Window.h"
#include <memory>

class PlayerWindow : public Window
{
public:
	using SpriteTexturePressID = std::tuple<std::unique_ptr<sf::Sprite>, std::unique_ptr<sf::Texture>, bool, uint16_t>;
	using SpriteTexture = std::pair<std::unique_ptr<sf::Sprite>, std::unique_ptr<sf::Texture>>;

	PlayerWindow(sf::RenderWindow&, const std::string&);
	PlayerWindow();

	void Display(sf::RenderWindow&, bool);

	bool GetIsArrowPressed() const noexcept;
	void SetIsArrowPressed(bool) noexcept;

	void GiveVisionCards(sf::RenderWindow&, bool);

	bool ChooseCharacterCards(sf::RenderWindow&, bool);
	bool ChooseLocationCards(sf::RenderWindow&, bool);
	bool ChooseWeaponCards(sf::RenderWindow&, bool);

private:
	inline static uint16_t m_activePlayer;
	
	bool m_isArrowPressed;
	uint16_t m_round;
	uint16_t m_visionChange;
	uint16_t m_crowPressedCounter;

	std::unique_ptr<sf::Sprite> m_backgroundSprite, m_clockSprite, m_crowMarkerSprite, m_moveToNextPlayerSprite;
	std::unique_ptr<sf::Texture> m_backgroundTexture, m_clockTexture, m_crowMarkerTexture, m_moveToNextPlayerTexture;

	std::vector<sf::Sprite> m_playerIcons;
	std::vector<Player> m_players;
	std::vector<SpriteTexture> m_icons, m_titles;
	std::vector<SpriteTexturePressID> m_characters, m_locations, m_objects;
	std::array<bool, NUMBER_OF_PSYCHICS> m_charactersGuessed;

	std::vector<std::tuple<uint16_t, uint16_t, uint16_t>> m_ghostCards;
	std::vector<std::tuple<std::unique_ptr<sf::Sprite>, std::unique_ptr<sf::Texture>, bool>> m_visions;

	void Initialize(sf::RenderWindow&);

	void PlaceIcon(std::unique_ptr<sf::Texture>&, std::unique_ptr<sf::Sprite>&, const std::string&, const uint16_t&);
	void PlaceCard(sf::RenderWindow&, uint16_t, uint16_t, std::unique_ptr<sf::Texture>&, std::unique_ptr<sf::Sprite>&);
	void PlaceVisionCards(uint16_t&, uint16_t&, std::unique_ptr<sf::Texture>&, std::unique_ptr<sf::Sprite>&);
	
	void AddPlayerIcons();
	void AddTitles();
	void AddCharacters(sf::RenderWindow&);
	void AddLocations(sf::RenderWindow&);
	void AddWeapons(sf::RenderWindow&);
	void AddVisionCards();
	void AddClock();
	void AddCrowMarker();
	void AddNextPlayerButton();
	
	void WhichIsHovered(sf::RenderWindow&, const sf::Vector2i&, std::vector<SpriteTexturePressID>&);
	bool CardsGuess(uint16_t&, uint16_t&, uint16_t&);
	void GameEnd(sf::RenderWindow&, bool);
};

