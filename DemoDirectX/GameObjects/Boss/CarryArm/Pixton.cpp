#include "Pixton.h"
#include "../../../GameComponents/Camera.h"


Pixton::Pixton()
{
	_isBottom = false;
	_pAnim = new Animation("Resources/Enemies/CarryArm/x3_subboss_carryarm_39.png", 1, 1, 144, 88);
	this->setWidth(_pAnim->getWidth());
	this->setHeight(_pAnim->getHeight());
	_pixtonPosY = 0;
}

Pixton::~Pixton()
{
	delete _pAnim;
}

RECT Pixton::getBound()
{
	RECT bound;
	bound.left = _posX - _width / 2;
	bound.right = _posX + _width / 2;
	bound.bottom = _posY + _height / 2;
	bound.top = bound.bottom -16;
	return bound;
}

void Pixton::draw(Camera * camera, RECT r, GVec2 scale, float angle, GVec2 rotate, D3DCOLOR color)
{
	if (!_isAllowDraw)
		return;

	_pAnim->setPosition(getPosition());
	if (camera)
		_pAnim->draw(_pAnim->getPosition(), r, scale, camera->getTrans(), angle, rotate, color);
	else
		_pAnim->draw(_pAnim->getPosition());
}

void Pixton::onCollision(Side_Collision side)
{
}

void Pixton::update(float gameTime)
{
	if (!_isAllowDraw)
		return;

	_pAnim->update(gameTime);
	BaseObject::update(gameTime);
}

bool Pixton::MoveDown(float gameTime, float x, float y)
{
	if (!_isBottom)
	{
		_pixtonPosY += 40 * gameTime;
		if (_pixtonPosY >= 88)
		{
			_isBottom = true;
			_pixtonPosY = 88;
		}
		setPosition(x + 55, y + _pixtonPosY);
	}
	return !_isBottom;
}

bool Pixton::MoveUp(float gameTime, float x, float y)
{
	if (_isBottom)
	{
		_pixtonPosY -= 40 * gameTime;
		if (_pixtonPosY <= 0)
		{
			_isBottom = false;
			_pixtonPosY = 0;
			_vy = -40.0f;
		}
		setPosition(x + 56, y + _pixtonPosY);
	}
	return _isBottom;
}
