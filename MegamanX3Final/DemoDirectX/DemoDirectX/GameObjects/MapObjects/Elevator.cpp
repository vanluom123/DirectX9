#include "Elevator.h"
#include "../../GameComponents/GameCollision.h"
#include "../../GameDefines/GameDefine.h"
Elevator::Elevator()
{
	tag = Entity::ELEVATOR;
	pAnimation = new Animation(Define::Elevator, 1, 3, 96, 45, 0.1);

	pAnimation->setAnimation(0, 1);
	isReverse = false;
	isDie = false;
	isRun = false;
	allowDraw = true;
	vx = 0;
	vy = 0;
}

Elevator::~Elevator()
{
	delete pAnimation;
}

void Elevator::Update(float dt)
{
	if (!allowDraw)
		return;

	if (y > starty && y < starty + 2)
	{
		y = starty;
		isRun = false;
		pAnimation->setAnimation(0, 1);
		vx = 0;
		vy = 0;
	}

	if (GetBound().top < 428.0f)
	{
		isRun = false;
		pAnimation->setAnimation(0, 1);
		vx = 0;
		vy = 0;
	}
		
	if (isRun)
	{
		y -= 35 * dt;
	}

	pAnimation->update(dt);

	Entity::Update(dt);
}

void Elevator::OnCollision(SideCollisions side)
{
}

void Elevator::OnCollision(Entity* obj)
{
	if (obj->GetTag() != ROCK_MAN || isRun == true)
		return;

	isRun = true;
	pAnimation->setAnimation(0, 3, 0.05);
}

void Elevator::Draw(Camera* camera, RECT rect, D3DXVECTOR2 scale, float angle, D3DXVECTOR2 rotationCenter,
	D3DCOLOR color)
{
	if (!allowDraw)
		return;

	if (!GameCollision::IsCollision(camera->getBound(), GetBound()))
	{
		isRun = true;
		pAnimation->setAnimation(0, 3, 0.05);
		y = starty + 65;
	}

	pAnimation->setReverse(isReverse);
	pAnimation->setPosition(this->GetPosition());
	if (camera)
		pAnimation->draw(pAnimation->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
	else
		pAnimation->draw(pAnimation->getPosition());

}
