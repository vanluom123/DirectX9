#pragma once
#include "BlastHornetState.h"
constexpr auto VAL = 0.0174532925199444;

constexpr auto LEFT_SIDE = 7709.47f;
constexpr auto RIGHT_SIDE = 7920.00f;
constexpr auto RELEGION = 7815.91f;

class BlastSinMovement :
	public BlastHornetState
{
public:
	BlastSinMovement(BlastHornet* b);
	~BlastSinMovement() = default;
	virtual void update(float dt) override;
	virtual void onCollision(Side_Collision side) override;
	virtual Hornet_State getState() override;

private:
	float m_moveTime;
	float m_gocSin;
	float m_vy;
	float m_speed;
};

