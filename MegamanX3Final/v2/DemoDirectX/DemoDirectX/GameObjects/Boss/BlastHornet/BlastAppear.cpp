#include "BlastAppear.h"
#include "BlastStand.h"


BlastAppear::BlastAppear(BlastHornetData* b) :BlastHornetState(b)
{
	_pBlastHornetData->blastHornet->SetVx(0);
	_pBlastHornetData->blastHornet->SetVy(0);
	timeAppear = 0;
}

BlastAppear::~BlastAppear()
{}

void BlastAppear::Update(float dt)
{
	timeAppear += dt;
	if (timeAppear > 3.0f)
	{
		_pBlastHornetData->blastHornet->_isAllowMove = true;
		_pBlastHornetData->blastHornet->SetState(new BlastStand(_pBlastHornetData));
	}
}

eBlastState BlastAppear::GetState()
{
	return eBlastState::BLAST_STATE_APPEAR;
}
