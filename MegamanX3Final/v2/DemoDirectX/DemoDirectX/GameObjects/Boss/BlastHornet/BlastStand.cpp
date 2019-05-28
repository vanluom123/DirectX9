#include "BlastStand.h"
#include "BlastAttack.h"
#include "BlastAppear.h"
#include <ctime>
#include "BlastShooter.h"
#include "Move.h"

BlastStand::BlastStand(BlastHornetData* b) :BlastHornetState(b)
{
	timeStand = 0;
	if (_pBlastHornetData->blastHornet->GetHP() > 20)
	{
		if (_pBlastHornetData->blastHornet->_isAllowMove == false)
		{
			if (_pBlastHornetData->blastHornet->_moveRandom == false)
			{
				_pBlastHornetData->blastHornet->SetVx(0);
				_pBlastHornetData->blastHornet->SetVy(20);
				_accelerateY = 10;
			}
			else
			{
				_pBlastHornetData->blastHornet->SetVx(0);
				_pBlastHornetData->blastHornet->SetVy(0);
				_accelerateY = 5;
				_accelerateX = 5;
			}

			return;
		}
		if (_pBlastHornetData->blastHornet->_isAllowMoveUp == true)
		{
			_pBlastHornetData->blastHornet->SetVx(80);
			_pBlastHornetData->blastHornet->SetVy(-80);
		}
		else
		{
			_pBlastHornetData->blastHornet->SetVx(0);
			_pBlastHornetData->blastHornet->SetVy(0);
		}
	}
}

BlastStand::~BlastStand()
{}

void BlastStand::Update(float dt)
{
	timeStand += dt;

	if (_pBlastHornetData->blastHornet->GetHP() > 20)
	{
		if (_pBlastHornetData->blastHornet->_isAllowMove == false)
		{
			if (_pBlastHornetData->blastHornet->_moveRandom == true)
			{
				if (timeStand <= 0.65)
				{
					_pBlastHornetData->blastHornet->AddVy(_accelerateY);
					_pBlastHornetData->blastHornet->AddVx(-_accelerateX);
				}
				else if (timeStand <= 1.5)
				{
					_pBlastHornetData->blastHornet->AddVy(-_accelerateY * 1.75);
					_pBlastHornetData->blastHornet->AddVx(-_accelerateX * 0.25);
				}
				else if (timeStand <= 2.25)
				{
					_pBlastHornetData->blastHornet->AddVy(_accelerateY * 2.5);
					_pBlastHornetData->blastHornet->AddVx(-_accelerateX * 0.15);
				}
				else if (timeStand <= 3.1)
				{
					_pBlastHornetData->blastHornet->AddVy(-_accelerateY * 1.25);
					_pBlastHornetData->blastHornet->AddVx(_accelerateX * 3.25);
				}
				else if (timeStand <= 3.25)
				{
					_pBlastHornetData->blastHornet->AddVy(-_accelerateY * 2.5);
					_pBlastHornetData->blastHornet->AddVx(-_accelerateX * 3.25);
				}
				else if (timeStand <= 3.5)
				{
					_pBlastHornetData->blastHornet->AddVy(-_accelerateY * 2.5);
					_pBlastHornetData->blastHornet->AddVx(-_accelerateX * 3.25);
				}
				else if (timeStand <= 3.75)
				{
					_pBlastHornetData->blastHornet->AddVy(-_accelerateY);
					_pBlastHornetData->blastHornet->AddVx(-_accelerateX);
				}
				else if (timeStand <= 4.5)
				{
					_pBlastHornetData->blastHornet->AddVy(_accelerateY * 3.25);
					_pBlastHornetData->blastHornet->AddVx(_accelerateX);
				}
				else
					_pBlastHornetData->blastHornet->SetState(new BlastAttack(_pBlastHornetData));
			}
			else
			{
				if (timeStand <= 0.5)
					_pBlastHornetData->blastHornet->AddVy(_accelerateY);
				else if (timeStand <= 1.5)
					_pBlastHornetData->blastHornet->AddVy(-_accelerateY);
				else
				{
					_pBlastHornetData->blastHornet->_moveRandom = true;
					_pBlastHornetData->blastHornet->SetState(new BlastAppear(_pBlastHornetData));
				}
			}
		}
		else
		{
			if (_pBlastHornetData->blastHornet->_isAllowMoveUp == true)
				_pBlastHornetData->blastHornet->AddVy(-_accelerateY * 10);
			else
			{
				if (timeStand > 1.0f)
					_pBlastHornetData->blastHornet->SetState(new BlastAttack(_pBlastHornetData));
			}
		}
	}
	else
		_pBlastHornetData->blastHornet->SetState(new SineMovement(_pBlastHornetData));
}

eBlastState BlastStand::GetState()
{
	return eBlastState::BLAST_STATE_STAND;
}

void BlastStand::OnCollision(BaseObject::eSideCollision side)
{
	if (_pBlastHornetData->blastHornet->_isAllowMove == true)
	{
		if (side == BaseObject::eSideCollision::TOP 
			|| side == BaseObject::eSideCollision::RIGHT)
		{
			_pBlastHornetData->blastHornet->_isAllowMoveUp = false;
			_pBlastHornetData->blastHornet->SetReverse(false);
			_pBlastHornetData->blastHornet->SetState(new BlastShooter(_pBlastHornetData));
		}
	}
}
