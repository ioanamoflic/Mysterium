#include "PlayerWindow.h"
#include "Game.h"
#include <chrono>
#include <thread>
#include <fstream>
#include "../Logger/Logging.h"

std::ofstream output("logMysterium.log", std::ios::app);
Logging logMysterium(output);

using namespace std::chrono_literals;

PlayerWindow::PlayerWindow(sf::RenderWindow& m_window, const std::string& title)
	: Window(m_window, title), m_isArrowPressed{ false }
{
	Initialize(m_window);
}

PlayerWindow::PlayerWindow()
{
}


void PlayerWindow::Initialize(sf::RenderWindow& window)
{
	m_ghostCards = GhostWindow::GetAllGhostCards();

	m_players.emplace_back(1, 1, Player::Color::RED);
	m_players.emplace_back(2, 2, Player::Color::YELLOW);
	m_players.emplace_back(3, 3, Player::Color::PURPLE);
	m_players.emplace_back(4, 4, Player::Color::BLUE);

	m_round = 1;
	m_visionChange = 1;
	m_crowPressedCounter = 0;
	m_activePlayer = 0;
	m_charactersGuessed = { false };

	const std::string backgroundPath = "GUI/1mainThings/playerBackground.jpg";

	m_backgroundSprite = std::make_unique<sf::Sprite>();
	m_backgroundTexture = std::make_unique<sf::Texture>();
	SetBackground(*m_backgroundSprite, *m_backgroundTexture, backgroundPath);

	AddCharacters(window);
	AddLocations(window);
	AddWeapons(window);
	AddVisionCards();
	AddPlayerIcons();
	AddTitles();
	AddClock();
	AddCrowMarker();
	AddNextPlayerButton();
}


void PlayerWindow::Display(sf::RenderWindow& m_window, bool pressed)
{
	const std::string titlePath = "GUI/10titles/playerBoard.png",
				arrowPath = "GUI/1mainThings/arrowRev.png";

	sf::Sprite titleSprite, arrowSprite;
	sf::Texture titleTexture, arrowTexture;

	SetArrowButton(arrowSprite, arrowTexture, arrowPath, LEFT_SIDE);
	SetTitle(titleSprite, titleTexture, titlePath);

	m_isArrowPressed = MakeClickable(arrowSprite, sf::Mouse::getPosition(m_window));

	m_window.draw(*m_backgroundSprite);
	m_window.draw(titleSprite);
	m_window.draw(arrowSprite);
	m_window.draw(*m_clockSprite);
	m_window.draw(*m_moveToNextPlayerSprite);

	if (MakeClickable(*m_crowMarkerSprite, sf::Mouse::getPosition(m_window)) && pressed && m_crowPressedCounter < Ghost::NUMBER_OF_CROW_MARKERS)
	{
		logMysterium.Log("Crow marker clicked - vision cards changed", Logging::Level::INFO);
		++m_crowPressedCounter;
		++m_visionChange;
		AddVisionCards();

		std::this_thread::sleep_for(0.1s);
	}

	m_window.draw(*m_crowMarkerSprite);

	for (auto& title : m_titles)
	{
		m_window.draw(*title.first);
	}

	for (auto& icon : m_icons)
	{
		m_window.draw(*icon.first);
	}

	switch (m_activePlayer)
	{
	case 0:
		logMysterium.Log("Red player's turn", Logging::Level::INFO);
		m_icons.at(0).first->setColor(sf::Color::Red);
		m_icons.at(1).first->setColor(sf::Color::White);
		m_icons.at(2).first->setColor(sf::Color::White);
		m_icons.at(3).first->setColor(sf::Color::White);
		break;
	case 1:
		logMysterium.Log("Yellow player's turn", Logging::Level::INFO);
		m_icons.at(0).first->setColor(sf::Color::White);
		m_icons.at(1).first->setColor(sf::Color::Yellow);
		m_icons.at(2).first->setColor(sf::Color::White);
		m_icons.at(3).first->setColor(sf::Color::White);
		break;
	case 2:
		logMysterium.Log("Purple player's turn", Logging::Level::INFO);
		m_icons.at(0).first->setColor(sf::Color::White);
		m_icons.at(1).first->setColor(sf::Color::White);
		m_icons.at(2).first->setColor(sf::Color(128, 0, 128));
		m_icons.at(3).first->setColor(sf::Color::White);
		break;
	case 3:
		logMysterium.Log("Blue player's turn", Logging::Level::INFO);
		m_icons.at(0).first->setColor(sf::Color::White);
		m_icons.at(1).first->setColor(sf::Color::White);
		m_icons.at(2).first->setColor(sf::Color::White);
		m_icons.at(3).first->setColor(sf::Color::Blue);
		break;
	default:
		break;
	}

	for (auto& character : m_characters)
	{
		m_window.draw(*std::get<0>(character));
	}
	WhichIsHovered(m_window, sf::Mouse::getPosition(m_window), m_characters);

	for (auto& location : m_locations)
	{
		m_window.draw(*std::get<0>(location));
	}
	WhichIsHovered(m_window, sf::Mouse::getPosition(m_window), m_locations);

	for (auto& object : m_objects)
	{
		m_window.draw(*std::get<0>(object));
	}
	int index = 0;
	for (auto& vision : m_visions)
	{
		m_window.draw(*std::get<0>(vision));
	}
	
	if (m_round > NUMBER_OF_ROUNDS)
	{
		GameEnd(m_window, false);
	}
}

