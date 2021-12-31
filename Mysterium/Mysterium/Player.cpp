#include "Player.h"
#include "Ghost.h"

Player::Player(uint16_t crystal, uint16_t picture, Color color)
{
	Initialize(crystal, picture, color);
}

std::pair<uint16_t, Player::Color> Player::GetCrystalBowl() const noexcept
{
	return m_CrystalBowl;
}

void Player::Initialize(uint16_t crystal, uint16_t picture, Color color)
{
	m_CrystalBowl.first = crystal;
	m_CrystalBowl.second = color;
}