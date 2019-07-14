#include "BlastShoot.h"
#include "BlastIdle.h"
#include "BlastMove.h"
#include "BlastSinMovement.h"

BlastShoot::BlastShoot(BlastHornet* b) : BlastHornetState(b)
{
	b->setVx(0.0f);
	b->setVy(0.0f);
	m_timeShoot = 0.0f;
	m_count = 0;
}

void BlastShoot::update(float dt)
{
	m_timeShoot += dt;

	if (m_timeShoot > 0.25f)
	{
		m_timeShoot = 0.0f;
		shoot();
	}
}

void BlastShoot::shoot()
{
	if (m_count > 3)
	{
		b->setState(new BlastSinMovement(b));
		return;
	}

	if (b->getListBullet()->size() < 5)
	{
		auto bullet = new BlastBullet();
		bullet->setPlayer(b->getPlayer());
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

Enumerator::Hornet_State BlastShoot::getState()
{
	return eHornet_Shoot;
}
