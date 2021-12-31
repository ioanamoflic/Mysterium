#pragma once
#include "Window.h"
#include "Board.h"

class GhostWindow : public Window
{
public:
	using SpriteTexture = std::pair<std::unique_ptr<sf::Sprite>, std::unique_ptr<sf::Texture>>;

	GhostWindow(sf::RenderWindow&, const std::string&);
	GhostWindow();

	void Display(sf::RenderWindow&);

	bool GetIsArrowPressed() const noexcept;
	void SetIsArrowPressed(bool) noexcept;

	inline static std::vector<std::tuple<uint16_t, uint16_t, uint16_t>> GetAllGhostCards() noexcept
	{
		return m_allGhostCards;
	}

private:
	Cards m_cards;
	
	std::unique_ptr<sf::Sprite> backgroundSprite;
	std::unique_ptr<sf::Texture> backgroundTexture;

	bool m_isArrowPressed;

	inline static std::vector<Ghost::psychicAssociatedCards> m_allGhostCards;
	std::vector<SpriteTexture> m_characters;
	std::vector<SpriteTexture> m_locations;
	std::vector<SpriteTexture> m_objects;

	void Initialize();
	void PlaceSuspectButton(uint16_t&, uint16_t&, std::unique_ptr<sf::Sprite>&);
};

