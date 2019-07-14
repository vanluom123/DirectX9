#include "Elevator.h"
#include "../../GameComponents/GameCollision.h"
#include "../../GameDefines/GameDefine.h"
Elevator::Elevator()
{
	_objectType = eObject_Elevator;
	_pAnim = new Animation(Define::Elevator, 1, 3, 96, 45, 0.1f);

	_pAnim->setAnimation(0, 1);
	_isReverse = false;
	_isDie = false;
	_isRun = false;
	_isAllowDraw = true;
	_vx = 0;
	_vy = 0;
}

Elevator::~Elevator()
{
	delete _pAnim;
}

void Elevator::update(float dt)
{
	if (!_isAllowDraw)
		return;

	if (_posY > _starty && _posY < _starty + 2)
	{
		_posY = _starty;
		_isRun = false;
		_pAnim->setAnimation(0, 1);
		_vx = 0;
		_vy = 0;
	}

	if (getBound().top < 428.0f)
	{
		_isRun = false;
		_pAnim->setAnimation(0, 1);
		_vx = 0;
		_vy = 0;
	}
		
	if (_isRun)
	{
		_posY -= 35 * dt;
	}

	_pAnim->update(dt);

	BaseObject::update(dt);
}

void Elevator::onCollision(Side_Collision side)
{
}

void Elevator::onCollision(BaseObject* obj)
{
	if (obj->getObjectType() != eOject_RockMan || _isRun == true)
		return;

	_isRun = true;
	_pAnim->setAnimation(0, 3, 0.05f);
}

void Elevator::draw(Camera* camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter,
	D3DCOLOR color)
{
	if (!_isAllowDraw)
		return;

	if (!GameCollision::isCollision(camera->getBound(), getBound()))
	{
		_isRun = true;
		_pAnim->setAnimation(0, 3, 0.05f);
		_posY = _starty + 65;
	}

	_pAnim->setReverse(_isReverse);
	_pAnim->setPosition(this->getPosition());
	if (camera)
		_pAnim->draw(_pAnim->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
	else
		_pAnim->draw(_pAnim->getPosition());

}
