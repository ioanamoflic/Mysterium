#pragma once
#include <memory>
#include "StartWindow.h"
#include "InstructionWindow.h"
#include "CharacterWindow.h"
#include "GhostWindow.h"
#include "PlayerWindow.h"
#include "VoteWindow.h"

class Game : public StartWindow, public InstructionWindow, public CharacterWindow, public GhostWindow, public PlayerWindow
{
public:
	Game();
	void RunGame();
	inline static Board m_board;

private:
	std::map<std::string, bool> m_activeWindows;
	sf::RenderWindow m_window;

	std::unique_ptr<StartWindow> m_startWindow;
	std::unique_ptr<InstructionWindow> m_instructionWindow;
	std::unique_ptr<CharacterWindow> m_characterWindow;
	std::unique_ptr<GhostWindow> m_ghostWindow;
	std::unique_ptr<PlayerWindow> m_playerWindow;
	std::unique_ptr<VoteWindow> m_votingWindow;
};