#include "GhostWindow.h"

GhostWindow::GhostWindow(sf::RenderWindow& m_window, const std::string& title)
	: Window(m_window, title), m_isArrowPressed{ false }
{
	Initialize();
}

GhostWindow::GhostWindow()
{
}


void GhostWindow::Initialize()
{
	m_allGhostCards = Ghost::assignCardsForPlayers();

	std::string characterPath = "GUI/2charactCards/character01.png",
		locationPath = "GUI/3locationCards/location01.png",
		objectPath = "GUI/4objectCards/object01.png";

	const std::string backgroundPath = "GUI/1mainThings/ghostBackgroundBlue.jpg";

	std::unique_ptr<sf::Sprite> suspectSprite, locationSprite, objectSprite;
	std::unique_ptr<sf::Texture> suspectTexture, locationTexture, objectTexture;

	backgroundSprite = std::make_unique<sf::Sprite>();
	backgroundTexture = std::make_unique<sf::Texture>();

	SetBackground(*backgroundSprite, *backgroundTexture, backgroundPath);

	for (uint16_t indexColumn = 1; indexColumn < NUMBER_OF_PLAYERS; ++indexColumn)
	{
		suspectSprite = std::make_unique<sf::Sprite>();
		locationSprite = std::make_unique<sf::Sprite>();
		objectSprite = std::make_unique<sf::Sprite>();

		suspectTexture = std::make_unique<sf::Texture>();
		locationTexture = std::make_unique<sf::Texture>();
		objectTexture = std::make_unique<sf::Texture>();

		const auto& [ch, loc, obj] = m_allGhostCards[indexColumn - 1];
		uint16_t indexRow = 0;

		characterPath[27] = '0' + (ch % TOTAL_CARDS_NUMBER / 10);
		characterPath[28] = '0' + (ch % TOTAL_CARDS_NUMBER % 10);
		suspectTexture->loadFromFile(characterPath);
		suspectSprite->setTexture(*suspectTexture);
		PlaceSuspectButton(++indexRow, indexColumn, suspectSprite);
		m_characters.emplace_back(std::move(suspectSprite), std::move(suspectTexture));

		locationPath[27] = '0' + (loc % TOTAL_CARDS_NUMBER / 10);
		locationPath[28] = '0' + (loc % TOTAL_CARDS_NUMBER % 10);
		locationTexture->loadFromFile(locationPath);
		locationSprite->setTexture(*locationTexture);
		PlaceSuspectButton(++indexRow, indexColumn, locationSprite);
		m_locations.emplace_back(std::move(locationSprite), std::move(locationTexture));

		objectPath[23] = '0' + (obj % TOTAL_CARDS_NUMBER / 10);
		objectPath[24] = '0' + (obj % TOTAL_CARDS_NUMBER % 10);
		objectTexture->loadFromFile(objectPath);
		objectSprite->setTexture(*objectTexture);
		PlaceSuspectButton(++indexRow, indexColumn, objectSprite);
		m_objects.emplace_back(std::move(objectSprite), std::move(objectTexture));
	}
}

bool GhostWindow::GetIsArrowPressed() const noexcept
{
	return m_isArrowPressed;
}

void GhostWindow::SetIsArrowPressed(bool isArrowPressed) noexcept
{
	m_isArrowPressed = isArrowPressed;
}

void GhostWindow::Display(sf::RenderWindow& m_window)
{
	const std::string titlePath = "GUI/10titles/ghostBoard.png",
				arrowPath = "GUI/1mainThings/arrow.png";

	sf::Texture titleTexture, arrowTexture;
	sf::Sprite titleSprite, arrowSprite;

	SetArrowButton(arrowSprite, arrowTexture, arrowPath, RIGHT_SIDE);
	SetTitle(titleSprite, titleTexture, titlePath);

	m_isArrowPressed = MakeClickable(arrowSprite, sf::Mouse::getPosition(m_window));

	m_window.draw(*backgroundSprite);
	m_window.draw(titleSprite);
	m_window.draw(arrowSprite);

	for (auto& character : m_characters)
	{
		m_window.draw(*character.first);
	}

	for (auto& location : m_locations)
	{
		m_window.draw(*location.first);
	}

	for (auto& object : m_objects)
	{
		m_window.draw(*object.first);
	}
}

void GhostWindow::PlaceSuspectButton(uint16_t& indexRow, uint16_t& indexColumn, std::unique_ptr<sf::Sprite>& sprite)
{
	sprite->setScale(DEFAULT_SCALE / 2.7F, DEFAULT_SCALE / 2.7F);

	float spriteX = sprite->getGlobalBounds().width,
		spriteY = sprite->getGlobalBounds().height;

	if (spriteX > spriteY)
		sprite->setPosition(indexColumn * m_windowSize.x / 5.0F - spriteX / 2.0F, indexRow * 0.97 * m_windowSize.y / 4.0F - spriteY / 2.0F);
	else
		sprite->setPosition(indexColumn * m_windowSize.x / 5.0F - spriteX / 2.0F, indexRow * 1.03 * m_windowSize.y / 4.0F - spriteY / 2.0F);
}
