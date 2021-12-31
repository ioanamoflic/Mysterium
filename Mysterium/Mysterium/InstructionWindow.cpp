#include "InstructionWindow.h"

InstructionWindow::InstructionWindow(sf::RenderWindow& m_window, const std::string& title)
	: Window(m_window, title) {}

InstructionWindow::InstructionWindow()
{
}

bool InstructionWindow::GetIsArrowPressed() const noexcept
{
	return m_isArrowPressed;
}

void InstructionWindow::SetIsArrowPressed(bool isArrowPressed) noexcept
{
	m_isArrowPressed = isArrowPressed;
}

void InstructionWindow::Display(sf::RenderWindow& m_window)
{
	sf::Texture backgroundTexture, arrowTexture;
	sf::Sprite backgroundSprite, arrowSprite;

	SetBackground(backgroundSprite, backgroundTexture, "GUI/1mainThings/rulesWindow.png");
	SetArrowButton(arrowSprite, arrowTexture, "GUI/1mainThings/arrowRev.png", LEFT_SIDE);

	m_isArrowPressed = MakeClickable(arrowSprite, sf::Mouse::getPosition(m_window));

	m_window.draw(backgroundSprite);
	m_window.draw(arrowSprite);
}
