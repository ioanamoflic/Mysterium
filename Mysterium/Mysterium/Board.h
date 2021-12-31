#pragma once
#include <array>
#include <vector>
#include "Cards.h"
#include "Player.h"
#include "Ghost.h"

class Board
{
public:
	static const uint16_t NUMBER_OF_CARDS_IN_GAME = 7;

	inline static std::array<uint16_t, NUMBER_OF_CARDS_IN_GAME> m_characterCardsInGame;
	inline static std::array<uint16_t, NUMBER_OF_CARDS_IN_GAME> m_locationCardsInGame;
    inline static std::array<uint16_t, NUMBER_OF_CARDS_IN_GAME> m_objectCardsInGame;
	inline static std::array<uint16_t, Cards::NUMBER_OF_VISION_CARDS> m_visionCards;

	Board();
	static void GetSameCharacterGhostCards(std::vector<uint16_t>&);
	static void GetSameObjectGhostCards(std::vector<uint16_t>&);
	static void GetSameLocationGhostCards(std::vector<uint16_t>&);

	std::tuple<uint16_t, uint16_t, uint16_t> GiveSetToPlayer(const uint16_t& Person, const uint16_t& Place, const uint16_t& Weapon);
	
	void GetVisionCards();
	void PrintAllSelectedCardsTest();
	void SetAllCards();
};
