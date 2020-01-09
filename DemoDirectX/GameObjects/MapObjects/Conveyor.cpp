#include "Conveyor.h"
#include "../../GameComponents/Camera.h"
#include "../../GameComponents/GameCollision.h"

Conveyor::Conveyor(bool direction): BaseObject()
{
	_objectType = Enumerator::Object_Type::CONVEYOR;
	_pAnim = new Animation("Resources/MapObject/Conveyor.png", 1, 4, 128, 32, 0.1f);
	_pAnim2 = new Animation("Resources/MapObject/Conveyor1.png", 1, 4, 32, 32, 0.1f);

	_pAnim->setAnimation(0, 4, 0.1f);
	_pAnim2->setAnimation(0, 4, 0.1f);

	_isReverse = direction;
	_isDestroy = false;
	_isAllowDraw = true;
	_vx = 0;
	_vy = 0;

	if (direction)
		_velocityX = -50;
	else
		_velocityX = 50;
}

Conveyor::~Conveyor()
{
	delete _pAnim;
}

void Conveyor::update(float dt)
{
	_pAnim->update(dt);
	_pAnim2->update(dt);
}

void Conveyor::onCollision(Side_Collision side)
{}

void Conveyor::onCollision(BaseObject* obj)
{
	if (obj->getObjectType() != Enumerator::Object_Type::ROCKMAN && obj->getObjectType() != Enumerator::Object_Type::ENEMY)
		return;
	if (obj->getObjectType() == Enumerator::Object_Type::ROCKMAN)
		obj->addVx(_velocityX);
	else if (obj->getObjectType() == Enumerator::Object_Type::ENEMY)
		obj->addVx(_velocityX/2);
}

void Conveyor::draw(Camera* camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter,
	D3DCOLOR color)
{
	if (!_isAllowDraw)
		return;

	int i = 64;

	_pAnim->setReverse(_isReverse);
	_pAnim->setPosition(getBound().left + i, _posY + 8);
	_pAnim->draw(_pAnim->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);

	

	while (true)
	{
		i += 128;
		if (i >= _width)
			return;

		_pAnim->setReverse(_isReverse);
		_pAnim->setPosition(getBound().left + i, _posY + 8);
		_pAnim->draw(_pAnim->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);

		_pAnim2->setReverse(_isReverse);
		_pAnim2->setPosition(getBound().left + i - 64, _posY + 8);
		_pAnim2->draw(_pAnim2->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
	}
}
