#include "BlastStand.h"
#include "BlastAttack.h"
#include "BlastAppear.h"
#include <ctime>
#include "BlastShooter.h"
#include "Move.h"

BlastStand::BlastStand(BlastHornetData* b) :BlastHornetState(b)
{
	m_timeStand = 0;
	if (m_blastHornetData->blastHornet->GetHP() > 20)
	{
		if (m_blastHornetData->blastHornet->m_isAllowMove == false)
		{
			if (m_blastHornetData->blastHornet->m_isMoveRandom == false)
			{
				m_blastHornetData->blastHornet->SetVx(0);
				m_blastHornetData->blastHornet->SetVy(20);
				m_accelerateY = 10;
			}
			else
			{
				m_blastHornetData->blastHornet->SetVx(0);
				m_blastHornetData->blastHornet->SetVy(0);
				m_accelerateY = 5;
				m_accelerateX = 5;
			}

			return;
		}
		if (m_blastHornetData->blastHornet->m_isAllowMoveUp == true)
		{
			m_blastHornetData->blastHornet->SetVx(80);
			m_blastHornetData->blastHornet->SetVy(-80);
		}
		else
		{
			m_blastHornetData->blastHornet->SetVx(0);
			m_blastHornetData->blastHornet->SetVy(0);
		}
	}
}

BlastStand::~BlastStand()
{}

void BlastStand::Update(float dt)
{
	m_timeStand += dt;

	if (m_blastHornetData->blastHornet->GetHP() > 20)
	{
		if (m_blastHornetData->blastHornet->m_isAllowMove == false)
		{
			if (m_blastHornetData->blastHornet->m_isMoveRandom == true)
			{
				if (m_timeStand <= 0.65)
				{
					m_blastHornetData->blastHornet->AddVy(m_accelerateY);
					m_blastHornetData->blastHornet->AddVx(-m_accelerateX);
				}
				else if (m_timeStand <= 1.5)
				{
					m_blastHornetData->blastHornet->AddVy(-m_accelerateY * 1.75);
					m_blastHornetData->blastHornet->AddVx(-m_accelerateX * 0.25);
				}
				else if (m_timeStand <= 2.25)
				{
					m_blastHornetData->blastHornet->AddVy(m_accelerateY * 2.5);
					m_blastHornetData->blastHornet->AddVx(-m_accelerateX * 0.15);
				}
				else if (m_timeStand <= 3.1)
				{
					m_blastHornetData->blastHornet->AddVy(-m_accelerateY * 1.25);
					m_blastHornetData->blastHornet->AddVx(m_accelerateX * 3.25);
				}
				else if (m_timeStand <= 3.25)
				{
					m_blastHornetData->blastHornet->AddVy(-m_accelerateY * 2.5);
					m_blastHornetData->blastHornet->AddVx(-m_accelerateX * 3.25);
				}
				else if (m_timeStand <= 3.5)
				{
					m_blastHornetData->blastHornet->AddVy(-m_accelerateY * 2.5);
					m_blastHornetData->blastHornet->AddVx(-m_accelerateX * 3.25);
				}
				else if (m_timeStand <= 3.75)
				{
					m_blastHornetData->blastHornet->AddVy(-m_accelerateY);
					m_blastHornetData->blastHornet->AddVx(-m_accelerateX);
				}
				else if (m_timeStand <= 4.5)
				{
					m_blastHornetData->blastHornet->AddVy(m_accelerateY * 3.25);
					m_blastHornetData->blastHornet->AddVx(m_accelerateX);
				}
				else
					m_blastHornetData->blastHornet->SetState(new BlastAttack(m_blastHornetData));
			}
			else
			{
				if (m_timeStand <= 0.5)
					m_blastHornetData->blastHornet->AddVy(m_accelerateY);
				else if (m_timeStand <= 1.5)
					m_blastHornetData->blastHornet->AddVy(-m_accelerateY);
				else
				{
					m_blastHornetData->blastHornet->m_isMoveRandom = true;
					m_blastHornetData->blastHornet->SetState(new BlastAppear(m_blastHornetData));
				}
			}
		}
		else
		{
			if (m_blastHornetData->blastHornet->m_isAllowMoveUp == true)
				m_blastHornetData->blastHornet->AddVy(-m_accelerateY * 10);
			else
			{
				if (m_timeStand > 1.0f)
					m_blastHornetData->blastHornet->SetState(new BlastAttack(m_blastHornetData));
			}
		}
	}
	else
		m_blastHornetData->blastHornet->SetState(new SineMovement(m_blastHornetData));
}

BlastHornet::eBlastState BlastStand::GetState()
{
	return BlastHornet::BLAST_STATE_STAND;
}

void BlastStand::OnCollision(BaseObject::eSideCollision side)
{
	if (m_blastHornetData->blastHornet->m_isAllowMove == true)
	{
		if (side == BaseObject::eSideCollision::SIDE_COLLISION_TOP 
			|| side == BaseObject::eSideCollision::SIDE_COLLISION_RIGHT)
		{
			m_blastHornetData->blastHornet->m_isAllowMoveUp = false;
			m_blastHornetData->blastHornet->SetReverse(false);
			m_blastHornetData->blastHornet->SetState(new BlastShooter(m_blastHornetData));
		}
	}
}
