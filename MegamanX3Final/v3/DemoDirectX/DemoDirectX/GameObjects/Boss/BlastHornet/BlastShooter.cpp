#include "BlastShooter.h"
#include "BlastStand.h"
#include "Move.h"

BlastShooter::BlastShooter(BlastHornetData* b) :BlastHornetState(b)
{
	m_blastHornetData->blastHornet->SetVx(0);
	m_blastHornetData->blastHornet->SetVy(0);
	_timeShooter = 0;
	_count = -1;
}

BlastShooter::~BlastShooter()
{}

void BlastShooter::Update(float dt)
{
	_timeShooter += dt;

	if(_timeShooter > 1)
	{
		_timeShooter = 0;
		Shoot();
	}
}

BlastHornet::eBlastState BlastShooter::GetState()
{
	return BlastHornet::BLAST_STATE_SHOOTER;
}

void BlastShooter::Shoot()
{
	_count++;

	if (_count > 3)
	{
		m_blastHornetData->blastHornet->m_isAllowMove = false;
		m_blastHornetData->blastHornet->SetState(new BlastStand(m_blastHornetData));
		return;
	}

	if (m_blastHornetData->blastHornet->GetListBullet()->size() < 5)
	{
		auto* ebullet = new BlastBullet();
		m_blastHornetData->blastHornet->GetListBullet()->push_back(ebullet);
	}

	float px = 0;
	float py = m_blastHornetData->blastHornet->GetBound().top;

	if (_count < 4)
	{
		if (_count == 0) py += 5;
		else if (_count == 1) py += 10;
		else if (_count == 2) py += 15;
		else py += 20;

		if (m_blastHornetData->blastHornet->GetReverse())
			px = m_blastHornetData->blastHornet->GetBound().right;
		else
			px = m_blastHornetData->blastHornet->GetBound().left;
	}

	m_blastHornetData->blastHornet->GetListBullet()->at(_count)->SetPosition(px, py);
	m_blastHornetData->blastHornet->GetListBullet()->at(_count)->SetReverse(m_blastHornetData->blastHornet->GetReverse());
	m_blastHornetData->blastHornet->GetListBullet()->at(_count)->NewEntity();
}
