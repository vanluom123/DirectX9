#include "BlastShooter.h"
#include "BlastStand.h"
#include "Move.h"

BlastShooter::BlastShooter(BlastHornetData* b) :BlastHornetState(b)
{
	b->GetHornet()->SetVx(0);
	b->GetHornet()->SetVy(0);
	timeShooter = 0;
	count = -1;
}

BlastShooter::~BlastShooter()
{}

void BlastShooter::Update(float dt)
{
	timeShooter += dt;

	/*if (timeShooter > 1)
	{
		b->allowMove = false;
		b->setState(new BlastStand(b));
	}*/

	if(timeShooter > 1)
	{
		timeShooter = 0;
		Shoot();
	}
}

BlastState BlastShooter::GetState()
{
	return BlastState::Shooter;
}

void BlastShooter::Shoot()
{
	count++;

	if (count > 3)
	{
		b->GetHornet()->allowMove = false;
		b->GetHornet()->SetState(new BlastStand(b));
		return;
	}

	if (b->GetHornet()->GetListBullet()->size() < 5)
	{
		auto* ebullet = new BlastBullet();
		b->GetHornet()->GetListBullet()->push_back(ebullet);
	}

	float px = 0;
	float py = b->GetHornet()->GetBound().top;

	if (count < 4)
	{
		if (count == 0) py += 5;
		else if (count == 1) py += 10;
		else if (count == 2) py += 15;
		else py += 20;

		if (b->GetHornet()->GetReverse())
			px = b->GetHornet()->GetBound().right;
		else
			px = b->GetHornet()->GetBound().left;
	}

	b->GetHornet()->GetListBullet()->at(count)->SetPosition(px, py);
	b->GetHornet()->GetListBullet()->at(count)->SetReverse(b->GetHornet()->GetReverse());
	b->GetHornet()->GetListBullet()->at(count)->NewEntity();
}
