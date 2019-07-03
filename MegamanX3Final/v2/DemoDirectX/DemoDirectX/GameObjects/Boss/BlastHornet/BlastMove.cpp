#include "BlastMove.h"
#include "BlastAttack.h"
#include "BlastShoot.h"
#include "BlastAppear.h"
#include "BlastIdle.h"

MoveTest::MoveTest(BlastHornet* b, bool moveUp) : BlastHornetState(b)
{
	b->setVx(0.0f);
	b->setVy(0.0f);
	m_timeMove = 0.0f;
	m_count = -1;
	m_gocSin = 90.0f;
	m_moveType = MovementType::MOVE_DOWN;

	if (moveUp)
		m_moveType = MovementType::MOVE_UP;
}

MoveTest::~MoveTest()
{}

void MoveTest::update(float dt)
{
	m_timeMove += dt;

	switch (m_moveType)
	{
		case MovementType::MOVE_TO_INFINITY:
			break;

		case MovementType::MOVE_DOWN:
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
		
		case MovementType::MOVE_UP:
		{
			b->setVy(-125.0f);
			b->setVx(30.0f);

			if (b->getVy() < -300.0f)
				b->setVy(-300.0f);

			if (b->getVx() > 300.0f)
				b->setVx(300.0f);
			else if (b->getVx() < -300.0f)
				b->setVx(-300.0f);

			break;
		}

		// Movement to graph of sin
		default:
		{
			if (m_timeMove > 1.0f)
			{
				m_timeMove = 0.0f;

				if (b->getDx() < 0.0f)
					b->setReverse(true);
				else
					b->setReverse(false);
			}

			break;
		}
	}
}

void MoveTest::shoot()
{
	m_count++;

	if (m_count > 3)
	{
		m_count = -1;
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
}

void MoveTest::GPS()
{
	// Getting GPS the location of Player
}

Enumerator::Hornet_State MoveTest::getState()
{
	return eHornet_Move;
}

void MoveTest::onCollision(Side_Collision side)
{
	switch (m_moveType)
	{
		case MovementType::MOVE_UP:
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
