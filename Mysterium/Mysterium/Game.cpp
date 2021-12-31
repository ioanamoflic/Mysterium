#include "Game.h"
#include <windows.h>
#include <chrono>
#include <thread>

Game::Game()
{
	m_startWindow = std::make_unique<StartWindow>(m_window, "Mysterium");
	m_instructionWindow = std::make_unique<InstructionWindow>(m_window, "Instruction");
	m_characterWindow = std::make_unique<CharacterWindow>(m_window, "Choose Character");
	m_ghostWindow = std::make_unique<GhostWindow>(m_window, "Ghost Board");
	m_playerWindow = std::make_unique<PlayerWindow>(m_window, "Player Board");
	m_votingWindow = std::make_unique<VoteWindow>(m_window, "Vote Board");

	m_activeWindows.emplace("StartWindow", false);
	m_activeWindows.emplace("InstructionWindow", false);
	m_activeWindows.emplace("CharacterWindow", false);
	m_activeWindows.emplace("GhostWindow", false);
	m_activeWindows.emplace("PlayerWindow", false);
	m_activeWindows.emplace("VotingWindow", false);
}

void Game::RunGame()
{
	sf::Music music;
	music.openFromFile("GUI/creepy.ogg");
	music.play();

	m_window.create(sf::VideoMode::getDesktopMode(), "Mysterium");
	sf::Vector2i mousePos;

	m_activeWindows["StartWindow"] = true;

	bool pressed = false;
	bool guessCharacterCards = false, 
		guessLocationCards = false, 
		guessWeaponCards = false;

	while (m_window.isOpen())
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			pressed = false;
			if (event.type == sf::Event::Closed)
				m_window.close();

			mousePos.x = event.mouseMove.x;
			mousePos.y = event.mouseMove.y;

			if (event.type == sf::Event::MouseButtonPressed)
			{
				pressed = true;
				mousePos.x = event.mouseButton.x;
				mousePos.y = event.mouseButton.y;
				break;
			}
		}

		if (m_activeWindows["StartWindow"])
		{
			m_window.clear();
			m_startWindow->Display(m_window);
			m_window.display();

			if (m_startWindow->GetIsPlayButtonPressed() && pressed)
			{
				m_activeWindows["StartWindow"] = false;
				m_activeWindows["CharacterWindow"] = true;
				m_startWindow->SetIsPlayButtonPressed(false);
				pressed = false;
			}
			if (m_startWindow->GetIsInstrButtonPressed() && pressed)
			{
				m_activeWindows["StartWindow"] = false;
				m_activeWindows["InstructionWindow"] = true;
				m_startWindow->SetIsInstrButtonPressed(false);
				pressed = false;
			}
			continue;
		}

		if (m_activeWindows["InstructionWindow"])
		{
			m_window.clear();
			m_instructionWindow->Display(m_window);
			m_window.display();

			if (m_instructionWindow->GetIsArrowPressed() && pressed)
			{
				m_activeWindows["InstructionWindow"] = false;
				m_activeWindows["StartWindow"] = true;
				m_instructionWindow->SetIsArrowPressed(false);
				pressed = false;
			}
			continue;
		}

		if (m_activeWindows["CharacterWindow"])
		{
			m_window.clear();
			m_characterWindow->Display(m_window, pressed);
			m_window.display();

			if (m_characterWindow->CheckAllPressed())
			{
				m_activeWindows["CharacterWindow"] = false;
				m_activeWindows["GhostWindow"] = true;
				pressed = false;
			}
			continue;
		}

		if (m_activeWindows["GhostWindow"])
		{
			m_window.clear();
			m_ghostWindow->Display(m_window);
			m_window.display();

			if (m_ghostWindow->GetIsArrowPressed() && pressed)
			{
				m_activeWindows["GhostWindow"] = false;
				m_activeWindows["PlayerWindow"] = true;
				m_ghostWindow->SetIsArrowPressed(false);
				pressed = false;
			}
			continue;
		}

		if (m_activeWindows["PlayerWindow"])
		{
			m_window.clear();
			m_playerWindow->Display(m_window, pressed);
			m_window.display();
			m_playerWindow->GiveVisionCards(m_window, pressed);

			if (!guessCharacterCards)
			{
				guessCharacterCards = m_playerWindow->ChooseCharacterCards(m_window, pressed);
			}

			if (guessCharacterCards && !guessLocationCards)
			{
				m_playerWindow->GiveVisionCards(m_window, pressed);
				guessLocationCards = m_playerWindow->ChooseLocationCards(m_window, pressed);
			}

			if (guessCharacterCards && guessLocationCards && !guessWeaponCards)
			{
				m_playerWindow->GiveVisionCards(m_window, pressed);
				guessWeaponCards = m_playerWindow->ChooseWeaponCards(m_window, pressed);
			}

			if (guessWeaponCards)
			{
				m_activeWindows["VotingWindow"] = true;
				m_activeWindows["PlayerWindow"] = false;
				pressed = false;
			}

			if (m_playerWindow->GetIsArrowPressed() && pressed)
			{
				m_activeWindows["PlayerWindow"] = false;
				m_activeWindows["GhostWindow"] = true;
				m_playerWindow->SetIsArrowPressed(false);
				pressed = false;
			}
			continue;
		}

		if (m_activeWindows["VotingWindow"])
		{
			m_window.clear();
			m_votingWindow->Display(m_window, pressed);
			m_window.display();

			m_votingWindow->GiveVisionCards(m_window, pressed);

			if (m_votingWindow->GetIsArrowPressed() && pressed)
			{
				m_activeWindows["VotingWindow"] = false;
				m_activeWindows["GhostWindow"] = true;
				m_votingWindow->SetIsArrowPressed(false);
				pressed = false;
			}
			continue;
		}
	}
}