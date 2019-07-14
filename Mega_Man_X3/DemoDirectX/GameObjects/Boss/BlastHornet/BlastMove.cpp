#include "BlastMove.h"
#include "BlastAttack.h"
#include "BlastShoot.h"
#include "BlastAppear.h"
#include "BlastIdle.h"

BlastMove::BlastMove(BlastHornet* b, bool moveUp) : BlastHornetState(b)
{
	b->setVx(0.0f);
	b->setVy(0.0f);
	m_timeMove = 0.0f;
	m_count = 0;
	m_currentMove = eMoveType_Down;
	m_confirmMoveUp = true;
	m_moveLeftUp = false;
	if (moveUp)
		m_currentMove = eMoveType_Up;
}

BlastMove::BlastMove(BlastHornet* b, bool moveUp, bool moveLeftUp) : BlastHornetState(b)
{
	b->setVx(0.0f);
	b->setVy(0.0f);
	m_timeMove = 0.0f;
	m_count = 0;
	m_currentMove = eMoveType_Down;
	m_moveLeftUp = moveLeftUp;
	m_confirmMoveUp = true;
	if (moveUp)
		m_currentMove = eMoveType_Up;
}

void BlastMove::update(float dt)
{
	m_timeMove += dt;

	switch (m_currentMove)
	{
		case eMoveType_Up:
		{
			if (m_moveLeftUp)
			{
				b->setVx(-b->getTempDxPos_PosStart());
				b->setVy(-b->getTempDyPos_PosStart());
			}
			else
			{
				b->setVx(b->getTempDxPos_PosStart());
				b->setVy(-b->getTempDyPos_PosStart());
			}

			break;
		}

		case eMoveType_Down:
		{
			b->setVy(50.0f);

			if (b->getVy() > 300.0f)
				b->setVy(300.0f);

			if (m_timeMove > 1.25f)
			{
				b->setVy(-50.0f);

				if (b->getVy() < -300.0f)
					b->setVy(-300.0f);
			}
			if (m_timeMove > 2.5f)
			{
				b->setVy(0.0f);
				b->setState(new BlastAppear(b));
			}

			break;
		}

		default:
			break;
	}
}

void BlastMove::shoot()
{
	if (m_count > 3)
	{
		b->setState(new BlastIdle(b));
		return;
	}

	if (b->getListBullet()->size() < 5)
	{
		auto bullet = new BlastBullet();
		b->getListBullet()->push_back(bullet);
	}

	float px = 0.0f;
	float py = b->getBound().top;

	if (m_count < 4)
	{
		if (m_count == 0) py += 5;
		else if (m_count == 1) py += 10;
		else if (m_count == 2) py += 15;
		else py += 20;

		if (b->getReverse())
			px = b->getBound().right;
		else
			px = b->getBound().left;
	}

	b->getListBullet()->at(m_count)->setPosition(px, py);
	b->getListBullet()->at(m_count)->setReverse(b->getReverse());
	b->getListBullet()->at(m_count)->newObject();

	m_count++;
}

void BlastMove::gps()
{
}

Enumerator::Hornet_State BlastMove::getState()
{
	return eHornet_Move;
}

void BlastMove::onCollision(Side_Collision side)
{
	switch (m_currentMove)
	{
		case eMoveType_Up:
		{
			if (b->getDx() > 0)
			{
				if (side == eSide_Top || side == eSide_Right)
				{
					b->setReverse(false);
					b->setState(new BlastShoot(b));
				}
			}
			else
			{
				if (side == eSide_Top || side == eSide_Left)
				{
					b->setReverse(true);
					b->setState(new BlastShoot(b));
				}
			}
			break;
		}

		default:
			break;
	}
}
