#pragma once
#include "Board.h"

Board::Board()
{
	Cards::Initialize();
	SetAllCards();
	Ghost::InitializeGhostCards();
	GetVisionCards();
}

void Board::GetVisionCards()
{
	for (int index = 0; index < Cards::NUMBER_OF_VISION_CARDS; ++index)
		m_visionCards.at(index) = Cards::GetRandomVisionCards();
}

std::tuple<uint16_t, uint16_t, uint16_t> Board::GiveSetToPlayer(const uint16_t& Person, const uint16_t& Place, const uint16_t& Weapon)
{
	auto bar = std::make_tuple(Person, Place, Weapon);
	return bar;
}

void Board::SetAllCards()
{
	for (uint16_t index = 0; index < Cards::NUMBER_OF_EXTRACTED_CARDS; ++index)
	{
		m_objectCardsInGame.at(index) = Cards::GetRandomObjectCards();
	}

	for (uint16_t index = 0; index < Cards::NUMBER_OF_EXTRACTED_CARDS; ++index)
	{
		m_characterCardsInGame.at(index) = Cards::GetRandomSuspectCards();
	}

	for (uint16_t index = 0; index < Cards::NUMBER_OF_EXTRACTED_CARDS; ++index)
	{
		m_locationCardsInGame.at(index) = Cards::GetRandomPlaceCards();
	}
}

void Board::GetSameCharacterGhostCards(std::vector<uint16_t>& characterGhostCards)
{
	for (uint16_t index = 0; index < NUMBER_OF_CARDS_IN_GAME; ++index)
	{
		characterGhostCards.push_back(Cards::GetSameGhostSuspectCard(m_characterCardsInGame.at(index)));
	}
}

void Board::GetSameObjectGhostCards(std::vector<uint16_t>& objectGhostCards)
{
	for (uint16_t index = 0; index < NUMBER_OF_CARDS_IN_GAME; ++index)
	{
		objectGhostCards.push_back(Cards::GetSameGhostObjectCard(m_objectCardsInGame.at(index)));
	}
}

void Board::GetSameLocationGhostCards(std::vector<uint16_t>& locationGhostCards)
{
	for (uint16_t index = 0; index < NUMBER_OF_CARDS_IN_GAME; ++index)
	{
		locationGhostCards.push_back(Cards::GetSameGhostPlaceCard(m_locationCardsInGame.at(index)));
	}
}