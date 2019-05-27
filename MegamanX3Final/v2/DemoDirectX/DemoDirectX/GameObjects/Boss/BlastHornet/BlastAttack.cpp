#include "BlastAttack.h"
#include "BlastStand.h"
#include "Move.h"

BlastAttack::BlastAttack(BlastHornetData* b) :BlastHornetState(b)
{
	_pBlastHornetData->blastHornet->SetVx(-10);
	_pBlastHornetData->blastHornet->SetVy(10);
	_accelerateX = 10;
	_accelerateY = 10;
}

BlastAttack::~BlastAttack()
{}

void BlastAttack::Update(float dt)
{
	_pBlastHornetData->blastHornet->AddVy(_accelerateY);
	_pBlastHornetData->blastHornet->AddVx(-_accelerateX);

	if (_pBlastHornetData->blastHornet->GetVy() > 300)
		_pBlastHornetData->blastHornet->SetVy(300);
}

void BlastAttack::OnCollision(BaseObject::eSideCollision side)
{
	if (side == BaseObject::eSideCollision::LEFT || side == BaseObject::eSideCollision::BOTTOM)
	{
		_pBlastHornetData->blastHornet->SetReverse(true);
		_pBlastHornetData->blastHornet->_isAllowMoveUp = true;
		_pBlastHornetData->blastHornet->_isAllowMove = true;
		_pBlastHornetData->blastHornet->SetState(new BlastStand(_pBlastHornetData));
	}
}

eBlastState BlastAttack::GetState()
{
	return eBlastState::BLAST_STATE_ATTACK;
}