bool PlayerWindow::GetIsArrowPressed() const noexcept
{
	return m_isArrowPressed;
}

void PlayerWindow::SetIsArrowPressed(bool isArrowPressed) noexcept
{
	m_isArrowPressed = isArrowPressed;
}

void PlayerWindow::PlaceIcon(std::unique_ptr<sf::Texture>& iconTexture, std::unique_ptr<sf::Sprite>& iconSprite, const std::string& iconPath, const uint16_t& lastPos)
{
	iconTexture->loadFromFile(iconPath);
	iconSprite->setTexture(*iconTexture);

	float scale = DEFAULT_SCALE / 4.7F;
	iconSprite->setScale(scale, scale);

	float iconX = iconSprite->getGlobalBounds().width,
		iconY = iconSprite->getGlobalBounds().height;
	iconSprite->setPosition((lastPos - iconX / 2.0F) * DEFAULT_SCALE_X, (1000 - iconY / 2.0F) * DEFAULT_SCALE_Y);
}

void PlayerWindow::PlaceCard(sf::RenderWindow& m_window, uint16_t index, uint16_t index2, std::unique_ptr<sf::Texture>& texture, std::unique_ptr<sf::Sprite>& sprite)
{
	sprite->setTexture(*texture);

	if (sprite->getGlobalBounds().width > sprite->getGlobalBounds().height)
		sprite->setScale(DEFAULT_SCALE / 4.6F, DEFAULT_SCALE / 4.1F);
	else
		sprite->setScale(DEFAULT_SCALE / 3.0F, DEFAULT_SCALE / 3.1F);

	float spriteX = sprite->getGlobalBounds().width,
		spriteY = sprite->getGlobalBounds().height;
	sprite->setPosition((index - spriteX / 2.0F) * DEFAULT_SCALE_X, (index2 - spriteY / 2.0F) * DEFAULT_SCALE_Y);
}

void PlayerWindow::PlaceVisionCards(uint16_t& indexRow, uint16_t& indexColumn, std::unique_ptr<sf::Texture>& cardTexture, std::unique_ptr<sf::Sprite>& cardSprite)
{
	cardSprite->setScale((DEFAULT_SCALE / 3.6F), DEFAULT_SCALE / 3.6F);
	cardSprite->setTexture(*cardTexture);

	float visionX = cardSprite->getGlobalBounds().width,
		visionY = cardSprite->getGlobalBounds().height;

	if (indexColumn % 2)
	{
		cardSprite->setPosition((1630 - visionX / 2.0F) * DEFAULT_SCALE_X, (indexRow * 252 - 80) * DEFAULT_SCALE_Y);
		--indexColumn;
		++indexRow;
	}
	else
	{
		cardSprite->setPosition((1820 - visionX / 2.0F) * DEFAULT_SCALE_X, (indexRow * 252 - 210) * DEFAULT_SCALE_Y);
		++indexColumn;
	}
}

