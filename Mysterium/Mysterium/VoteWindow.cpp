#include "VoteWindow.h"
#include "Game.h"
#include <chrono>
#include <thread>

using namespace std::chrono_literals;

VoteWindow::VoteWindow(sf::RenderWindow& window, const std::string& title)
	:Window(window, title)
{
	Initialize();
}

void VoteWindow::Initialize()
{
	const std::string backgroundPath = "GUI/1mainThings/playerBackground.jpg";
	m_isArrowPressed = false;
	m_winner = -1;

	m_backgroundSprite = std::make_unique<sf::Sprite>();
	m_backgroundTexture = std::make_unique<sf::Texture>();

	SetBackground(*m_backgroundSprite, *m_backgroundTexture, backgroundPath);
	AddVisionCards();
	AddPlayerIcons();
}

void VoteWindow::Display(sf::RenderWindow& window, bool pressed)
{
	sf::Sprite titleSprite, arrowSprite, playerSubTitleSprite, ghostSubTitleSprite;
	sf::Texture titleTexture, arrowTexture, playerSubTitleTexture, ghostSubTitleTexture;

	const std::string titlePath = "GUI/10titles/votingBoardTitle.png", arrowPath = "GUI/1mainThings/arrowRev.png";
	const std::string playerTitlePath ="GUI/1mainThings/psychicVoteTitle.png", ghostTitlePath = "GUI/1mainThings/ghostVoteTitle.png";

	SetArrowButton(arrowSprite, arrowTexture, arrowPath, LEFT_SIDE);
	SetTitle(titleSprite, titleTexture, titlePath);

	m_isArrowPressed = MakeClickable(arrowSprite, sf::Mouse::getPosition(window));

	window.draw(*m_backgroundSprite);
	window.draw(titleSprite);
	window.draw(arrowSprite);

	if (m_winner == -1)
	{
		SetSubTitle(ghostSubTitleSprite, ghostSubTitleTexture, ghostTitlePath);
		window.draw(ghostSubTitleSprite);
	}
	else
	{
		SetSubTitle(playerSubTitleSprite, playerSubTitleTexture, playerTitlePath);
		window.draw(playerSubTitleSprite);
	}

	for (auto& vision : m_visions)
	{
		window.draw(*std::get<0>(vision));
	}

	for (auto& icon : m_icons)
	{
		window.draw(*icon.first);
	}

	GetWinnerSet(window, pressed);

	if (voteCounter > NUMBER_OF_PSYCHICS)
	{
		if (WinChecker())
			GameEnd(window, true);
		else
			GameEnd(window, false);
	}
}

bool VoteWindow::GetIsArrowPressed() const noexcept
{
	return m_isArrowPressed;
}

void VoteWindow::SetIsArrowPressed(bool isArrowPressed) noexcept
{
	m_isArrowPressed = isArrowPressed;
}

void VoteWindow::GiveVisionCards(sf::RenderWindow& window, bool pressed)
{
	static uint16_t counter = 0;

	for (auto& visionCard : m_visions)
	{
		auto& [spriteVision, textureVision, pressVision] = visionCard;

		if (!pressVision && pressed && counter < NUMBER_OF_PSYCHICS - 1 && spriteVision->getColor() != sf::Color::Green)
		{
			pressVision = MakeClickable(*spriteVision, sf::Mouse::getPosition(window));
			if (pressVision == true)
			{
				++counter;
				spriteVision->setColor(sf::Color::Green);
			}
		}
	}
}

