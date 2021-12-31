#pragma once
#include "Window.h"

class InstructionWindow : public Window
{
public:
	InstructionWindow(sf::RenderWindow&, const std::string&);
	InstructionWindow();

	bool GetIsArrowPressed() const noexcept;
	void SetIsArrowPressed(bool) noexcept;

	void Display(sf::RenderWindow&);	

private:
	bool m_isArrowPressed;
};