void PlayerWindow::AddPlayerIcons()
{
	/* RED ICON */
	std::unique_ptr<sf::Sprite> iconRedSprite = std::make_unique<sf::Sprite>();
	std::unique_ptr<sf::Texture> iconRedTexture = std::make_unique<sf::Texture>();

	PlaceIcon(iconRedTexture, iconRedSprite, "GUI/7playerIcon/iconRed.png", 400);
	m_playerIcons.push_back(*iconRedSprite);
	m_icons.emplace_back(std::move(iconRedSprite), std::move(iconRedTexture));

	/* YELLOW ICON */
	std::unique_ptr<sf::Sprite> iconYellowSprite = std::make_unique<sf::Sprite>();
	std::unique_ptr<sf::Texture> iconYellowTexture = std::make_unique<sf::Texture>();

	PlaceIcon(iconYellowTexture, iconYellowSprite, "GUI/7playerIcon/iconYellow.png", 600);
	m_playerIcons.push_back(*iconYellowSprite);
	m_icons.emplace_back(std::move(iconYellowSprite), std::move(iconYellowTexture));

	/* PURPLE ICON */
	std::unique_ptr<sf::Sprite> iconPurpleSprite = std::make_unique<sf::Sprite>();
	std::unique_ptr<sf::Texture> iconPurpleTexture = std::make_unique<sf::Texture>();

	PlaceIcon(iconPurpleTexture, iconPurpleSprite, "GUI/7playerIcon/iconPurple.png", 800);
	m_playerIcons.push_back(*iconPurpleSprite);
	m_icons.emplace_back(std::move(iconPurpleSprite), std::move(iconPurpleTexture));

	/* BLUE ICON */
	std::unique_ptr<sf::Sprite> iconBlueSprite = std::make_unique<sf::Sprite>();
	std::unique_ptr<sf::Texture> iconBlueTexture = std::make_unique<sf::Texture>();

	PlaceIcon(iconBlueTexture, iconBlueSprite, "GUI/7playerIcon/iconBlue.png", 1000);
	m_playerIcons.push_back(*iconBlueSprite);
	m_icons.emplace_back(std::move(iconBlueSprite), std::move(iconBlueTexture));
}

void PlayerWindow::AddTitles()
{
	float scale = DEFAULT_SCALE / 3.0F;

	/* SUSPECTS TITLE */
	std::unique_ptr<sf::Sprite> suspectsTitleSprite = std::make_unique<sf::Sprite>();
	std::unique_ptr<sf::Texture> suspectsTitleTexture = std::make_unique<sf::Texture>();

	suspectsTitleTexture->loadFromFile("GUI/10titles/suspectsTitle.png");
	suspectsTitleSprite->setTexture(*suspectsTitleTexture);
	suspectsTitleSprite->setScale(scale, scale);

	float suspectsTitleSpriteX = suspectsTitleSprite->getGlobalBounds().width,
		suspectsTitleSpriteY = suspectsTitleSprite->getGlobalBounds().height;

	suspectsTitleSprite->setPosition((405 - suspectsTitleSpriteX / 2.0F) * DEFAULT_SCALE_X, (740 - suspectsTitleSpriteY / 2.0F) * DEFAULT_SCALE_Y);
	m_titles.emplace_back(std::move(suspectsTitleSprite), std::move(suspectsTitleTexture));

	/* LOCATIONS TITLE */
	std::unique_ptr<sf::Sprite> locationsTitleSprite = std::make_unique<sf::Sprite>();
	std::unique_ptr<sf::Texture> locationsTitleTexture = std::make_unique<sf::Texture>();

	locationsTitleTexture->loadFromFile("GUI/10titles/locationsTitle.png");
	locationsTitleSprite->setTexture(*locationsTitleTexture);
	locationsTitleSprite->setScale(scale, scale);

	float locationsTitleSpriteX = locationsTitleSprite->getGlobalBounds().width,
		locationsTitleSpriteY = locationsTitleSprite->getGlobalBounds().height;

	locationsTitleSprite->setPosition((405 - locationsTitleSpriteX / 2.0F) * DEFAULT_SCALE_X, (500 - locationsTitleSpriteY / 2.0F) * DEFAULT_SCALE_Y);
	m_titles.emplace_back(std::move(locationsTitleSprite), std::move(locationsTitleTexture));

	/* WEAPONS TITLE */
	std::unique_ptr<sf::Sprite> weaponsTitleSprite = std::make_unique<sf::Sprite>();
	std::unique_ptr<sf::Texture> weaponsTitleTexture = std::make_unique<sf::Texture>();

	weaponsTitleTexture->loadFromFile("GUI/10titles/weaponsTitle.png");
	weaponsTitleSprite->setTexture(*weaponsTitleTexture);
	weaponsTitleSprite->setScale(scale, scale);

	float weaponsTitleSpriteX = weaponsTitleSprite->getGlobalBounds().width,
		weaponsTitleSpriteY = weaponsTitleSprite->getGlobalBounds().height;

	weaponsTitleSprite->setPosition((405 - weaponsTitleSpriteX / 2.0F) * DEFAULT_SCALE_X, (130 - weaponsTitleSpriteY / 2.0F) * DEFAULT_SCALE_Y);
	m_titles.emplace_back(std::move(weaponsTitleSprite), std::move(weaponsTitleTexture));
}

