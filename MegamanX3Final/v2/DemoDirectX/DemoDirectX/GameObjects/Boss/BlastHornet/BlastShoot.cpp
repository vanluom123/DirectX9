#include "BlastShoot.h"
#include "BlastIdle.h"
#include "BlastMove.h"

BlastShoot::BlastShoot(BlastHornet* b) : BlastHornetState(b)
{
	b->setVx(0.0f);
	b->setVy(0.0f);
	m_timeShoot = 0.0f;
	m_count = -1;
}

BlastShoot::~BlastShoot()
{}

void BlastShoot::update(float dt)
{
	m_timeShoot += dt;

	if (m_timeShoot > 0.75f)
	{
		m_timeShoot = 0.0f;
		shoot();
	}
}

void BlastShoot::shoot()
{
	m_count++;

	if (m_count > 3)
	{
		m_count = -1;
		b->setState(new MoveTest(b, false));
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

Enumerator::Hornet_State BlastShoot::getState()
{
	return eHornet_Shoot;
}
