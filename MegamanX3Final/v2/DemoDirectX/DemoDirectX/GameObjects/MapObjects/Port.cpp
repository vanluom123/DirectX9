#include "Port.h"
#include "../../GameComponents/GameCollision.h"

// INCLUDE PLAYER AND PLAYER'S STATE
#include "../Player/Player.h"
#include "../Player/GameState/StandState/StandState.h"


Port::Port()
{
	_objectType = eObject_Port;
	_pAnim = new Animation("Resources/MapObject/Port.png", 1, 17, 16, 48, 0.1f);

	_pAnim->setAnimation(0, 1);
	_isReverse = false;
	_isDie = false;
	_isAllowDraw = true;
	_isOpen = false;
	_isClose = false;
	_isMove = false;
	_HP = 0;
	_Damage = 0;
	_vx = 0.0f;
	_vy = 0.0f;
}

Port::~Port()
{
	delete _pAnim;
}

RECT Port::getBound()
{
	if (!_isOpen)
		return BaseObject::getBound();

	RECT bound;
	bound.left = _posX - _width;
	bound.right = _posX + _height;
	bound.top = _posY - _height/2;
	bound.bottom = _posY + _height / 2;
	return bound;
}

void Port::update(float dt)
{
	if (_pAnim->getPause() && _isOpen)
	{
		if (_isClose)
		{
			_HP = 2;
			_Damage = 1;
			_isOpen = false;
			_isMove = false;
			_pAnim->setAnimation(0, 1);
			
		}
		else
		{
			_isMove = true;
			_Damage = 1;
		}
	}

	_pAnim->update(dt);
}

void Port::onCollision(Side_Collision side)
{}

void Port::onCollision(BaseObject* obj)
{
	if ((obj->getObjectType() != eOject_RockMan)
		|| (_HP > 0)
		|| (obj->getBound().top < getBound().top))
	{
		return;
	}

	if ((!_isOpen) && (!_isClose))
	{
		_HP = -1;
		_isOpen = true;
		_isMove = false;
		_Damage = 0;
		_pAnim->setAnimation(0, 17, 0.1f, false);
	}

	if (_isMove)
	{
		if (obj->getReverse())
			obj->setVx(-40.0f);
		else
			obj->setVx(40.0f);

		_bound.top = _posY - _height / 2;
		_bound.bottom = _posY + _height / 2;
		_bound.left = _posX - 20;
		_bound.right = _posX + 20;

		if (!GameCollision::isCollision(_bound, obj->getBound()))
		{
			_isClose = true;
			_pAnim->setAnimation(1, 17, 0.1f, false);
			_isMove = false;
			_Damage = 0;

			// Improved DashState of Player when Player was dashing though Port
			auto* player = dynamic_cast<Player*>(obj);
			player->setState(new StandState(player));
		}
	}
	else
		obj->setVx(0.0f);
}

void Port::draw(Camera* camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter,
	D3DCOLOR color)
{
	if (_pAnim->getPause())
		return;

	_pAnim->setReverse(_isReverse);

	_pAnim->setPosition(_startx - 8, _starty);
	_pAnim->draw(_pAnim->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);

	_pAnim->setPosition(_startx + 8, _starty);
	_pAnim->draw(_pAnim->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
}