void VoteWindow::AddVisionCards()
{
	std::unique_ptr<sf::Sprite> visionSprite;
	std::unique_ptr<sf::Texture> visionTexture;

	std::string visionCardPath = "GUI/5visionCards/vision01.png";
	uint16_t indexRow = 1, indexColumn = 0;

	for (uint16_t index = Game::m_board.m_visionCards.size() - 7; index < Game::m_board.m_visionCards.size(); ++index)
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

void VoteWindow::PlaceVisionCards(uint16_t& indexRow, uint16_t& indexColumn, std::unique_ptr<sf::Texture>& cardTexture, std::unique_ptr<sf::Sprite>& cardSprite)
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

void VoteWindow::AddPlayerIcons()
{
	/* RED ICON */
	std::unique_ptr<sf::Sprite> iconRedSprite = std::make_unique<sf::Sprite>();
	std::unique_ptr<sf::Texture> iconRedTexture = std::make_unique<sf::Texture>();
	m_guessed.push_back(0);

	PlaceIcon(iconRedTexture, iconRedSprite, "GUI/7playerIcon/iconRed.png", 200);
	playerIcons.push_back(*iconRedSprite);
	m_icons.emplace_back(std::move(iconRedSprite), std::move(iconRedTexture));

	/* YELLOW ICON */
	std::unique_ptr<sf::Sprite> iconYellowSprite = std::make_unique<sf::Sprite>();
	std::unique_ptr<sf::Texture> iconYellowTexture = std::make_unique<sf::Texture>();
	m_guessed.push_back(0);

	PlaceIcon(iconYellowTexture, iconYellowSprite, "GUI/7playerIcon/iconYellow.png", 600);
	playerIcons.push_back(*iconYellowSprite);
	m_icons.emplace_back(std::move(iconYellowSprite), std::move(iconYellowTexture));

	/* PURPLE ICON */
	std::unique_ptr<sf::Sprite> iconPurpleSprite = std::make_unique<sf::Sprite>();
	std::unique_ptr<sf::Texture> iconPurpleTexture = std::make_unique<sf::Texture>();
	m_guessed.push_back(0);

	PlaceIcon(iconPurpleTexture, iconPurpleSprite, "GUI/7playerIcon/iconPurple.png", 1000);
	playerIcons.push_back(*iconPurpleSprite);
	m_icons.emplace_back(std::move(iconPurpleSprite), std::move(iconPurpleTexture));

	/* BLUE ICON */
	std::unique_ptr<sf::Sprite> iconBlueSprite = std::make_unique<sf::Sprite>();
	std::unique_ptr<sf::Texture> iconBlueTexture = std::make_unique<sf::Texture>();
	m_guessed.push_back(0);

	PlaceIcon(iconBlueTexture, iconBlueSprite, "GUI/7playerIcon/iconBlue.png", 1400);
	playerIcons.push_back(*iconBlueSprite);
	m_icons.emplace_back(std::move(iconBlueSprite), std::move(iconBlueTexture));
}

void VoteWindow::GetWinnerSet(sf::RenderWindow& window, bool pressed)
{
	for (int index = 0; index < m_icons.size(); ++index)
	{
		if (pressed && MakeClickable(playerIcons[index], sf::Mouse::getPosition(window)))
		{
			std::this_thread::sleep_for(1s);
			++m_guessed[index];
			++voteCounter;

			if (voteCounter == 1)
				m_winner = index;
		}
	}
}

bool VoteWindow::WinChecker()
{
	auto maxVoted = std::max_element(m_guessed.begin(), m_guessed.end());

	for (uint16_t winnerIndex = 0; winnerIndex < m_guessed.size(); ++winnerIndex)
		if (m_guessed[winnerIndex] == *maxVoted)
		{
			if (winnerIndex == m_winner)
				return true;
		}
	return false;
}

void VoteWindow::PlaceIcon(std::unique_ptr<sf::Texture>& iconTexture, std::unique_ptr<sf::Sprite>& iconSprite, const std::string& iconPath, const uint16_t& lastPos)
{
	iconTexture->loadFromFile(iconPath);
	iconSprite->setTexture(*iconTexture);

	float scale = DEFAULT_SCALE / 1.5F;
	iconSprite->setScale(scale, scale);

	float iconX = iconSprite->getGlobalBounds().width,
		iconY = iconSprite->getGlobalBounds().height;
	iconSprite->setPosition((lastPos - iconX / 2.0F) * DEFAULT_SCALE_X, (600 - iconY / 2.0F) * DEFAULT_SCALE_Y);
}

void VoteWindow::GameEnd(sf::RenderWindow& window, bool win)
{
	window.clear();
	const std::string backgroundPath = "GUI/1mainThings/characterBackground.jpg";

	std::unique_ptr<sf::Sprite> backgroundSprite = std::make_unique<sf::Sprite>();
	std::unique_ptr<sf::Texture> backgroundTexture = std::make_unique<sf::Texture>();

	SetBackground(*backgroundSprite, *backgroundTexture, backgroundPath);
	window.draw(*backgroundSprite);

	std::unique_ptr<sf::Sprite> gameOverSprite = std::make_unique<sf::Sprite>(), 
								logoSprite = std::make_unique<sf::Sprite>();;
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
	logoSprite->setPosition(m_windowSize.x / 2.0F - logoX / 2.0F, (300 - logoY / 2.0F) * DEFAULT_SCALE_Y);

	if (!win)
	{
		path = "GUI/1mainThings/gameOverButton.png";
		SetLogo(*gameOverSprite, *gameOverTexture, path);
		gameOverSprite->setScale(scale2, scale2);
		float gameOverX = gameOverSprite->getGlobalBounds().width,
			gameOverY = gameOverSprite->getGlobalBounds().height;
		gameOverSprite->setPosition(m_windowSize.x / 2.0F - gameOverX / 2.0F, m_windowSize.y / 2.0F + 100 - gameOverY / 2.0F);
	}
	else
	{
		path = "GUI/1mainThings/congratsButton.png";
		SetLogo(*gameOverSprite, *gameOverTexture, path);
		gameOverSprite->setScale(scale2, scale2);
		float gameOverX = gameOverSprite->getGlobalBounds().width,
			gameOverY = gameOverSprite->getGlobalBounds().height;
		gameOverSprite->setPosition(m_windowSize.x / 2.0F - gameOverX / 2.0F, m_windowSize.y / 2.0F + 100 - gameOverY / 2.0F);
	}

	window.draw(*logoSprite);
	window.draw(*gameOverSprite);
}

void VoteWindow::SetSubTitle(sf::Sprite& titleSprite, sf::Texture& titleTexture, const std::string& titlePath)
{
	titleTexture.loadFromFile(titlePath);
	titleSprite.setTexture(titleTexture);

	float scale = DEFAULT_SCALE / 2.5F;
	titleSprite.setScale(scale, scale);

	float titleSpriteX = titleSprite.getGlobalBounds().width,
		titleSpriteY = titleSprite.getGlobalBounds().height;
	titleSprite.setPosition(m_windowSize.x / 2.0F - 250 - titleSpriteX / 2.0F, (300 - titleSpriteY / 2.0F) * DEFAULT_SCALE_Y);
}
