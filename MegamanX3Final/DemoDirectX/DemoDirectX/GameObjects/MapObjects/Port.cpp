#include "Port.h"
#include "../../GameComponents/GameCollision.h"

Port::Port()
{
	tag = Entity::PORT;
	pAnimation = new Animation("Resources/MapObject/Port.png", 1, 17, 16, 48, 0.1);

	pAnimation->setAnimation(0, 1);
	isReverse = false;
	isDie = false;
	allowDraw = true;
	isOpen = false;
	isClose = false;
	isMove = false;
	HP = 0;
	Damage = 0;
	vx = 0;
	vy = 0;
}

Port::~Port()
{
	delete pAnimation;
}

RECT Port::GetBound()
{
	if (!isOpen)
		return Entity::GetBound();

	RECT r;
	r.left = x - width;
	r.right = x + height;
	r.top = y - height/2;
	r.bottom = y + height / 2;
	return r;
}

void Port::Update(float dt)
{
	if (pAnimation->getPause() && isOpen)
	{
		if (isClose)
		{
			HP = 2;
			Damage = 1;
			isOpen = false;
			isMove = false;
			pAnimation->setAnimation(0, 1);
			
		}
		else
		{
			isMove = true;
			Damage = 1;
		}
	}

	pAnimation->update(dt);
}

void Port::OnCollision(SideCollisions side)
{}

void Port::OnCollision(Entity* obj)
{
	if (obj->GetTag() != ROCK_MAN || HP > 0 || obj->GetBound().top < GetBound().top)
		return;

	if (!isOpen && !isClose)
	{
		HP = -1;
		isOpen = true;
		isMove = false;
		Damage = 0;
		pAnimation->setAnimation(0, 17, 0.1, false);
	}

	if (isMove)
	{
		if (obj->GetReverse())
			obj->SetVx(-40);
		else
			obj->SetVx(40);

		bound.top = y - height / 2;
		bound.bottom = y + height / 2;
		bound.left = x - 20;
		bound.right = x + 20;

		if (!GameCollision::IsCollision(bound, obj->GetBound()))
		{
			isClose = true;
			pAnimation->setAnimation(1, 17, 0.1, false);
			isMove = false;
			Damage = 0;
		}
	}
	else
		obj->SetVx(0);
	
}

void Port::Draw(Camera* camera, RECT rect, D3DXVECTOR2 scale, float angle, D3DXVECTOR2 rotationCenter,
	D3DCOLOR color)
{
	if (pAnimation->getPause())
		return;
	pAnimation->setReverse(isReverse);

	pAnimation->setPosition(startx - 8, starty);
	pAnimation->draw(pAnimation->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);

	pAnimation->setPosition(startx + 8, starty);
	pAnimation->draw(pAnimation->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
}
