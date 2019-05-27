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
		if (_pBlastHornetData->blastHornet->allowMove == false)
		{
			if (_pBlastHornetData->blastHornet->moveRandom == false)
			{
				_pBlastHornetData->blastHornet->SetVx(0);
				_pBlastHornetData->blastHornet->SetVy(20);
				accelerateY = 10;
			}
			else
			{
				_pBlastHornetData->blastHornet->SetVx(0);
				_pBlastHornetData->blastHornet->SetVy(0);
				accelerateY = 5;
				accelerateX = 5;
			}

			return;
		}
		if (_pBlastHornetData->blastHornet->moveUp == true)
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
		if (_pBlastHornetData->blastHornet->allowMove == false)
		{
			if (_pBlastHornetData->blastHornet->moveRandom == true)
			{
				if (timeStand <= 0.65)
				{
					_pBlastHornetData->blastHornet->AddVy(accelerateY);
					_pBlastHornetData->blastHornet->AddVx(-accelerateX);
				}
				else if (timeStand <= 1.5)
				{
					_pBlastHornetData->blastHornet->AddVy(-accelerateY * 1.75);
					_pBlastHornetData->blastHornet->AddVx(-accelerateX * 0.25);
				}
				else if (timeStand <= 2.25)
				{
					_pBlastHornetData->blastHornet->AddVy(accelerateY * 2.5);
					_pBlastHornetData->blastHornet->AddVx(-accelerateX * 0.15);
				}
				else if (timeStand <= 3.1)
				{
					_pBlastHornetData->blastHornet->AddVy(-accelerateY * 1.25);
					_pBlastHornetData->blastHornet->AddVx(accelerateX * 3.25);
				}
				else if (timeStand <= 3.25)
				{
					_pBlastHornetData->blastHornet->AddVy(-accelerateY * 2.5);
					_pBlastHornetData->blastHornet->AddVx(-accelerateX * 3.25);
				}
				else if (timeStand <= 3.5)
				{
					_pBlastHornetData->blastHornet->AddVy(-accelerateY * 2.5);
					_pBlastHornetData->blastHornet->AddVx(-accelerateX * 3.25);
				}
				else if (timeStand <= 3.75)
				{
					_pBlastHornetData->blastHornet->AddVy(-accelerateY);
					_pBlastHornetData->blastHornet->AddVx(-accelerateX);
				}
				else if (timeStand <= 4.5)
				{
					_pBlastHornetData->blastHornet->AddVy(accelerateY * 3.25);
					_pBlastHornetData->blastHornet->AddVx(accelerateX);
				}
				else
					_pBlastHornetData->blastHornet->SetState(new BlastAttack(_pBlastHornetData));
			}
			else
			{
				if (timeStand <= 0.5)
					_pBlastHornetData->blastHornet->AddVy(accelerateY);
				else if (timeStand <= 1.5)
					_pBlastHornetData->blastHornet->AddVy(-accelerateY);
				else
				{
					_pBlastHornetData->blastHornet->moveRandom = true;
					_pBlastHornetData->blastHornet->SetState(new BlastAppear(_pBlastHornetData));
				}
			}
		}
		else
		{
			if (_pBlastHornetData->blastHornet->moveUp == true)
				_pBlastHornetData->blastHornet->AddVy(-accelerateY * 10);
			else
			{
				if (timeStand > 1.0f)
					_pBlastHornetData->blastHornet->SetState(new BlastAttack(_pBlastHornetData));
			}
		}
	}
	else
		_pBlastHornetData->blastHornet->SetState(new MoveTest(_pBlastHornetData));
}

BlastState BlastStand::GetState()
{
	return BlastState::Stand;
}

void BlastStand::OnCollision(BaseObject::eSideCollision side)
{
	if (_pBlastHornetData->blastHornet->allowMove == true)
	{
		if (side == BaseObject::eSideCollision::TOP 
			|| side == BaseObject::eSideCollision::RIGHT)
		{
			_pBlastHornetData->blastHornet->moveUp = false;
			_pBlastHornetData->blastHornet->SetReverse(false);
			_pBlastHornetData->blastHornet->SetState(new BlastShooter(_pBlastHornetData));
		}
	}
}
