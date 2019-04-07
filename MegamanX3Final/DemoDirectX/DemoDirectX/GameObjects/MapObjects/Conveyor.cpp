#include "Conveyor.h"
#include "../../GameComponents/Camera.h"
#include "../../GameComponents/GameCollision.h"

Conveyor::Conveyor(bool direction): Entity()
{
	tag = Entity::CONVEYOR;
	pAnimation = new Animation("Resources/MapObject/Conveyor.png", 1, 4, 128, 32, 0.1);
	pAnimation1 = new Animation("Resources/MapObject/Conveyor1.png", 1, 4, 32, 32, 0.1);

	pAnimation->setAnimation(0, 4, 0.1);
	pAnimation1->setAnimation(0, 4, 0.1);

	isReverse = direction;
	isDie = false;
	allowDraw = true;
	vx = 0;
	vy = 0;

	if (direction)
		VelocityX = -50;
	else
		VelocityX = 50;
}

Conveyor::~Conveyor()
{
	delete pAnimation;
}

void Conveyor::Update(float dt)
{
	pAnimation->update(dt);
	pAnimation1->update(dt);
}

void Conveyor::OnCollision(SideCollisions side)
{}

void Conveyor::OnCollision(Entity* obj)
{
	if (obj->GetTag() != ROCK_MAN && obj->GetTag() != ENEMY)
		return;
	if (obj->GetTag() == ROCK_MAN)
		obj->AddVx(VelocityX);
	else if (obj->GetTag() == ENEMY)
		obj->AddVx(VelocityX/2);
}

void Conveyor::Draw(Camera* camera, RECT rect, D3DXVECTOR2 scale, float angle, D3DXVECTOR2 rotationCenter,
	D3DCOLOR color)
{
	if (!allowDraw)
		return;

	int i = 64;

	pAnimation->setReverse(isReverse);
	pAnimation->setPosition(GetBound().left + i, y + 8);
	pAnimation->draw(pAnimation->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);

	

	while (true)
	{
		i += 128;
		if (i >= width)
			return;

		pAnimation->setReverse(isReverse);
		pAnimation->setPosition(GetBound().left + i, y + 8);
		pAnimation->draw(pAnimation->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);

		pAnimation1->setReverse(isReverse);
		pAnimation1->setPosition(GetBound().left + i - 64, y + 8);
		pAnimation1->draw(pAnimation1->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
	}
}
