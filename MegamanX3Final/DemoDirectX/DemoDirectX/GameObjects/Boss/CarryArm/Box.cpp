#include "Box.h"
#include "../../../GameDefines/GameDefine.h"
#include "../../../GameComponents/GameCollision.h"

Box::Box(bool isr)
{
	isR = isr;
	tag     = Tag::BOX;
	MaxHP	= 6;
	HP		= MaxHP;
	anim    = new Animation("Resources/Enemies/CarryArm/box.png", 2, 1, 48, 48);
	pAnimationDie = new Animation(Define::EXPLOSIONS, 1, 8, 35, 30);
	pAnimationDie->setPause(true);
	width    = anim->getWidth();
	height   = anim->getHeight();
	vx = 0;
	vy = 0;
}
void Box::NewEntity()
{
	if (isR)
	{
		vx = 0;
		vy = 300;
		Damage = 4;
	}
	else
	{
		vx = 0;
		vy = 0;
	}
	HP = MaxHP;
	isDie = false;
	x = startx;
	y = starty;

}

Box::~Box()
{
	delete anim;
	delete pAnimationDie;
}

void Box::Draw(Camera* camera, RECT r, D3DXVECTOR2 scale, float angle, D3DXVECTOR2 rotateCenter, D3DCOLOR color)
{
	if (!allowDraw) return;

	if (!GameCollision::IsCollision(camera->getBound(), GetBound()))
		if (isR)
			NewEntity();

	if (!pAnimationDie->getPause())
	{
		pAnimationDie->draw(pAnimationDie->getPosition(), r, scale, camera->getTrans(), angle, rotateCenter, color);

		if (height > 48)
		{
			int i = 24;
			while (true)
			{
				pAnimationDie->setPosition(x, GetBound().top + i);
				pAnimationDie->draw(pAnimationDie->getPosition(), r, scale, camera->getTrans(), angle, rotateCenter, color);

				i += 48;
				if (i > height)
					break;
			}
		}
	}

	if (!isDie)
	{
		int i = 24;
		while (true)
		{
			anim->setPosition(x, GetBound().top + i);
			anim->draw(anim->getPosition(), r, scale, camera->getTrans(), angle, rotateCenter, color);

			if (isR)
				if (!pAnimationDie->getPause())
					pAnimationDie->draw(pAnimationDie->getPosition(), r, scale, camera->getTrans(), angle, rotateCenter, color);

			i += 48;
			if (i > height)
				return;
		}
	}
}

RECT Box::GetBound()
{
	RECT r;

	r.left = x - (float)width / 2;
	r.top = y - (float)height / 2;
	r.right = r.left + width;
	r.bottom = r.top + height;

	return r;
}

void Box::Update(float dt)
{
	if (!allowDraw) return;

	anim->update(dt);
	pAnimationDie->update(dt);
	Entity::Update(dt);
}

void Box::OnCollision(SideCollisions side)
{
	if (sideY == Entity::BOTTOM && isR)
	{
		HP = 1;
		isBottom = false;
		isDie = true;
		pAnimationDie->setPosition(GetPosition());
		pAnimationDie->setAnimation(0, 10, 0.05, false);
	}
}

void Box::OnCollision(Entity* obj)
{
	
	if (obj->GetTag() == Tag::ROCK_MAN_BULLET && !isDie)
	{
		HP -= obj->GetDamage();
		if (HP <= 0)
		{
			HP = 1;
			isBottom = false;
			isDie = true;
			pAnimationDie->setPosition(GetPosition());
			pAnimationDie->setAnimation(0, 8, 0.05, false);
		}
	}
}