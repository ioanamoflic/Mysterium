#pragma once
#include "Window.h"
#include "InstructionWindow.h"

class StartWindow : public Window
{
public:
	StartWindow(sf::RenderWindow&, const std::string&);
	StartWindow();

	void Display(sf::RenderWindow&);

	bool GetIsPlayButtonPressed() const noexcept;
	bool GetIsInstrButtonPressed() const noexcept;
	void SetIsPlayButtonPressed(bool) noexcept;
	void SetIsInstrButtonPressed(bool) noexcept;

private:
	bool m_isPlayButtonPressed;
	bool m_isInstrButtonPressed;

	void SetPlayButton(sf::Sprite&, sf::Texture&, const std::string&);
	void SetInstructionButton(sf::Sprite&, sf::Texture&, const std::string&);
};