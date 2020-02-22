#include "Elevator.h"
#include "../../GameComponents/GameCollision.h"
#include "../../GameDefines/GameDefine.h"
Elevator::Elevator()
{
	_objectType = Enumerator::Object_Type::ELEVATOR;
	_pAnim = new Animation(Define::Elevator, 1, 3, 96, 45, 0.1f);

	_pAnim->setAnimation(0, 1);
	_isReverse = false;
	_isDestroy = false;
	_isRun = false;
	_isAllowDraw = true;
	_velocity.x = 0;
	_velocity.y = 0;
}

Elevator::~Elevator()
{
	delete _pAnim;
}

void Elevator::update(float dt)
{
	if (!_isAllowDraw)
		return;

	if (_position.y > _startPosition.y && _position.y < _startPosition.y + 2)
	{
		_position.y = _startPosition.y;
		_isRun = false;
		_pAnim->setAnimation(0, 1);
		_velocity.x = 0;
		_velocity.y = 0;
	}

	if (getBound().top < 428.0f)
	{
		_isRun = false;
		_pAnim->setAnimation(0, 1);
		_velocity.x = 0;
		_velocity.y = 0;
	}
		
	if (_isRun)
	{
		_position.y -= 35 * dt;
	}

	_pAnim->update(dt);

	BaseObject::update(dt);
}

void Elevator::onCollision(Side_Collision side)
{
}

void Elevator::onCollision(BaseObject* obj)
{
	if (obj->getObjectType() != Enumerator::Object_Type::ROCKMAN || _isRun == true)
		return;

	_isRun = true;
	_pAnim->setAnimation(0, 3, 0.05f);
}

void Elevator::draw(Camera* camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter,
	D3DCOLOR color)
{
	if (!_isAllowDraw)
		return;

	if (!GameCollision::getInstance()->AABBCheck(camera->getBound(), getBound()))
	{
		_isRun = true;
		_pAnim->setAnimation(0, 3, 0.05f);
		_position.y = _startPosition.y + 65;
	}

	_pAnim->setReverse(_isReverse);
	_pAnim->setPosition(this->getPosition());
	if (camera)
		_pAnim->draw(_pAnim->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
	else
		_pAnim->draw(_pAnim->getPosition());

}
