#include "pch.h"
#include "../Mysterium/Cards.h"
#include "../Mysterium/Cards.cpp"

TEST(InitializeCards, TestCards)
{
	Cards cards;
	cards.Initialize();

	for (uint16_t index = 0; index < cards.GetVisionCards().size(); ++index)
	{
		EXPECT_TRUE(cards.GetVisionCards().at(index) > 0 && cards.GetVisionCards().at(index) <= Cards::NUMBER_OF_VISION_CARDS);
	}

	for (uint16_t index = 0; index < cards.GetCharacterCards().size(); ++index)
	{
		EXPECT_TRUE(cards.GetCharacterCards().at(index) > 0 && cards.GetCharacterCards().at(index) <= Cards::NUMBER_OF_CHARACTERS);
	}

	for (uint16_t index = 0; index < cards.GetPlacesCards().size(); ++index)
	{
		EXPECT_TRUE(cards.GetPlacesCards().at(index) > Cards::NUMBER_OF_CHARACTERS && cards.GetPlacesCards().at(index) <= 2 * cards.NUMBER_OF_LOCATIONS);
	}

	for (uint16_t index = 0; index < cards.GetObjectCards().size(); ++index)
	{
		EXPECT_TRUE(cards.GetObjectCards().at(index) > 2 * Cards::NUMBER_OF_LOCATIONS && cards.GetObjectCards().at(index) <= 3 * cards.NUMBER_OF_WEAPONS);
	}
}

TEST(DifferentCards, TestCards)
{
	Cards cards;
	cards.Initialize();

	for (uint16_t index = 0; index < cards.GetVisionCards().size() - 1; ++index)
	{
		for (uint16_t next = index + 1; next < cards.GetVisionCards().size(); ++next)

			EXPECT_FALSE(cards.GetVisionCards().at(index) == cards.GetVisionCards().at(next));
	}

	for (uint16_t index = 0; index < cards.GetCharacterCards().size() - 1; ++index)
	{
		for (uint16_t next = index + 1; next < cards.GetCharacterCards().size(); ++next)

			EXPECT_FALSE(cards.GetCharacterCards().at(index) == cards.GetCharacterCards().at(next));
	}

	for (uint16_t index = 0; index < cards.GetPlacesCards().size() - 1; ++index)
	{
		for (uint16_t next = index + 1; next < cards.GetPlacesCards().size(); ++next)

			EXPECT_FALSE(cards.GetPlacesCards().at(index) == cards.GetPlacesCards().at(next));
	}

	for (uint16_t index = 0; index < cards.GetObjectCards().size() - 1; ++index)
	{
		for (uint16_t next = index + 1; next < cards.GetObjectCards().size(); ++next)

			EXPECT_FALSE(cards.GetObjectCards().at(index) == cards.GetObjectCards().at(next));
	}
}

TEST(RandomCards, TestCards)
{
	Cards card;

	for (int index = 0; index < card.NUMBER_OF_VISION_CARDS; ++index)
	{
		uint16_t extracted = card.GetRandomCard(card.GetVisionCards());
	}
	EXPECT_TRUE(card.GetVisionCards().size() == 0);

	for (int index = 0; index < card.NUMBER_OF_CHARACTERS; ++index)
	{
		uint16_t extracted = card.GetRandomCard(card.GetCharacterCards());
	}
	EXPECT_TRUE(card.GetCharacterCards().size() == 0);

	for (int index = 0; index < card.NUMBER_OF_LOCATIONS; ++index)
	{
		uint16_t extracted = card.GetRandomCard(card.GetPlacesCards());
	}
	EXPECT_TRUE(card.GetPlacesCards().size() == 0);

	for (int index = 0; index < card.NUMBER_OF_WEAPONS; ++index)
	{
		uint16_t extracted = card.GetRandomCard(card.GetObjectCards());
	}
	EXPECT_TRUE(card.GetObjectCards().size() == 0);
}

TEST(GettingSameCards, TestCards)
{
	Cards card;
	card.Initialize();

	for (int index = 0; index < card.NUMBER_OF_CHARACTERS; ++index)
	{
		uint16_t extracted = card.GetRandomCard(card.GetCharacterCards());
		EXPECT_TRUE(extracted == card.GetSameGhostSuspectCard(extracted));
	}

	for (int index = 0; index < card.NUMBER_OF_LOCATIONS; ++index)
	{
		uint16_t extracted = card.GetRandomCard(card.GetPlacesCards());
		EXPECT_TRUE(extracted == card.GetSameGhostPlaceCard(extracted));
	}

	for (int index = 0; index < card.NUMBER_OF_WEAPONS; ++index)
	{
		uint16_t extracted = card.GetRandomCard(card.GetObjectCards());
		EXPECT_TRUE(extracted == card.GetSameGhostObjectCard(extracted));
	}
}