#include "Move.h"
#include "BlastAttack.h"
#include <ctime>

MoveTest::MoveTest(BlastHornetData* b) : BlastHornetState(b)
{
	_pBlastHornetData->blastHornet->SetVx(-10);
	_pBlastHornetData->blastHornet->SetVy(10);
	timeMove = 0;
	accelerateX = 10;
	accelerateY = 10;
	count = -1;
}

MoveTest::~MoveTest()
{}

void MoveTest::Update(float dt)
{
	srand(time(nullptr));
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
			_pBlastHornetData->blastHornet->ChangeAnimation(BlastState::Shooter);
			Shoot();
		}
		else _pBlastHornetData->blastHornet->ChangeAnimation(BlastState::Move);
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
			_pBlastHornetData->blastHornet->ChangeAnimation(BlastState::Attack);
		else _pBlastHornetData->blastHornet->ChangeAnimation(BlastState::Move);

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
	}
}

BlastState MoveTest::GetState()
{
	return BlastState::Move;
}

void MoveTest::Shoot()
{
	count++;

	if (count > 3)
	{
		count = -1;
		return;
	}

	if (_pBlastHornetData->blastHornet->GetListBullet()->size() < 5)
	{
		auto* ebullet = new BlastBullet();
		_pBlastHornetData->blastHornet->GetListBullet()->push_back(ebullet);
	}

	float px = 0;
	float py = _pBlastHornetData->blastHornet->GetBound().top;

	if (count < 4)
	{
		if (count == 0) py += 5;
		else if (count == 1) py += 10;
		else if (count == 2) py += 15;
		else py += 20;

		if (_pBlastHornetData->blastHornet->GetReverse())
			px = _pBlastHornetData->blastHornet->GetBound().right;
		else
			px = _pBlastHornetData->blastHornet->GetBound().left;
	}


	_pBlastHornetData->blastHornet->GetListBullet()->at(count)->NewEntity();
}

void MoveTest::GPS()
{
	// Getting GPS the location of Player
}
