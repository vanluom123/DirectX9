#include "BlastAttack.h"
#include "BlastIdle.h"
#include "BlastMove.h"

BlastAttack::BlastAttack(BlastHornet* b)
	: BlastHornetState(b)
{
	b->setVx(0.0f);
	b->setVy(0.0f);
	m_timeAttack = 0.0f;
}

void BlastAttack::update(float dt)
{
	m_timeAttack += dt;

	if (m_timeAttack < 0.9f) {
		m_distance.x = b->getPlayer()->getPosition().x - b->getPosition().x;
		m_distance.y = b->getPlayer()->getPosition().y - b->getPosition().y;
		D3DXVec2Normalize(&m_distance, &m_distance);

		b->setVx(m_distance.x * 125.0f);
		b->setVy(m_distance.y * 250.f);
	}
}

void BlastAttack::onCollision(Side_Collision side)
{
	switch (side)
	{
		case Enumerator::Side_Collision::LEFT:
		case Enumerator::Side_Collision::BOTTOM:
		{
			float fDxPosStart = b->getDxPos_PosStart();
			float fDyPosStart = b->getDyPos_PosStart();

			b->setTempDxPos_PosStart(fDxPosStart);
			b->setTempDyPos_PosStart(fDyPosStart);

			b->setReverse(true);
			b->setState(new BlastMove(b, true, false));
			break;
		}
		default:
			break;
	}
}

Enumerator::Hornet_State BlastAttack::getState()
{
	return Enumerator::Hornet_State::ATTACK;
}