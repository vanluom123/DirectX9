#include "BlastAttack.h"
#include "BlastStand.h"
#include "Move.h"

BlastAttack::BlastAttack(BlastHornetData* b) :BlastHornetState(b)
{
	b->GetHornet()->SetVx(-10);
	b->GetHornet()->SetVy(10);
	accelerateX = 10;
	accelerateY = 10;
}

BlastAttack::~BlastAttack()
{}

void BlastAttack::Update(float dt)
{
	b->GetHornet()->AddVy(accelerateY);
	b->GetHornet()->AddVx(-accelerateX);
	if (b->GetHornet()->GetVy() > 300)
		b->GetHornet()->SetVy(300);
}

void BlastAttack::OnCollision(Entity::SideCollisions side)
{
	if (side == Entity::SideCollisions::LEFT || side == Entity::SideCollisions::BOTTOM)
	{
		b->GetHornet()->SetReverse(true);
		b->GetHornet()->moveUp = true;
		b->GetHornet()->allowMove = true;
		b->GetHornet()->SetState(new BlastStand(b));
	}
}

BlastState BlastAttack::GetState()
{
	return BlastState::Attack;
}