void PlayerWindow::AddCharacters(sf::RenderWindow& m_window)
{
	std::unique_ptr<sf::Sprite> characterSprite;
	std::unique_ptr<sf::Texture> characterTexture;

	std::string path = "GUI/2charactCards/character01.png";
	uint16_t index2 = 860;

	for (uint16_t index = 0; index < Game::m_board.m_characterCardsInGame.size(); ++index)
	{
		characterSprite = std::make_unique<sf::Sprite>();
		characterTexture = std::make_unique<sf::Texture>();

		uint16_t ch = Game::m_board.m_characterCardsInGame.at(index);
		path[27] = '0' + (ch % TOTAL_CARDS_NUMBER / 10);
		path[28] = '0' + (ch % TOTAL_CARDS_NUMBER % 10);

		characterTexture->loadFromFile(path);
		PlaceCard(m_window, (index + 1) * 200 + 5, index2, characterTexture, characterSprite);
		m_characters.emplace_back(std::move(characterSprite), std::move(characterTexture), false, ch);
	}
}

void PlayerWindow::AddLocations(sf::RenderWindow& m_window)
{
	std::unique_ptr<sf::Sprite> locationSprite;
	std::unique_ptr<sf::Texture> locationTexture;

	std::string path = "GUI/3locationCards/location01.png";
	uint16_t index2 = 600;

	for (uint16_t index = 0; index < Game::m_board.m_locationCardsInGame.size(); ++index)
	{
		locationSprite = std::make_unique<sf::Sprite>();
		locationTexture = std::make_unique<sf::Texture>();

		uint16_t ch = Game::m_board.m_locationCardsInGame.at(index);
		path[27] = '0' + (ch % TOTAL_CARDS_NUMBER / 10);
		path[28] = '0' + (ch % TOTAL_CARDS_NUMBER % 10);

		locationTexture->loadFromFile(path);
		PlaceCard(m_window, (index + 1) * 200 + 5, index2, locationTexture, locationSprite);
		m_locations.emplace_back(std::move(locationSprite), std::move(locationTexture), false, ch);
	}
}

void PlayerWindow::AddWeapons(sf::RenderWindow& m_window)
{
	std::unique_ptr<sf::Sprite> objectSprite;
	std::unique_ptr<sf::Texture> objectTexture;

	std::string path = "GUI/4objectCards/object01.png";
	uint16_t index2 = 320;

	for (uint16_t index = 0; index < Game::m_board.m_objectCardsInGame.size(); ++index)
	{
		objectSprite = std::make_unique<sf::Sprite>();
		objectTexture = std::make_unique<sf::Texture>();

		uint16_t ch = Game::m_board.m_objectCardsInGame.at(index);
		path[23] = '0' + (ch % TOTAL_CARDS_NUMBER / 10);
		path[24] = '0' + (ch % TOTAL_CARDS_NUMBER % 10);

		objectTexture->loadFromFile(path);
		PlaceCard(m_window, (index + 1) * 200 + 5, index2, objectTexture, objectSprite);
		m_objects.emplace_back(std::move(objectSprite), std::move(objectTexture), false, ch);
	}
}

void PlayerWindow::AddVisionCards()
{
	std::unique_ptr<sf::Sprite> visionSprite;
	std::unique_ptr<sf::Texture> visionTexture;

	std::string visionCardPath = "GUI/5visionCards/vision01.png";
	uint16_t indexRow = 1, indexColumn = 0;

	for (uint16_t index = (m_visionChange - 1) * 7; index < (m_visionChange - 1) * 7 + 7; ++index)
	{
		visionSprite = std::make_unique<sf::Sprite>();
		visionTexture = std::make_unique<sf::Texture>();

		uint16_t numberOfVisionCard = Game::m_board.m_visionCards.at(index);
		visionCardPath[23] = '0' + (numberOfVisionCard % TOTAL_VISION_CARDS_NUMBER / 10);
		visionCardPath[24] = '0' + (numberOfVisionCard % TOTAL_VISION_CARDS_NUMBER % 10);

		visionTexture->loadFromFile(visionCardPath);
		PlaceVisionCards(indexRow, indexColumn, visionTexture, visionSprite);
		m_visions.emplace_back(std::move(visionSprite), std::move(visionTexture), false);
	}
}

void PlayerWindow::AddClock()
{
	std::unique_ptr<sf::Sprite> clockSprite = std::make_unique<sf::Sprite>();
	std::unique_ptr<sf::Texture> clockTexture = std::make_unique<sf::Texture>();
	std::string path = "GUI/8clock/round1.png";

	path[16] = '0' + m_round;
	clockTexture->loadFromFile(path);
	clockSprite->setTexture(*clockTexture);

	float scale = DEFAULT_SCALE / 3.1F;
	clockSprite->setScale(scale, scale);

	float clockX = clockSprite->getGlobalBounds().width,
		clockY = clockSprite->getGlobalBounds().height;
	clockSprite->setPosition((1630 - clockX / 2.0F) * DEFAULT_SCALE_X, (90 - clockY / 2.0F) * pow(DEFAULT_SCALE_Y, 6));

	m_clockSprite = std::move(clockSprite);
	m_clockTexture = std::move(clockTexture);
}

