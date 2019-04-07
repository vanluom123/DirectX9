#include "Move.h"
#include "BlastAttack.h"
#include <ctime>

MoveTest::MoveTest(BlastHornetData* b) : BlastHornetState(b)
{
	b->GetHornet()->SetVx(-10);
	b->GetHornet()->SetVy(10);
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
		b->GetHornet()->AddVy(accelerateY);
		b->GetHornet()->AddVx(-accelerateX);
		if (b->GetHornet()->GetVy() >= 300)
			b->GetHornet()->SetVy(300);
	}
	else if (timeMove <= 0.75)
	{
		b->GetHornet()->AddVy(-accelerateY * 2);
		b->GetHornet()->AddVx(accelerateX / 1.5);
		if (b->GetHornet()->GetVy() <= -300)
			b->GetHornet()->SetVy(-300);
	}
	else if (timeMove <= 1.5)
	{
		if(timeMove <= 1.45)
		{
			b->GetHornet()->ChangeAnimation(BlastState::Shooter);
			Shoot();
		}
		else b->GetHornet()->ChangeAnimation(BlastState::Move);
	}
	else if (timeMove <= 1.975)
	{
		b->GetHornet()->AddVy(accelerateY * 1.5);
		b->GetHornet()->AddVx(-accelerateX / 2);
		if (b->GetHornet()->GetVy() >= 300)
			b->GetHornet()->SetVy(300);
	}
	else if (timeMove <= 2.5)
	{
		b->GetHornet()->AddVy(-accelerateY / 2);
		b->GetHornet()->AddVx(accelerateX * 2);
		if (b->GetHornet()->GetVy() <= -300)
			b->GetHornet()->SetVy(-300);
	}
	else if (timeMove <= 3)
	{
		if (timeMove == 2.75)
			GPS();

		b->GetHornet()->AddVy(-accelerateY * 2);
		b->GetHornet()->AddVx(accelerateX / 2);
		if (b->GetHornet()->GetVy() <= -300)
			b->GetHornet()->SetVy(-300);
	}
	else if (timeMove <= 3.5)
	{
		b->GetHornet()->AddVy(-accelerateY / 10);
		b->GetHornet()->AddVx(-accelerateX);
		if (b->GetHornet()->GetVy() <= -300)
			b->GetHornet()->SetVy(-300);
	}
	else if (timeMove <= 5)
	{
		/*b->setVy(1);
		b->addVx(-accelerateX);*/
		b->GetHornet()->AddVy(rand() % 5);
		b->GetHornet()->AddVx(-(rand() % 15));
	}
	else if (timeMove <= 5.75)
	{
		if(timeMove <= 5.75)
			b->GetHornet()->ChangeAnimation(BlastState::Attack);
		else b->GetHornet()->ChangeAnimation(BlastState::Move);

		b->GetHornet()->SetVx(1);
		b->GetHornet()->AddVy(accelerateY);
		if (b->GetHornet()->GetVy() >= 300)
			b->GetHornet()->SetVy(300);
	}
	else if (timeMove <= 6.5)
	{
	/*	b->setVy(1);
		b->addVx(accelerateX);*/
		b->GetHornet()->AddVy(rand() % 5);
		b->GetHornet()->AddVx(rand() % 15);
	}
	else if (timeMove <= 7)
	{
		b->GetHornet()->AddVy(-accelerateY * 2);
		b->GetHornet()->AddVx(-accelerateX / 2);
		if (b->GetHornet()->GetVy() <= -300)
			b->GetHornet()->SetVy(-300);
	}
	else
	{
		b->GetHornet()->SetVx(0);
		b->GetHornet()->SetVy(0);
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

	if (b->GetHornet()->GetListBullet()->size() < 5)
	{
		auto* ebullet = new BlastBullet();
		b->GetHornet()->GetListBullet()->push_back(ebullet);
	}

	float px = 0;
	float py = b->GetHornet()->GetBound().top;

	if (count < 4)
	{
		if (count == 0) py += 5;
		else if (count == 1) py += 10;
		else if (count == 2) py += 15;
		else py += 20;

		if (b->GetHornet()->GetReverse())
			px = b->GetHornet()->GetBound().right;
		else
			px = b->GetHornet()->GetBound().left;
	}


	b->GetHornet()->GetListBullet()->at(count)->NewEntity();
}

void MoveTest::GPS()
{
	//GPS location of Rockman
}
