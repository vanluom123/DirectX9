#include "BangerAttack.h"
#include "../BangerJump/BangerJump.h"
#include "..//..//BangerBullet/BangerBullet.h"

BangerAttack::BangerAttack(Banger* banger) : BangerState(banger)
{
	_timeAttack = 0.0f;
	_count = -1;
}

BangerAttack::~BangerAttack()
{
}

void BangerAttack::Update(float dt)
{
	m_pBanger->setVx(0.0f);
	_timeAttack += dt;

	if (_timeAttack >= 0.45f)
	{
		_timeAttack = 0.0f;
		_count++;

		if (_count >= 3)
		{
			m_pBanger->setState(new BangerJump(m_pBanger));
			return;
		}

		if (m_pBanger->getListBullet().size() < 4)
		{
			auto bullet = new BangerBullet();
			m_pBanger->insertBullet(bullet);
		}

		float posX;
		float posY = m_pBanger->getBound().top + 8;

		if (m_pBanger->getReverse())
			posX = m_pBanger->getBound().right - 8;
		else
			posX = m_pBanger->getBound().left + 8;

		m_pBanger->getIndexBullet(_count)->setPosition(posX, posY);
		m_pBanger->getIndexBullet(_count)->setReverse(m_pBanger->getReverse());
		m_pBanger->getIndexBullet(_count)->newObject();
	}
}

Enumerator::Banger_State BangerAttack::getState()
{
	return Enumerator::Banger_State::ATTACK;
}
