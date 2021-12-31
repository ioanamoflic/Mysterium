#include "CharacterWindow.h"

CharacterWindow::CharacterWindow(sf::RenderWindow& m_window, const std::string& title)
	: Window(m_window, title)
{
	for (int index = 0; index < NUMBER_OF_PLAYERS; ++index)
		m_charactersPressed.push_back(false);
}

CharacterWindow::CharacterWindow()
{
}

void CharacterWindow::SetRedPlayer(uint16_t& order, sf::Sprite& redPlayerSprite, sf::Texture& redPlayerTexture, const std::string& redPlayerPath)
{
	redPlayerTexture.loadFromFile(redPlayerPath);
	PlaceIconButton(order, redPlayerTexture, redPlayerSprite, m_windowSize, DEFAULT_SCALE);
}

void CharacterWindow::SetPurplePlayer(uint16_t& order, sf::Sprite& purplePlayerSprite, sf::Texture& purplePlayerTexture, const std::string& purplePlayerPath)
{
	purplePlayerTexture.loadFromFile(purplePlayerPath);
	PlaceIconButton(order, purplePlayerTexture, purplePlayerSprite, m_windowSize, DEFAULT_SCALE);
}

void CharacterWindow::SetGhostPlayer(uint16_t& order, sf::Sprite& ghostPlayerSprite, sf::Texture& ghostPlayerTexture, const std::string& ghostPlayerPath)
{
	ghostPlayerTexture.loadFromFile(ghostPlayerPath);
	PlaceIconButton(order, ghostPlayerTexture, ghostPlayerSprite, m_windowSize, DEFAULT_SCALE);
}

void CharacterWindow::SetBluePlayer(uint16_t& order, sf::Sprite& bluePlayerSprite, sf::Texture& bluePlayerTexture, const std::string& bluePlayerPath)
{
	bluePlayerTexture.loadFromFile(bluePlayerPath);
	PlaceIconButton(order, bluePlayerTexture, bluePlayerSprite, m_windowSize, DEFAULT_SCALE);
}

void CharacterWindow::SetYellowPlayer(uint16_t& order, sf::Sprite& yellowPlayerSprite, sf::Texture& yellowPlayerTexture, const std::string& yellowPlayerPath)
{
	yellowPlayerTexture.loadFromFile(yellowPlayerPath);
	PlaceIconButton(order, yellowPlayerTexture, yellowPlayerSprite, m_windowSize, DEFAULT_SCALE);

}

void CharacterWindow::Display(sf::RenderWindow& m_window, bool pressed)
{
	sf::Texture backgroundTexture, titleTexture, ghostTexture, redPlayerTexture, purplePlayerTexture, bluePlayerTexture, yellowPlayerTexture;
	sf::Sprite backgroundSprite, titleSprite, ghostSprite, redPlayerSprite, purplePlayerSprite, bluePlayerSprite, yellowPlayerSprite;

	uint16_t orderOfCharacters = 0;
	SetBackground(backgroundSprite, backgroundTexture, "GUI/1mainThings/characterBackground.jpg");
	SetTitle(titleSprite, titleTexture, "GUI/10titles/chooseCharacter.png");
	
	SetRedPlayer(++orderOfCharacters, redPlayerSprite, redPlayerTexture, "GUI/7playerIcon/playerRed.png");
	SetPurplePlayer(++orderOfCharacters, purplePlayerSprite, purplePlayerTexture, "GUI/7playerIcon/playerPurple.png");
	SetGhostPlayer(++orderOfCharacters, ghostSprite, ghostTexture, "GUI/7playerIcon/ghostPlayer.jpg");
	SetBluePlayer(++orderOfCharacters, bluePlayerSprite, bluePlayerTexture, "GUI/7playerIcon/playerBlue.png");
	SetYellowPlayer(++orderOfCharacters, yellowPlayerSprite, yellowPlayerTexture, "GUI/7playerIcon/playerYellow.png");
	
	if (pressed) 
	{
		if (!m_charactersPressed.at(0))
			m_charactersPressed.at(0) = MakeClickable(bluePlayerSprite, sf::Mouse::getPosition(m_window));

		if (!m_charactersPressed.at(1))
			m_charactersPressed.at(1) = MakeClickable(purplePlayerSprite, sf::Mouse::getPosition(m_window));

		if (!m_charactersPressed.at(2))
			m_charactersPressed.at(2) = MakeClickable(redPlayerSprite, sf::Mouse::getPosition(m_window));

		if (!m_charactersPressed.at(3))
			m_charactersPressed.at(3) = MakeClickable(yellowPlayerSprite, sf::Mouse::getPosition(m_window));

		if (!m_charactersPressed.at(4))
			m_charactersPressed.at(4) = MakeClickable(ghostSprite, sf::Mouse::getPosition(m_window));
	}

	MakeClickable(bluePlayerSprite, sf::Mouse::getPosition(m_window));
	MakeClickable(purplePlayerSprite, sf::Mouse::getPosition(m_window));
	MakeClickable(redPlayerSprite, sf::Mouse::getPosition(m_window));
	MakeClickable(yellowPlayerSprite, sf::Mouse::getPosition(m_window));
	MakeClickable(ghostSprite, sf::Mouse::getPosition(m_window));

	m_window.draw(backgroundSprite);
	m_window.draw(titleSprite);
	m_window.draw(bluePlayerSprite);
	m_window.draw(yellowPlayerSprite);
	m_window.draw(redPlayerSprite);
	m_window.draw(purplePlayerSprite);
	m_window.draw(ghostSprite);
}

void CharacterWindow::PlaceIconButton(uint16_t& index, sf::Texture& texture, sf::Sprite& sprite, sf::Vector2u& windowSize, const float& defaultScale)
{
	sprite.setScale(defaultScale / 2.0F, defaultScale / 2.0F);
	sprite.setTexture(texture);

	float spriteX = sprite.getGlobalBounds().width,
		spriteY = sprite.getGlobalBounds().height;

	sprite.setPosition(index * windowSize.x / 6.0F - spriteX / 2.0F, windowSize.y / 2.0F - spriteY / 2.0F);
}

bool CharacterWindow::CheckAllPressed() const noexcept
{
	if (std::find(m_charactersPressed.begin(), m_charactersPressed.end(), false) == m_charactersPressed.end())
		return true;
	return false;
}
