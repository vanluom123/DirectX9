#include "BlastHornetState.h"

BlastHornetState::BlastHornetState(BlastHornetData* b): b(b)
{
	accelerateX = 0;
	accelerateY = 0;
}

BlastHornetState::~BlastHornetState()
{}

void BlastHornetState::Update(float dt)
{}

void BlastHornetState::OnCollision(Entity::SideCollisions side)
{}

void BlastHornetState::Shoot()
{}
