#pragma once
#include "Player.h"
#include "Cards.h"
#include <cstdint>
#include <vector>
#include <tuple>

class Ghost
{
public:
	using psychicAssociatedCards = std::tuple<uint16_t, uint16_t, uint16_t>;

	static const uint16_t NUMBER_OF_PSYCHICS = 4;
	static const uint16_t NUMBER_OF_CROW_MARKERS = 3;

	Ghost();
	static std::vector<psychicAssociatedCards> assignCardsForPlayers();
	inline static std::vector<uint16_t> m_characterGhostCards;
	inline static std::vector<uint16_t> m_locationGhostCards;
	inline static std::vector<uint16_t> m_objectGhostCards;
	
	static void InitializeGhostCards();

private:
	static void ShuffleCards(std::vector<uint16_t>&);
};
