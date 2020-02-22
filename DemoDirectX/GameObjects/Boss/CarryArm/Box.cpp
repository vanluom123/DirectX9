#include "Box.h"
#include "../../../GameDefines/GameDefine.h"
#include "../../../GameComponents/GameCollision.h"

Box::Box(bool isr)
{
	this->isR = isr;
	this->_objectType = Enumerator::Object_Type::BOX;
	this->_MaxHP = 6;
	this->_HP = this->_MaxHP;
	this->anim = new Animation("Resources/Enemies/CarryArm/box.png", 2, 1, 48, 48);
	this->pAnimationDie = new Animation(Define::EXPLOSIONS, 1, 8, 35, 30);
	this->pAnimationDie->setPause(true);
	this->_width = this->anim->getWidth();
	this->_height = this->anim->getHeight();
	this->_velocity.x = 0.0f;
	this->_velocity.y = 0.0f;
}
void Box::newObject()
{
	if (this->isR)
	{
		this->_velocity.x = 0.0f;
		this->_velocity.y = 300.0f;
		this->_Damage = 4;
	}
	else
	{
		this->_velocity.x = 0.0f;
		this->_velocity.y = 0.0f;
	}
	this->_HP = this->_MaxHP;
	this->_isDestroy = false;
	this->_position.x = this->_startPosition.x;
	this->_position.y = this->_startPosition.y;

}

Box::~Box()
{
	delete this->anim;
	delete this->pAnimationDie;
}

void Box::draw(Camera* camera, RECT r, GVec2 scale, float angle, GVec2 rotateCenter, D3DCOLOR color)
{
	if (!this->_isAllowDraw) return;

	if (!GameCollision::getInstance()->AABBCheck(camera->getBound(), getBound()))
		if (this->isR)
			newObject();

	if (!this->pAnimationDie->getPause())
	{
		this->pAnimationDie->draw(this->pAnimationDie->getPosition(), r, scale, camera->getTrans(), angle, rotateCenter, color);

		if (this->_height > 48)
		{
			int i = 24;
			while (true)
			{
				this->pAnimationDie->setPosition(this->_position.x, getBound().top + i);
				this->pAnimationDie->draw(this->pAnimationDie->getPosition(), r, scale, camera->getTrans(), angle, rotateCenter, color);

				i += 48;
				if (i > this->_height)
					break;
			}
		}
	}

	if (!this->_isDestroy)
	{
		int i = 24;
		while (true)
		{
			this->anim->setPosition(_position.x, getBound().top + i);
			this->anim->draw(anim->getPosition(), r, scale, camera->getTrans(), angle, rotateCenter, color);

			if (this->isR)
				if (!this->pAnimationDie->getPause())
					this->pAnimationDie->draw(this->pAnimationDie->getPosition(), r, scale, camera->getTrans(), angle, rotateCenter, color);

			i += 48;
			if (i > this->_height)
				return;
		}
	}
}

RECT Box::getBound()
{
	RECT bound;

	bound.left = _position.x - this->_width / 2;
	bound.top = _position.y - this->_height / 2;
	bound.right = bound.left + this->_width;
	bound.bottom = bound.top + this->_height;

	return bound;
}

void Box::update(float dt)
{
	if (!this->_isAllowDraw) return;

	this->anim->update(dt);
	this->pAnimationDie->update(dt);
	BaseObject::update(dt);
}

void Box::onCollision(Side_Collision side)
{
	if (this->_side_y == Enumerator::Side_Collision::BOTTOM && this->isR)
	{
		this->_HP = 1;
		this->isBottom = false;
		this->_isDestroy = true;
		this->pAnimationDie->setPosition(this->getPosition());
		this->pAnimationDie->setAnimation(0, 10, 0.05, false);
	}
}

void Box::onCollision(BaseObject* obj)
{
	if (obj->getObjectType() == Enumerator::Object_Type::ROCKMAN_BULLET && !this->_isDestroy)
	{
		this->_HP -= obj->getDamage();
		if (this->_HP <= 0)
		{
			this->_HP = 1;
			this->isBottom = false;
			this->_isDestroy = true;
			this->pAnimationDie->setPosition(this->getPosition());
			this->pAnimationDie->setAnimation(0, 8, 0.05f, false);
		}
	}
}