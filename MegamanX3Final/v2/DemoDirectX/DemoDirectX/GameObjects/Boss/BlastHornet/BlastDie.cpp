#include "BlastDie.h"

BlastDie::BlastDie(BlastHornetData* b) :BlastHornetState(b)
{
	timeDie = 0;
}

BlastDie::~BlastDie()
{}

void BlastDie::Update(float dt)
{
	timeDie += dt;
	if (timeDie > 1)
		_pBlastHornetData->blastHornet->SetDraw(false);
}

eBlastState BlastDie::GetState()
{
	return eBlastState::BLAST_STATE_DIE;
}
