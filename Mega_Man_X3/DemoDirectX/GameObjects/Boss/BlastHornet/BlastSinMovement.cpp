#include "BlastSinMovement.h"
#include <cmath>
#include "BlastAttack.h"

BlastSinMovement::BlastSinMovement(BlastHornet* b) : BlastHornetState(b)
{
	b->setVx(0.0f);
	b->setVy(0.0f);
	m_moveTime = 0.0f;
	m_gocSin = 90.0f;
	m_vy = 0.0f;
	m_speed = -120.0f;
}

void BlastSinMovement::update(float dt)
{
	m_moveTime += dt / 10;

	if (m_moveTime < 1.5f)
	{
		// the right of side
		if (b->getBound().right > RIGHT_SIDE - 20.0f)
			b->setVx(m_speed);

		// the left of side
		else if (b->getPosition().x < LEFT_SIDE + 20.0f)
			b->setVx(-m_speed);

		m_vy = 120.0f * (float)sin(m_gocSin * VAL);
		b->setVy(m_vy);
	}
	else
	{
		m_moveTime = 0.0f;
		b->setState(new BlastAttack(b));
	}

	m_gocSin += 230 * dt;
}

void BlastSinMovement::onCollision(Side_Collision side)
{
}

Enumerator::Hornet_State BlastSinMovement::getState()
{
	return eHornet_Move;
}
