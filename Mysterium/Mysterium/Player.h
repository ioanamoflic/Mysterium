#pragma once
#include <cstdint>
#include <array>
#include <tuple>
#include <vector>
class Player
{
public:

	enum class Color : uint16_t
	{
		PURPLE,
		YELLOW,
		BLUE,
		RED
	};

	void Initialize(uint16_t crystal, uint16_t picture, Color color);
	Player(uint16_t crystal, uint16_t picture, Color color);

	std::pair<uint16_t, Color> GetCrystalBowl() const noexcept;

private:
	std::pair<uint16_t, Color> m_CrystalBowl;
};

