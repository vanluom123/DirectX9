#include "BlastHornetState.h"

BlastHornetState::BlastHornetState(BlastHornetData* b): _pBlastHornetData(b)
{
	accelerateX = 0;
	accelerateY = 0;
}

BlastHornetState::~BlastHornetState()
{}

void BlastHornetState::Update(float dt)
{}

void BlastHornetState::OnCollision(BaseObject::eSideCollision side)
{}

void BlastHornetState::Shoot()
{}
