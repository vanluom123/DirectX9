#include "Move.h"
#include "BlastAttack.h"
#include <ctime>

SineMovement::SineMovement(BlastHornetData* b) : BlastHornetState(b)
{
	m_blastHornetData->blastHornet->SetVx(-10);
	m_blastHornetData->blastHornet->SetVy(10);
	m_timeMove = 0;
	m_accelerateX = 10;
	m_accelerateY = 10;
	m_count = -1;
}

SineMovement::~SineMovement()
{}

void SineMovement::Update(float dt)
{
	/*srand(time(nullptr));
	timeMove += dt;

	if (timeMove <= 0.45)
	{
		_pBlastHornetData->blastHornet->AddVy(accelerateY);
		_pBlastHornetData->blastHornet->AddVx(-accelerateX);

		if (_pBlastHornetData->blastHornet->GetVy() >= 300)
			_pBlastHornetData->blastHornet->SetVy(300);
	}
	else if (timeMove <= 0.75)
	{
		_pBlastHornetData->blastHornet->AddVy(-accelerateY * 2);
		_pBlastHornetData->blastHornet->AddVx(accelerateX / 1.5);

		if (_pBlastHornetData->blastHornet->GetVy() <= -300)
			_pBlastHornetData->blastHornet->SetVy(-300);
	}
	else if (timeMove <= 1.5)
	{
		if(timeMove <= 1.45)
		{
			_pBlastHornetData->blastHornet->ChangeAnimation(eBlastState::BLAST_STATE_SHOOTER);
			Shoot();
		}
		else _pBlastHornetData->blastHornet->ChangeAnimation(eBlastState::BLAST_STATE_MOVE);
	}
	else if (timeMove <= 1.975)
	{
		_pBlastHornetData->blastHornet->AddVy(accelerateY * 1.5);
		_pBlastHornetData->blastHornet->AddVx(-accelerateX / 2);

		if (_pBlastHornetData->blastHornet->GetVy() >= 300)
			_pBlastHornetData->blastHornet->SetVy(300);
	}
	else if (timeMove <= 2.5)
	{
		_pBlastHornetData->blastHornet->AddVy(-accelerateY / 2);
		_pBlastHornetData->blastHornet->AddVx(accelerateX * 2);

		if (_pBlastHornetData->blastHornet->GetVy() <= -300)
			_pBlastHornetData->blastHornet->SetVy(-300);
	}
	else if (timeMove <= 3)
	{
		if (timeMove == 2.75)
			this->GPS();

		_pBlastHornetData->blastHornet->AddVy(-accelerateY * 2);
		_pBlastHornetData->blastHornet->AddVx(accelerateX / 2);

		if (_pBlastHornetData->blastHornet->GetVy() <= -300)
			_pBlastHornetData->blastHornet->SetVy(-300);
	}
	else if (timeMove <= 3.5)
	{
		_pBlastHornetData->blastHornet->AddVy(-accelerateY / 10);
		_pBlastHornetData->blastHornet->AddVx(-accelerateX);
		if (_pBlastHornetData->blastHornet->GetVy() <= -300)
			_pBlastHornetData->blastHornet->SetVy(-300);
	}
	else if (timeMove <= 5)
	{
		_pBlastHornetData->blastHornet->AddVy(rand() % 5);
		_pBlastHornetData->blastHornet->AddVx(-(rand() % 15));
	}
	else if (timeMove <= 5.75)
	{
		if(timeMove <= 5.75)
			_pBlastHornetData->blastHornet->ChangeAnimation(eBlastState::BLAST_STATE_ATTACK);
		else _pBlastHornetData->blastHornet->ChangeAnimation(eBlastState::BLAST_STATE_MOVE);

		_pBlastHornetData->blastHornet->SetVx(1);
		_pBlastHornetData->blastHornet->AddVy(accelerateY);

		if (_pBlastHornetData->blastHornet->GetVy() >= 300)
			_pBlastHornetData->blastHornet->SetVy(300);
	}
	else if (timeMove <= 6.5)
	{
		_pBlastHornetData->blastHornet->AddVy(rand() % 5);
		_pBlastHornetData->blastHornet->AddVx(rand() % 15);
	}
	else if (timeMove <= 7)
	{
		_pBlastHornetData->blastHornet->AddVy(-accelerateY * 2);
		_pBlastHornetData->blastHornet->AddVx(-accelerateX / 2);

		if (_pBlastHornetData->blastHornet->GetVy() <= -300)
			_pBlastHornetData->blastHornet->SetVy(-300);
	}
	else
	{
		_pBlastHornetData->blastHornet->SetVx(0);
		_pBlastHornetData->blastHornet->SetVy(0);
		timeMove = 0;
	}*/

	double x = m_blastHornetData->blastHornet->GetPosition().x + newPosX(1, 1, GetTickCount64());
	double y = m_blastHornetData->blastHornet->GetPosition().y + newPosY(GetTickCount64(), 300.0f);

	m_blastHornetData->blastHornet->SetPosition(float(x), float(y));
}

BlastHornet::eBlastState SineMovement::GetState()
{
	return BlastHornet::BLAST_STATE_MOVE;
}

void SineMovement::Shoot()
{
	m_count++;

	if (m_count > 3)
	{
		m_count = -1;
		return;
	}

	if (m_blastHornetData->blastHornet->GetListBullet()->size() < 5)
	{
		auto* ebullet = new BlastBullet();
		m_blastHornetData->blastHornet->GetListBullet()->push_back(ebullet);
	}

	float px = 0;
	float py = m_blastHornetData->blastHornet->GetBound().top;

	if (m_count < 4)
	{
		if (m_count == 0) py += 5;
		else if (m_count == 1) py += 10;
		else if (m_count == 2) py += 15;
		else py += 20;

		if (m_blastHornetData->blastHornet->GetReverse())
			px = m_blastHornetData->blastHornet->GetBound().right;
		else
			px = m_blastHornetData->blastHornet->GetBound().left;
	}

	m_blastHornetData->blastHornet->GetListBullet()->at(m_count)->NewEntity();
}

void SineMovement::GPS()
{
	// Getting GPS the location of Player
}

void SineMovement::MoveRight()
{

}

void SineMovement::MoveLeft()
{
}

double SineMovement::newPosX(int amplitude, int frequency, int milliSecs)
{
	double xPos = amplitude * sin(2 * 3.14 * frequency * (milliSecs / 1000));
	return xPos;
}

double SineMovement::newPosY(int milliSecs, int speed)
{
	double yPos = double(milliSecs / 1000) * speed;
	return yPos;
}
