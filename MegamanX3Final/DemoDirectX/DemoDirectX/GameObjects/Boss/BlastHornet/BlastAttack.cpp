#include "BlastAttack.h"
#include "BlastStand.h"
#include "Move.h"

BlastAttack::BlastAttack(BlastHornetData* b) :BlastHornetState(b)
{
	_pBlastHornetData->blastHornet->SetVx(-10);
	_pBlastHornetData->blastHornet->SetVy(10);
	accelerateX = 10;
	accelerateY = 10;
}

BlastAttack::~BlastAttack()
{}

void BlastAttack::Update(float dt)
{
	_pBlastHornetData->blastHornet->AddVy(accelerateY);
	_pBlastHornetData->blastHornet->AddVx(-accelerateX);

	if (_pBlastHornetData->blastHornet->GetVy() > 300)
		_pBlastHornetData->blastHornet->SetVy(300);
}

void BlastAttack::OnCollision(BaseObject::eSideCollision side)
{
	if (side == BaseObject::eSideCollision::LEFT || side == BaseObject::eSideCollision::BOTTOM)
	{
		_pBlastHornetData->blastHornet->SetReverse(true);
		_pBlastHornetData->blastHornet->moveUp = true;
		_pBlastHornetData->blastHornet->allowMove = true;
		_pBlastHornetData->blastHornet->SetState(new BlastStand(_pBlastHornetData));
	}
}

BlastState BlastAttack::GetState()
{
	return BlastState::Attack;
}
