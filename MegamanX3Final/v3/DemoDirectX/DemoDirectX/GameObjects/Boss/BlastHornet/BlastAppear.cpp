#include "BlastAppear.h"
#include "BlastStand.h"


BlastAppear::BlastAppear(BlastHornetData* b) :BlastHornetState(b)
{
	m_blastHornetData->blastHornet->SetVx(0);
	m_blastHornetData->blastHornet->SetVy(0);
	m_timeAppear = 0;
}

BlastAppear::~BlastAppear()
{}

void BlastAppear::Update(float dt)
{
	m_timeAppear += dt;
	if (m_timeAppear > 3.0f)
	{
		m_blastHornetData->blastHornet->m_isAllowMove = true;
		m_blastHornetData->blastHornet->SetState(new BlastStand(m_blastHornetData));
	}
}

BlastHornet::eBlastState BlastAppear::GetState()
{
	return BlastHornet::BLAST_STATE_APPEAR;
}
