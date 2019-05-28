#include "BlastHornetState.h"

BlastHornetState::BlastHornetState(BlastHornetData* b): _pBlastHornetData(b)
{
	_accelerateX = 0;
	_accelerateY = 0;
}

BlastHornetState::~BlastHornetState()
{}

void BlastHornetState::Update(float dt)
{}

void BlastHornetState::OnCollision(BaseObject::eSideCollision side)
{}

void BlastHornetState::Shoot()
{}
