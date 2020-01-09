#include "BlastSinMovement.h"
#include <cmath>
#include "BlastAttack.h"

BlastSinMovement::BlastSinMovement(BlastHornet* b) : BlastHornetState(b)
{
	this->b->setVx(0.0f);
	this->b->setVy(0.0f);
	this->m_moveTime = 0.0f;
	this->m_gocSin = 90.0f;
	this->m_vy = 0.0f;
	this->m_speed = -120.0f;
}

void BlastSinMovement::update(float dt)
{
	this->m_moveTime += dt / 10;

	if (this->m_moveTime < 1.5f)
	{
		// the right of side
		if (this->b->getBound().right > RIGHT_SIDE - 20.0f)
			this->b->setVx(this->m_speed);

		// the left of side
		else if (this->b->getPosition().x < LEFT_SIDE + 20.0f)
			this->b->setVx(-this->m_speed);

		this->m_vy = 120.0f * (float)sin(this->m_gocSin * VAL);
		this->b->setVy(this->m_vy);
	}
	else
	{
		this->m_moveTime = 0.0f;
		this->b->setState(new BlastAttack(b));
	}

	this->m_gocSin += 230 * dt;
}

void BlastSinMovement::onCollision(Side_Collision side)
{
}

Enumerator::Hornet_State BlastSinMovement::getState()
{
	return Enumerator::Hornet_State::MOVE;
}
