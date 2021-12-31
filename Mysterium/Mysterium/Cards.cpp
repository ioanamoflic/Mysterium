#include "Cards.h"

Cards::Cards()
{
	
}

void Cards::Initialize() noexcept
{
	for (uint16_t index = 0; index < NUMBER_OF_CHARACTERS; ++index)
		m_suspectsCards.push_back(index + 1);

	for (uint16_t index = 0; index < NUMBER_OF_LOCATIONS; ++index)
		m_placesCards.push_back(NUMBER_OF_LOCATIONS + index + 1);

	for (uint16_t index = 0; index < NUMBER_OF_WEAPONS; ++index)
		m_objectsCards.push_back(2 * NUMBER_OF_WEAPONS + index + 1);

	for (uint16_t index = 0; index < NUMBER_OF_VISION_CARDS; ++index)
		m_visionCards.push_back(index + 1);
}

uint16_t Cards::GetRandomCard(std::vector<uint16_t>& cards) noexcept
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<uint16_t> dis(0, cards.size() - 1);
	uint16_t returned = cards[dis(mt)];
	cards.erase(std::remove(cards.begin(), cards.end(), returned), cards.end());
	return returned;
}

uint16_t Cards::GetRandomObjectCards() noexcept
{
	return GetRandomCard(m_objectsCards);
}

uint16_t Cards::GetRandomSuspectCards() noexcept
{
	return GetRandomCard(m_suspectsCards);
}

uint16_t Cards::GetRandomPlaceCards() noexcept
{
	return GetRandomCard(m_placesCards);
}

uint16_t Cards::GetRandomVisionCards() noexcept
{
	return GetRandomCard(m_visionCards);
}

uint16_t Cards::GetSameGhostObjectCard(uint16_t& objectCard) noexcept
{
	m_ghostObjectsCards.erase(std::remove(m_ghostObjectsCards.begin(), m_ghostObjectsCards.end(), objectCard), m_ghostObjectsCards.end());
	return objectCard;
}

uint16_t Cards::GetSameGhostPlaceCard(uint16_t& placeCard) noexcept
{
	m_ghostPlacesCards.erase(std::remove(m_ghostPlacesCards.begin(), m_ghostPlacesCards.end(), placeCard), m_ghostPlacesCards.end());
	return placeCard;
}

uint16_t Cards::GetSameGhostSuspectCard(uint16_t& suspectCard) noexcept
{
	m_ghostSuspectsCards.erase(std::remove(m_ghostSuspectsCards.begin(), m_ghostSuspectsCards.end(), suspectCard), m_ghostSuspectsCards.end());
	return suspectCard;
}

const uint16_t Cards::GetNoExtractedCards() noexcept
{
	return NUMBER_OF_EXTRACTED_CARDS;
}

std::vector<uint16_t>& Cards::GetVisionCards() noexcept
{
	return m_visionCards;
}

std::vector<uint16_t>& Cards::GetPlacesCards() noexcept
{
	return m_placesCards;
}

std::vector<uint16_t>& Cards::GetObjectCards() noexcept
{
	return m_objectsCards;
}

std::vector<uint16_t>& Cards::GetCharacterCards() noexcept
{
	return m_suspectsCards;
}

std::vector<uint16_t>& Cards::GetGhostPlacesCards() noexcept
{
	return m_ghostPlacesCards;
}

std::vector<uint16_t>& Cards::GetGhostObjectCards() noexcept
{
	return m_ghostObjectsCards;
}

std::vector<uint16_t>& Cards::GetGhostCharacterCards() noexcept
{
	return m_ghostSuspectsCards;
}
