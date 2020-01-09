#include "BlastMove.h"
#include "BlastAttack.h"
#include "BlastShoot.h"
#include "BlastAppear.h"
#include "BlastIdle.h"

BlastMove::BlastMove(BlastHornet* b, bool moveUp) : BlastHornetState(b)
{
	this->b->setVx(0.0f);
	this->b->setVy(0.0f);
	this->m_timeMove = 0.0f;
	this->m_count = 0;
	this->m_currentMove = eMoveType_Down;
	this->m_confirmMoveUp = true;
	this->m_moveLeftUp = false;
	if (moveUp)
		this->m_currentMove = eMoveType_Up;
}

BlastMove::BlastMove(BlastHornet* b, bool moveUp, bool moveLeftUp) : BlastHornetState(b)
{
	this->b->setVx(0.0f);
	this->b->setVy(0.0f);
	this->m_timeMove = 0.0f;
	this->m_count = 0;
	this->m_currentMove = eMoveType_Down;
	this->m_moveLeftUp = moveLeftUp;
	this->m_confirmMoveUp = true;
	if (moveUp)
		this->m_currentMove = eMoveType_Up;
}

void BlastMove::update(float dt)
{
	this->m_timeMove += dt;

	switch (this->m_currentMove)
	{
		case eMoveType_Up:
		{
			if (this->m_moveLeftUp)
			{
				this->b->setVx(-this->b->getTempDxPos_PosStart());
				this->b->setVy(-this->b->getTempDyPos_PosStart());
			}
			else
			{
				this->b->setVx(this->b->getTempDxPos_PosStart());
				this->b->setVy(-this->b->getTempDyPos_PosStart());
			}

			break;
		}

		case eMoveType_Down:
		{
			this->b->setVy(50.0f);

			if (this->b->getVy() > 300.0f)
				this->b->setVy(300.0f);

			if (this->m_timeMove > 1.25f)
			{
				this->b->setVy(-50.0f);

				if (this->b->getVy() < -300.0f)
					this->b->setVy(-300.0f);
			}
			if (this->m_timeMove > 2.5f)
			{
				this->b->setVy(0.0f);
				this->b->setState(new BlastAppear(this->b));
			}

			break;
		}

		default:
			break;
	}
}

void BlastMove::shoot()
{
	if (this->m_count > 3)
	{
		this->b->setState(new BlastIdle(b));
		return;
	}

	if (this->b->getListBullet().size() < 5)
	{
		auto bullet = new BlastBullet();
		b->insertBullet(bullet);
	}

	float px = 0.0f;
	float py = b->getBound().top;

	if (this->m_count < 4)
	{
		if (this->m_count == 0) py += 5;
		else if (this->m_count == 1) py += 10;
		else if (this->m_count == 2) py += 15;
		else py += 20;

		if (this->b->getReverse())
			px = this->b->getBound().right;
		else
			px = this->b->getBound().left;
	}

	b->getIndexBullet(m_count)->setPosition(px, py);
	b->getIndexBullet(m_count)->setReverse(b->getReverse());
	b->getIndexBullet(m_count)->newObject();
	
	this->m_count++;
}

void BlastMove::gps()
{
}

Enumerator::Hornet_State BlastMove::getState()
{
	return Enumerator::Hornet_State::MOVE;
}

void BlastMove::onCollision(Side_Collision side)
{
	switch (this->m_currentMove)
	{
		case eMoveType_Up:
		{
			if (this->b->getDx() > 0)
			{
				if (side == Enumerator::Side_Collision::TOP || side == Enumerator::Side_Collision::RIGHT)
				{
					this->b->setReverse(false);
					this->b->setState(new BlastShoot(this->b));
				}
			}
			else
			{
				if (side == Enumerator::Side_Collision::TOP || side == Enumerator::Side_Collision::LEFT)
				{
					this->b->setReverse(true);
					this->b->setState(new BlastShoot(this->b));
				}
			}
			break;
		}

		default:
			break;
	}
}
