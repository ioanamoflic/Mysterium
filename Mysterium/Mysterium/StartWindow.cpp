#include "StartWindow.h"

StartWindow::StartWindow(sf::RenderWindow& m_window, const std::string& title)
	: Window(m_window, title), m_isPlayButtonPressed{ false }, m_isInstrButtonPressed{ false } {}

StartWindow::StartWindow()
{
}

bool StartWindow::GetIsPlayButtonPressed() const noexcept
{
	return m_isPlayButtonPressed;
}

bool StartWindow::GetIsInstrButtonPressed() const noexcept
{
	return m_isInstrButtonPressed;
}

void StartWindow::SetIsPlayButtonPressed(bool isPlayButtonPressed) noexcept
{
	m_isPlayButtonPressed = isPlayButtonPressed;
}

void StartWindow::SetIsInstrButtonPressed(bool isInstrButtonPressed) noexcept
{
	m_isInstrButtonPressed = isInstrButtonPressed;
}

void StartWindow::SetPlayButton(sf::Sprite& playButtonSprite, sf::Texture& playButtonTexture, const std::string& playButtonPath)
{
	playButtonTexture.loadFromFile(playButtonPath);
	playButtonSprite.setTexture(playButtonTexture);
	playButtonSprite.setScale(2, 2);
	float playButtonX = playButtonSprite.getGlobalBounds().width,
		playButtonY = playButtonSprite.getGlobalBounds().height;
	playButtonSprite.setPosition(m_windowSize.x / 2.0F - playButtonX / 2.0F, m_windowSize.y / 2.0F - playButtonY / 2.0F);
}

void StartWindow::SetInstructionButton(sf::Sprite& instructionButtonSprite, sf::Texture& instructionButtonTexture, const std::string& instructionButtonPath)
{
	instructionButtonTexture.loadFromFile(instructionButtonPath);
	instructionButtonSprite.setTexture(instructionButtonTexture);
	instructionButtonSprite.setScale(2, 2);
	float instructionButtonX = instructionButtonSprite.getGlobalBounds().width,
		instructionButtonY = instructionButtonSprite.getGlobalBounds().height;
	instructionButtonSprite.setPosition(m_windowSize.x / 2.0F - instructionButtonX / 2.0F, m_windowSize.y / 2.0F + 200 - instructionButtonY / 2.0F);
}

void StartWindow::Display(sf::RenderWindow& m_window)
{
	sf::Texture backgroundTexture, instructionTexture, logoTexture, playTexture, titleTexture;
	sf::Sprite backgroundSprite, instructionSprite, logoSprite, playSprite, titleSprite;

	SetBackground(backgroundSprite, backgroundTexture, "GUI/1mainThings/background2.jpg");
	SetInstructionButton(instructionSprite, instructionTexture, "GUI/1mainThings/instructionsButton.png");
	SetLogo(logoSprite, logoTexture, "GUI/1mainThings/logo.png");
	SetPlayButton(playSprite, playTexture, "GUI/1mainThings/playbutton.png");

	m_isPlayButtonPressed = MakeClickable(playSprite, sf::Mouse::getPosition(m_window));
	m_isInstrButtonPressed = MakeClickable(instructionSprite, sf::Mouse::getPosition(m_window));

	m_window.draw(backgroundSprite);
	m_window.draw(playSprite);
	m_window.draw(instructionSprite);
	m_window.draw(logoSprite);
}