void PlayerWindow::AddCrowMarker()
{
	std::unique_ptr<sf::Sprite> crowMarkerSprite = std::make_unique<sf::Sprite>();
	std::unique_ptr<sf::Texture> crowMarkerTexture = std::make_unique<sf::Texture>();
	const std::string path = "GUI/1mainThings/crowMarker.png";

	crowMarkerTexture->loadFromFile(path);
	crowMarkerSprite->setTexture(*crowMarkerTexture);

	float scale = DEFAULT_SCALE / 3.15;
	crowMarkerSprite->setScale(scale, scale);

	float crowX = crowMarkerSprite->getGlobalBounds().width,
		crowY = crowMarkerSprite->getGlobalBounds().height;
	crowMarkerSprite->setPosition((1520 - crowX / 2.0F) * DEFAULT_SCALE_X, (1060 - crowY / 2.0F) * DEFAULT_SCALE_Y);

	m_crowMarkerSprite = std::move(crowMarkerSprite);
	m_crowMarkerTexture = std::move(crowMarkerTexture);
}

void PlayerWindow::AddNextPlayerButton()
{
	std::unique_ptr<sf::Sprite> moveToNextPlayerSprite = std::make_unique<sf::Sprite>();
	std::unique_ptr<sf::Texture> moveToNextPlayerTexture = std::make_unique<sf::Texture>();
	const std::string path = "GUI/1mainThings/moveToNextPlayerButton.png";

	moveToNextPlayerTexture->loadFromFile(path);
	moveToNextPlayerSprite->setTexture(*moveToNextPlayerTexture);

	float scale = DEFAULT_SCALE;
	moveToNextPlayerSprite->setScale(scale, scale);

	float nextX = moveToNextPlayerSprite->getGlobalBounds().width,
		nextY = moveToNextPlayerSprite->getGlobalBounds().height;
	moveToNextPlayerSprite->setPosition((1240 - nextX / 2.0F) * DEFAULT_SCALE_X, (1000 - nextY / 2.0F) * DEFAULT_SCALE_Y);

	m_moveToNextPlayerSprite = std::move(moveToNextPlayerSprite);
	m_moveToNextPlayerTexture = std::move(moveToNextPlayerTexture);
}

void PlayerWindow::WhichIsHovered(sf::RenderWindow& window, const sf::Vector2i& mousePos, std::vector<SpriteTexturePressID>& buttons)
{
	for (auto& button : buttons)
	{
		if (MakeBiggerHover(window, *std::get<0>(button), mousePos))
			return;
	}
}

bool PlayerWindow::CardsGuess(uint16_t& id, uint16_t& position, uint16_t& player)
{
	if (position == 0 && std::get<0>(m_ghostCards.at(player - 1)) == id)
		return true;

	if (position == 1 && std::get<1>(m_ghostCards.at(player - 1)) == id)
		return true;

	if (position == 2 && std::get<2>(m_ghostCards.at(player - 1)) == id)
		return true;

	return false;
}

