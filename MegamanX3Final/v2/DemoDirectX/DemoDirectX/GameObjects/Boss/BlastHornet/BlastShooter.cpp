#include "BlastShooter.h"
#include "BlastStand.h"
#include "Move.h"

BlastShooter::BlastShooter(BlastHornetData* b) :BlastHornetState(b)
{
	_pBlastHornetData->blastHornet->SetVx(0);
	_pBlastHornetData->blastHornet->SetVy(0);
	_timeShooter = 0;
	_count = -1;
}

BlastShooter::~BlastShooter()
{}

void BlastShooter::Update(float dt)
{
	_timeShooter += dt;

	/*if (timeShooter > 1)
	{
		b->allowMove = false;
		b->setState(new BlastStand(b));
	}*/

	if(_timeShooter > 1)
	{
		_timeShooter = 0;
		Shoot();
	}
}

eBlastState BlastShooter::GetState()
{
	return eBlastState::BLAST_STATE_SHOOTER;
}

void BlastShooter::Shoot()
{
	_count++;

	if (_count > 3)
	{
		_pBlastHornetData->blastHornet->_isAllowMove = false;
		_pBlastHornetData->blastHornet->SetState(new BlastStand(_pBlastHornetData));
		return;
	}

	if (_pBlastHornetData->blastHornet->GetListBullet()->size() < 5)
	{
		auto* ebullet = new BlastBullet();
		_pBlastHornetData->blastHornet->GetListBullet()->push_back(ebullet);
	}

	float px = 0;
	float py = _pBlastHornetData->blastHornet->GetBound().top;

	if (_count < 4)
	{
		if (_count == 0) py += 5;
		else if (_count == 1) py += 10;
		else if (_count == 2) py += 15;
		else py += 20;

		if (_pBlastHornetData->blastHornet->GetReverse())
			px = _pBlastHornetData->blastHornet->GetBound().right;
		else
			px = _pBlastHornetData->blastHornet->GetBound().left;
	}

	_pBlastHornetData->blastHornet->GetListBullet()->at(_count)->SetPosition(px, py);
	_pBlastHornetData->blastHornet->GetListBullet()->at(_count)->SetReverse(_pBlastHornetData->blastHornet->GetReverse());
	_pBlastHornetData->blastHornet->GetListBullet()->at(_count)->NewEntity();
}
