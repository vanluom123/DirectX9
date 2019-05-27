#include "BlastHornetState.h"

BlastHornetState::BlastHornetState(BlastHornetData* b): m_blastHornetData(b)
{
	m_accelerateX = 0;
	m_accelerateY = 0;
}

BlastHornetState::~BlastHornetState()
{}

void BlastHornetState::Update(float dt)
{}

void BlastHornetState::OnCollision(BaseObject::eSideCollision side)
{}

void BlastHornetState::Shoot()
{}