void PlayerWindow::GameEnd(sf::RenderWindow& window, bool win)
{
	window.clear();

	const std::string backgroundPath = "GUI/1mainThings/endBackground.png";
	std::unique_ptr<sf::Sprite> backgroundSprite = std::make_unique<sf::Sprite>();
	std::unique_ptr<sf::Texture> backgroundTexture = std::make_unique<sf::Texture>();
	SetBackground(*backgroundSprite, *backgroundTexture, backgroundPath);
	window.draw(*backgroundSprite);

	std::unique_ptr<sf::Sprite> gameOverSprite = std::make_unique<sf::Sprite>(), 
									logoSprite = std::make_unique<sf::Sprite>();
	std::unique_ptr<sf::Texture> gameOverTexture = std::make_unique<sf::Texture>(), 
									logoTexture = std::make_unique<sf::Texture>();
	
	const std::string logoPath = "GUI/1mainThings/logo.png";
	std::string path;
	
	SetLogo(*logoSprite, *logoTexture, logoPath);

	float scale1 = float(m_windowSize.x) / 4500, 
			scale2 = DEFAULT_SCALE;

	logoSprite->setScale(scale1, scale1);
	float logoX = logoSprite->getGlobalBounds().width,
		logoY = logoSprite->getGlobalBounds().height;
	logoSprite->setPosition(m_windowSize.x / 2.0F - logoX / 2.0F, (900 - logoY / 2.0F) * DEFAULT_SCALE_Y);

	if (win == false)
	{
		path = "GUI/1mainThings/gameOverButton.png";
		SetLogo(*gameOverSprite, *gameOverTexture, path);
		gameOverSprite->setScale(scale2, scale2);
		float gameOverX = gameOverSprite->getGlobalBounds().width,
			gameOverY = gameOverSprite->getGlobalBounds().height;
		gameOverSprite->setPosition(m_windowSize.x / 2.0F - gameOverX / 2.0F, m_windowSize.y / 2.0F + 100 - gameOverY / 2.0F);
		logMysterium.Log("Game ended with no winners", Logging::Level::INFO);
	}
	else
	{
		path = "GUI/1mainThings/congratsButton.png";
		SetLogo(*gameOverSprite, *gameOverTexture, path);
		gameOverSprite->setScale(scale2, scale2);
		float gameOverX = gameOverSprite->getGlobalBounds().width,
			gameOverY = gameOverSprite->getGlobalBounds().height;
		gameOverSprite->setPosition(m_windowSize.x / 2.0F - gameOverX / 2.0F, m_windowSize.y / 2.0F + 100 - gameOverY / 2.0F);
		logMysterium.Log("Game ended with winners", Logging::Level::INFO);
	}

	window.draw(*logoSprite);
	window.draw(*gameOverSprite);
}

bool PlayerWindow::ChooseCharacterCards(sf::RenderWindow& m_window, bool pressed)
{
	uint16_t onBoardPosition = 0;
	static uint16_t allGuessed = 0;
	static uint16_t clickCounter = 0;

	for (auto& character : m_characters)
	{
		auto& [spriteCharacter, textureCharacter, pressOnCharacter, ID] = character;

		if (!pressOnCharacter && pressed)
		{
			pressOnCharacter = MakeClickable(*spriteCharacter, sf::Mouse::getPosition(m_window));
		}

		if (pressOnCharacter && spriteCharacter->getColor() != sf::Color::Red
			&& spriteCharacter->getColor() != sf::Color::Yellow
			&& spriteCharacter->getColor() != sf::Color::Color(128, 0, 128)
			&& spriteCharacter->getColor() != sf::Color::Blue)
		{
			uint16_t numberOfPlayer = m_players[m_activePlayer].GetCrystalBowl().first;

			switch (numberOfPlayer)
			{
			case 1:
				spriteCharacter->setColor(sf::Color::Red);
				++clickCounter;
				if (CardsGuess(ID, onBoardPosition, numberOfPlayer))
				{
					++allGuessed;
					logMysterium.Log("Character card guessed by red player", Logging::Level::INFO);
					m_charactersGuessed[numberOfPlayer - 1] = true;
				}
				else
					logMysterium.Log("Character card guessed by red player", Logging::Level::ERROR);
				break;
			case 2:
				spriteCharacter->setColor(sf::Color::Yellow);
				++clickCounter;
				if (CardsGuess(ID, onBoardPosition, numberOfPlayer))
				{
					++allGuessed;
					logMysterium.Log("Character card guessed by yellow player", Logging::Level::INFO);
					m_charactersGuessed[numberOfPlayer - 1] = true;
				}
				else
					logMysterium.Log("Character card guessed by yellow player", Logging::Level::ERROR);
				break;
			case 3:
				spriteCharacter->setColor(sf::Color::Color(128, 0, 128));
				++clickCounter;
				if (CardsGuess(ID, onBoardPosition, numberOfPlayer))
				{
					++allGuessed;
					logMysterium.Log("Character card guessed by purple player", Logging::Level::INFO);
					m_charactersGuessed[numberOfPlayer - 1] = true;
				}
				else
					logMysterium.Log("Character card guessed by purple player", Logging::Level::ERROR);
				break;
			case 4:
				spriteCharacter->setColor(sf::Color::Blue);
				std::this_thread::sleep_for(1s);
				++clickCounter;
				if (CardsGuess(ID, onBoardPosition, numberOfPlayer))
				{
					++allGuessed;
					logMysterium.Log("Character card guessed by blue player", Logging::Level::INFO);
					m_charactersGuessed[numberOfPlayer - 1] = true;
				}
				else
					logMysterium.Log("Character card guessed by blue player", Logging::Level::ERROR);
				break;
			default:
				break;
			}

			++m_activePlayer;
		}

		if (clickCounter >= NUMBER_OF_PSYCHICS && allGuessed != NUMBER_OF_PSYCHICS)
		{
			m_activePlayer = 0;
			clickCounter = 0;

			++m_round;
			AddClock();
		}

		if (allGuessed == NUMBER_OF_PSYCHICS)
		{
			for (auto& character1 : m_characters)
			{
				auto& [spriteCharacter1, textureCharacter1, pressOnCharacter1, ID1] = character1;
				spriteCharacter1->setColor(sf::Color::White);
			}

			allGuessed = 0;
			m_activePlayer = 0;

			++m_round;
			++m_visionChange;

			AddClock();
			AddVisionCards();
			return true;
		}
	}
	return false;
}

