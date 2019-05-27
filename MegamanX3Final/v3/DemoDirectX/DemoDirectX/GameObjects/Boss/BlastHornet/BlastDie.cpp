#include "BlastDie.h"

BlastDie::BlastDie(BlastHornetData* b) :BlastHornetState(b)
{
	m_timeDie = 0;
}

BlastDie::~BlastDie()
{}

void BlastDie::Update(float dt)
{
	m_timeDie += dt;
	if (m_timeDie > 1)
		m_blastHornetData->blastHornet->SetDraw(false);
}

BlastHornet::eBlastState BlastDie::GetState()
{
	return BlastHornet::BLAST_STATE_DIE;
}
