#include "Box.h"
#include "../../../GameDefines/GameDefine.h"
#include "../../../GameComponents/GameCollision.h"

Box::Box(bool isr)
{
	isR = isr;
	_objectType = eObject_Box;
	_MaxHP = 6;
	_HP = _MaxHP;
	anim = new Animation("Resources/Enemies/CarryArm/box.png", 2, 1, 48, 48);
	pAnimationDie = new Animation(Define::EXPLOSIONS, 1, 8, 35, 30);
	pAnimationDie->setPause(true);
	_width = anim->getWidth();
	_height = anim->getHeight();
	_vx = 0;
	_vy = 0;
}
void Box::newObject()
{
	if (isR)
	{
		_vx = 0;
		_vy = 300;
		_Damage = 4;
	}
	else
	{
		_vx = 0;
		_vy = 0;
	}
	_HP = _MaxHP;
	_isDie = false;
	_posX = _startx;
	_posY = _starty;

}

Box::~Box()
{
	delete anim;
	delete pAnimationDie;
}

void Box::draw(Camera* camera, RECT r, GVec2 scale, float angle, GVec2 rotateCenter, D3DCOLOR color)
{
	if (!_isAllowDraw) return;

	if (!GameCollision::isCollision(camera->getBound(), getBound()))
		if (isR)
			newObject();

	if (!pAnimationDie->getPause())
	{
		pAnimationDie->draw(pAnimationDie->getPosition(), r, scale, camera->getTrans(), angle, rotateCenter, color);

		if (_height > 48)
		{
			int i = 24;
			while (true)
			{
				pAnimationDie->setPosition(_posX, getBound().top + i);
				pAnimationDie->draw(pAnimationDie->getPosition(), r, scale, camera->getTrans(), angle, rotateCenter, color);

				i += 48;
				if (i > _height)
					break;
			}
		}
	}

	if (!_isDie)
	{
		int i = 24;
		while (true)
		{
			anim->setPosition(_posX, getBound().top + i);
			anim->draw(anim->getPosition(), r, scale, camera->getTrans(), angle, rotateCenter, color);

			if (isR)
				if (!pAnimationDie->getPause())
					pAnimationDie->draw(pAnimationDie->getPosition(), r, scale, camera->getTrans(), angle, rotateCenter, color);

			i += 48;
			if (i > _height)
				return;
		}
	}
}

RECT Box::getBound()
{
	RECT bound;

	bound.left = _posX - _width / 2;
	bound.top = _posY - _height / 2;
	bound.right = bound.left + _width;
	bound.bottom = bound.top + _height;

	return bound;
}

void Box::update(float dt)
{
	if (!_isAllowDraw) return;

	anim->update(dt);
	pAnimationDie->update(dt);
	BaseObject::update(dt);
}

void Box::onCollision(Side_Collision side)
{
	if (_side_y == eSide_Bottom && isR)
	{
		_HP = 1;
		isBottom = false;
		_isDie = true;
		pAnimationDie->setPosition(getPosition());
		pAnimationDie->setAnimation(0, 10, 0.05, false);
	}
}

void Box::onCollision(BaseObject* obj)
{

	if (obj->getObjectType() == eObject_RockMan_Bullet && !_isDie)
	{
		_HP -= obj->getDamage();
		if (_HP <= 0)
		{
			_HP = 1;
			isBottom = false;
			_isDie = true;
			pAnimationDie->setPosition(getPosition());
			pAnimationDie->setAnimation(0, 8, 0.05, false);
		}
	}
}