bool PlayerWindow::ChooseLocationCards(sf::RenderWindow& m_window, bool pressed)
{
	static uint16_t allGuessed = 0;
	static uint16_t clickCounter = 0;
	uint16_t onBoardPosition = 1;

	for (auto& location : m_locations)
	{
		auto& [spriteLocation, textureLocation, pressOnLocation, ID] = location;

		if (!pressOnLocation && pressed)
		{
			pressOnLocation = MakeClickable(*spriteLocation, sf::Mouse::getPosition(m_window));
		}

		if (pressOnLocation && spriteLocation->getColor() != sf::Color::Red
			&& spriteLocation->getColor() != sf::Color::Yellow
			&& spriteLocation->getColor() != sf::Color::Color(128, 0, 128)
			&& spriteLocation->getColor() != sf::Color::Blue)
		{
			uint16_t numberOfPlayer = m_players[m_activePlayer].GetCrystalBowl().first;

			switch (numberOfPlayer)
			{
			case 1:
				spriteLocation->setColor(sf::Color::Red);
				++clickCounter;
				if (CardsGuess(ID, onBoardPosition, numberOfPlayer))
				{
					logMysterium.Log("Location card guessed by red player", Logging::Level::INFO);
					++allGuessed;
				}
				else
					logMysterium.Log("Location card guessed by red player", Logging::Level::ERROR);
				break;
			case 2:
				spriteLocation->setColor(sf::Color::Yellow);
				++clickCounter;
				if (CardsGuess(ID, onBoardPosition, numberOfPlayer))
				{
					logMysterium.Log("Location card guessed by yellow player", Logging::Level::INFO);
					++allGuessed;
				}
				else
					logMysterium.Log("Location card guessed by yellow player", Logging::Level::ERROR);
				break;
			case 3:
				spriteLocation->setColor(sf::Color::Color(128, 0, 128));
				++clickCounter;
				if (CardsGuess(ID, onBoardPosition, numberOfPlayer))
				{
					logMysterium.Log("Location card guessed by purple player", Logging::Level::INFO);
					++allGuessed;
				}
				else
					logMysterium.Log("Location card guessed by purple player", Logging::Level::ERROR);
				break;
			case 4:
				spriteLocation->setColor(sf::Color::Blue);
				std::this_thread::sleep_for(1s);
				++clickCounter;
				if (CardsGuess(ID, onBoardPosition, numberOfPlayer))
				{
					logMysterium.Log("Location card guessed by blue player", Logging::Level::INFO);
					++allGuessed;
				}
				else
					logMysterium.Log("Location card guessed by blue player", Logging::Level::ERROR);
				break;
			default:
				break;
			}

			++m_activePlayer;
		}
		if (clickCounter >= NUMBER_OF_PSYCHICS && allGuessed != NUMBER_OF_PSYCHICS)
		{
			m_activePlayer = 0;
			clickCounter = 0;

			++m_round;
			AddClock();

		}
		if (allGuessed == NUMBER_OF_PSYCHICS)
		{
			for (auto& location1 : m_locations)
			{
				auto& [spriteLocation1, textureLocation1, pressOnLocation1, ID1] = location1;
				spriteLocation1->setColor(sf::Color::White);
			}
			allGuessed = 0;
			m_activePlayer = 0;

			++m_round;
			++m_visionChange;

			AddClock();
			AddVisionCards();
			return true;
		}
	}
	return false;
}

