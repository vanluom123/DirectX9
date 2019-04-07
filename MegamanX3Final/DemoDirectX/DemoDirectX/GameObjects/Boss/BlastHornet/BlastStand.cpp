#include "BlastStand.h"
#include "BlastAttack.h"
#include "BlastAppear.h"
#include <ctime>
#include "BlastShooter.h"
#include "Move.h"

BlastStand::BlastStand(BlastHornetData* b) :BlastHornetState(b)
{
	timeStand = 0;
	if (b->GetHornet()->GetHP() > 20)
	{
		if (b->GetHornet()->allowMove == false)
		{
			if (b->GetHornet()->moveRandom == false)
			{
				b->GetHornet()->SetVx(0);
				b->GetHornet()->SetVy(20);
				accelerateY = 10;
			}
			else
			{
				b->GetHornet()->SetVx(0);
				b->GetHornet()->SetVy(0);
				accelerateY = 5;
				accelerateX = 5;
			}

			return;
		}
		if (b->GetHornet()->moveUp == true)
		{
			b->GetHornet()->SetVx(80);
			b->GetHornet()->SetVy(-80);
		}
		else
		{
			b->GetHornet()->SetVx(0);
			b->GetHornet()->SetVy(0);
		}
	}
}

BlastStand::~BlastStand()
{}

void BlastStand::Update(float dt)
{
	timeStand += dt;

	if (b->GetHornet()->GetHP() > 20)
	{
		if (b->GetHornet()->allowMove == false)
		{
			if (b->GetHornet()->moveRandom == true)
			{
				if (timeStand <= 0.65)
				{
					b->GetHornet()->AddVy(accelerateY);
					b->GetHornet()->AddVx(-accelerateX);
				}
				else if (timeStand <= 1.5)
				{
					b->GetHornet()->AddVy(-accelerateY * 1.75);
					b->GetHornet()->AddVx(-accelerateX * 0.25);
				}
				else if (timeStand <= 2.25)
				{
					b->GetHornet()->AddVy(accelerateY * 2.5);
					b->GetHornet()->AddVx(-accelerateX * 0.15);
				}
				else if (timeStand <= 3.1)
				{
					b->GetHornet()->AddVy(-accelerateY * 1.25);
					b->GetHornet()->AddVx(accelerateX * 3.25);
				}
				else if (timeStand <= 3.25)
				{
					b->GetHornet()->AddVy(-accelerateY * 2.5);
					b->GetHornet()->AddVx(-accelerateX * 3.25);
				}
				else if (timeStand <= 3.5)
				{
					b->GetHornet()->AddVy(-accelerateY * 2.5);
					b->GetHornet()->AddVx(-accelerateX * 3.25);
				}
				else if (timeStand <= 3.75)
				{
					b->GetHornet()->AddVy(-accelerateY);
					b->GetHornet()->AddVx(-accelerateX);
				}
				else if (timeStand <= 4.5)
				{
					b->GetHornet()->AddVy(accelerateY * 3.25);
					b->GetHornet()->AddVx(accelerateX);
				}
				else
					b->GetHornet()->SetState(new BlastAttack(b));
			}
			else
			{
				if (timeStand <= 0.5)
					b->GetHornet()->AddVy(accelerateY);
				else if (timeStand <= 1.5)
					b->GetHornet()->AddVy(-accelerateY);
				else
				{
					b->GetHornet()->moveRandom = true;
					b->GetHornet()->SetState(new BlastAppear(b));
				}
			}
		}
		else
		{
			if (b->GetHornet()->moveUp == true)
				b->GetHornet()->AddVy(-accelerateY * 10);
			else
			{
				if (timeStand > 1.0f)
					b->GetHornet()->SetState(new BlastAttack(b));
			}
		}
	}
	else
		b->GetHornet()->SetState(new MoveTest(b));
}

BlastState BlastStand::GetState()
{
	return BlastState::Stand;
}

void BlastStand::OnCollision(Entity::SideCollisions side)
{
	if (b->GetHornet()->allowMove == true)
	{
		if (side == Entity::SideCollisions::TOP || side == Entity::SideCollisions::RIGHT)
		{
			b->GetHornet()->moveUp = false;
			b->GetHornet()->SetReverse(false);
			b->GetHornet()->SetState(new BlastShooter(b));
		}
	}
}
