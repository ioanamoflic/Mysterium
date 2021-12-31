#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

class Cards
{
public:
	static const uint16_t NUMBER_OF_VISION_CARDS = 84;
	static const uint16_t NUMBER_OF_WEAPONS = 18;
	static const uint16_t NUMBER_OF_CHARACTERS = 18;
	static const uint16_t NUMBER_OF_LOCATIONS = 18;
	static const uint16_t NUMBER_OF_EXTRACTED_CARDS = 7;

	Cards();
	static void Initialize() noexcept;

	static uint16_t GetRandomCard(std::vector<uint16_t>&) noexcept;
	static uint16_t GetRandomObjectCards() noexcept;
	static uint16_t GetRandomSuspectCards() noexcept;
	static uint16_t GetRandomPlaceCards() noexcept;
	static uint16_t GetRandomVisionCards() noexcept;

	static uint16_t GetSameGhostObjectCard(uint16_t&) noexcept;
	static uint16_t GetSameGhostPlaceCard(uint16_t&) noexcept;
	static uint16_t GetSameGhostSuspectCard(uint16_t&) noexcept;

	static const uint16_t GetNoExtractedCards() noexcept;

	static std::vector<uint16_t>& GetVisionCards() noexcept;
	static std::vector<uint16_t>& GetPlacesCards() noexcept;
	static std::vector<uint16_t>& GetObjectCards() noexcept;
	static std::vector<uint16_t>& GetCharacterCards() noexcept;
	static std::vector<uint16_t>& GetGhostPlacesCards() noexcept;
	static std::vector<uint16_t>& GetGhostObjectCards() noexcept;
	static std::vector<uint16_t>& GetGhostCharacterCards() noexcept;

private:
	inline static std::vector<uint16_t> m_visionCards;
	inline static std::vector<uint16_t> m_objectsCards;
	inline static std::vector<uint16_t> m_suspectsCards;
	inline static std::vector<uint16_t> m_placesCards;
	inline static std::vector<uint16_t> m_ghostObjectsCards;
	inline static std::vector<uint16_t> m_ghostSuspectsCards;
	inline static std::vector<uint16_t> m_ghostPlacesCards;
};