bool PlayerWindow::ChooseWeaponCards(sf::RenderWindow& m_window, bool pressed)
{
	static uint16_t allGuessed = 0;
	static uint16_t clickCounter = 0;
	uint16_t onBoardPosition = 2;

	for (auto& object : m_objects)
	{
		auto& [spriteObject, textureObject, pressOnObject, ID] = object;

		if (!pressOnObject && pressed)
		{
			pressOnObject = MakeClickable(*spriteObject, sf::Mouse::getPosition(m_window));
		}

		if (pressOnObject && spriteObject->getColor() != sf::Color::Red
			&& spriteObject->getColor() != sf::Color::Yellow
			&& spriteObject->getColor() != sf::Color::Color(128, 0, 128)
			&& spriteObject->getColor() != sf::Color::Blue)
		{
			uint16_t numberOfPlayer = m_players[m_activePlayer].GetCrystalBowl().first;

			switch (numberOfPlayer)
			{
			case 1:
				spriteObject->setColor(sf::Color::Red);
				++clickCounter;
				if (CardsGuess(ID, onBoardPosition, numberOfPlayer))
				{
					logMysterium.Log("Weapon card guessed by red player", Logging::Level::INFO);
					++allGuessed;
				}
				else
					logMysterium.Log("Weapon card guessed by red player", Logging::Level::ERROR);
				break;
			case 2:
				spriteObject->setColor(sf::Color::Yellow);
				++clickCounter;
				if (CardsGuess(ID, onBoardPosition, numberOfPlayer))
				{
					logMysterium.Log("Weapon card guessed by yellow player", Logging::Level::INFO);
					++allGuessed;
				}
				else
					logMysterium.Log("Weapon card not guessed by yellow player", Logging::Level::ERROR);
				break;
			case 3:
				spriteObject->setColor(sf::Color::Color(128, 0, 128));
				++clickCounter;
				if (CardsGuess(ID, onBoardPosition, numberOfPlayer))
				{
					logMysterium.Log("Weapon card guessed by purple player", Logging::Level::INFO);
					++allGuessed;
				}
				else
					logMysterium.Log("Weapon card not guessed by purple player", Logging::Level::ERROR);
				break;
			case 4:
				spriteObject->setColor(sf::Color::Blue);
				std::this_thread::sleep_for(1s);
				++clickCounter;
				if (CardsGuess(ID, onBoardPosition, numberOfPlayer))
				{
					logMysterium.Log("Weapon card guessed by blue player", Logging::Level::INFO);
					++allGuessed;
				}
				else
					logMysterium.Log("Weapon card not guessed by blue player", Logging::Level::ERROR);
				break;
			default:
				break;
			}

			++m_activePlayer;
		}
		if (clickCounter >= NUMBER_OF_PSYCHICS && allGuessed != NUMBER_OF_PSYCHICS)
		{
			m_activePlayer = 0;
			clickCounter = 0;

			++m_round;
			AddClock();

		}
		if (allGuessed == NUMBER_OF_PSYCHICS)
		{
			for (auto& object1 : m_objects)
			{
				auto& [spriteObject1, textureObject1, pressOnObject1, ID1] = object1;
				spriteObject1->setColor(sf::Color::White);
			}
			allGuessed = 0;
			m_activePlayer = 0;

			++m_round;
			++m_visionChange;

			AddClock();
			AddVisionCards();
			return true;
		}
	}
	return false;
}

void PlayerWindow::GiveVisionCards(sf::RenderWindow& m_window, bool pressed)
{
	for (auto& visionCard : m_visions)
	{
		auto& [spriteVision, textureVision, pressVision] = visionCard;

		if (!pressVision && pressed)
		{
			pressVision = MakeClickable(*spriteVision, sf::Mouse::getPosition(m_window));
		}

		if (pressVision && spriteVision->getColor() != sf::Color::Red
			&& spriteVision->getColor() != sf::Color::Yellow
			&& spriteVision->getColor() != sf::Color::Color(128, 0, 128)
			&& spriteVision->getColor() != sf::Color::Blue)
		{
			switch (m_players[m_activePlayer].GetCrystalBowl().first)
			{
			case 1:
				logMysterium.Log("Vision card given to red player", Logging::Level::INFO);
				spriteVision->setColor(sf::Color::Red);
				break;
			case 2:
				logMysterium.Log("Vision card given to yellow player", Logging::Level::INFO);
				spriteVision->setColor(sf::Color::Yellow);
				break;
			case 3:
				logMysterium.Log("Vision card given to purple player", Logging::Level::INFO);
				spriteVision->setColor(sf::Color::Color(128, 0, 128));
				break;
			case 4:
				logMysterium.Log("Vision card given to blue player", Logging::Level::INFO);
				spriteVision->setColor(sf::Color::Blue);
				break;
			default:
				break;
			}
		}

		if (m_activePlayer == NUMBER_OF_PSYCHICS)
		{
			m_activePlayer = 0;
			break;
		}

		if (MakeClickable(*m_moveToNextPlayerSprite, sf::Mouse::getPosition(m_window)) && pressed)
		{
			std::this_thread::sleep_for(0.5s);
			++m_activePlayer;
			break;
		}
	}
}