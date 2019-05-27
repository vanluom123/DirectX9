#include "BlastAttack.h"
#include "BlastStand.h"
#include "Move.h"

BlastAttack::BlastAttack(BlastHornetData* b) :BlastHornetState(b)
{
	m_blastHornetData->blastHornet->SetVx(-10);
	m_blastHornetData->blastHornet->SetVy(10);
	m_accelerateX = 10;
	m_accelerateY = 10;
}

BlastAttack::~BlastAttack()
{}

void BlastAttack::Update(float dt)
{
	m_blastHornetData->blastHornet->AddVy(m_accelerateY);
	m_blastHornetData->blastHornet->AddVx(-m_accelerateX);

	if (m_blastHornetData->blastHornet->GetVy() > 300)
		m_blastHornetData->blastHornet->SetVy(300);
}

void BlastAttack::OnCollision(BaseObject::eSideCollision side)
{
	if (side == BaseObject::eSideCollision::SIDE_COLLISION_LEFT || side == BaseObject::eSideCollision::SIDE_COLLISION_BOTTOM)
	{
		m_blastHornetData->blastHornet->SetReverse(true);
		m_blastHornetData->blastHornet->m_isAllowMoveUp = true;
		m_blastHornetData->blastHornet->m_isAllowMove = true;
		m_blastHornetData->blastHornet->SetState(new BlastStand(m_blastHornetData));
	}
}

BlastHornet::eBlastState BlastAttack::GetState()
{
	return BlastHornet::BLAST_STATE_ATTACK;
}
