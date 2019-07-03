#include "BlastAttack.h"
#include "BlastIdle.h"
#include "BlastMove.h"

BlastAttack::BlastAttack(BlastHornet* b)
	: BlastHornetState(b)
{
	b->setVx(0.0f);
	b->setVy(0.0f);
}

BlastAttack::~BlastAttack()
{}

void BlastAttack::update(float dt)
{
	if (b->getDx() < 0) 
	{
		b->setVx(60.0f);
		b->setVy(120.0f);
	}
	else
	{
		b->setVx(-60.0f);
		b->setVy(120.0f);
	}

	if (b->getVy() > 300.0f)
		b->setVy(300.0f);

	if (b->getVx() < -300.0f)
		b->setVx(-300.0f);
	else if(b->getVx() > 300.0f)
		b->setVx(300.0f);
}

void BlastAttack::onCollision(Side_Collision side)
{
	switch (side)
	{
		case eSide_Left:
		case eSide_Bottom:
		{
			b->setReverse(true);
			b->setState(new MoveTest(b, true));
			break;
		}
		default:
			break;
	}
}

Enumerator::Hornet_State BlastAttack::getState()
{
	return eHornet_Attack;
}