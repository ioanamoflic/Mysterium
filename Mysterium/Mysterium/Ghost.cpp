#pragma once
#include "Ghost.h"
#include "Game.h"

Ghost::Ghost()
{

}

std::vector<Ghost::psychicAssociatedCards> Ghost::assignCardsForPlayers()
{
	std::vector<psychicAssociatedCards> ghostCards;

	ShuffleCards(m_characterGhostCards);
	ShuffleCards(m_locationGhostCards);
	ShuffleCards(m_objectGhostCards);

	for (int index = 0; index < NUMBER_OF_PSYCHICS; ++index)
	{
		int characterCard = m_characterGhostCards[index],
			locationCard = m_locationGhostCards[index],
			objectCard = m_objectGhostCards[index];

		ghostCards.emplace_back(characterCard, locationCard, objectCard);
	}

	return ghostCards;
}

void Ghost::InitializeGhostCards()
{
	Game::m_board.GetSameCharacterGhostCards(m_characterGhostCards);

	Game::m_board.GetSameObjectGhostCards(m_objectGhostCards);

	Game::m_board.GetSameLocationGhostCards(m_locationGhostCards);
}

void Ghost::ShuffleCards(std::vector<uint16_t>& vectorOfCards)
{
	std::random_device myRD;
	std::mt19937 mt(myRD());

	std::shuffle(vectorOfCards.begin(), vectorOfCards.end(), mt);
}