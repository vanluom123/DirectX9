#include "BangerAttack.h"
#include "../BangerJump/BangerJump.h"

BangerAttack::BangerAttack(BangerData* banger) : BangerState(banger)
{
	m_timeAttack = 0.0f;
	m_count = -1;
}

void BangerAttack::Update(float dt)
{
	m_bangerData->banger->SetVx(0);
	m_timeAttack += dt;

	if (m_timeAttack >= 0.45f)
	{
		m_timeAttack = 0.0f;
		m_count++;

		if (m_count >= 3)
		{
			m_bangerData->banger->SetState(new BangerJump(m_bangerData));
			return;
		}

		if (m_bangerData->banger->GetListBullet()->size() < 4)
		{
			auto* ebullet = new BangerBullet();
			m_bangerData->banger->GetListBullet()->push_back(ebullet);
		}

		float posX;
		float posY = m_bangerData->banger->GetBound().top + 8;

		if (m_bangerData->banger->GetReverse())
			posX = m_bangerData->banger->GetBound().right - 8;
		else
			posX = m_bangerData->banger->GetBound().left + 8;

		m_bangerData->banger->GetListBullet()->at(m_count)->SetPosition(posX, posY);
		m_bangerData->banger->GetListBullet()->at(m_count)->SetReverse(m_bangerData->banger->GetReverse());
		m_bangerData->banger->GetListBullet()->at(m_count)->NewEntity();
	}
}

Banger::eBangerState BangerAttack::GetStateName()
{
	return Banger::eBangerState::BANGER_ATTACK;
}
