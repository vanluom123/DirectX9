#include "Helit.h"
#include "../../../GameDefines/GameDefine.h"
#include "HelitState/HelitDie/HelitDie.h"
#include "HelitState/HelitStand/HelitStand.h"
#include "../../../GameComponents/GameCollision.h"
#include "../../Item/SmallBlood.h"
#include "../../Item/SmallSubtankItem.h"

Helit::Helit()
{
	_objectType = ENEMY;
	_pAnim = new Animation(Define::HELIT_SPRITE_SHEET, 2, 4, 39, 37, 0.1f, D3DCOLOR_XRGB(100, 100, 100));
	_pAnimDie = new Animation(Define::EXPLOSIONS, 1, 8, 35, 30);
	_isReverse = false;
	_isDie = false;
	_isAllowDraw = true;
	_MaxHP = 4;
	_HP = _MaxHP;
	_Damage = 3;
	_currentState = HELIT_UNKNOWN;

	_pHelitData = new HelitData;
	_pHelitData->helit = this;
	_pHelitData->helitState = NULL;

	this->setState(new HelitStand(_pHelitData));
}

void Helit::newObject()
{
	_posX = _startx;
	_posY = _starty;

	_isReverse = false;
	_isDie = false;
	_isAllowDraw = true;
	_HP = _MaxHP;
	_currentState = HELIT_UNKNOWN;
	setState(new HelitStand(_pHelitData));
}

Helit::~Helit()
{
	delete _pHelitData;
	delete _pAnim;
	delete _pAnimDie;
	for (auto& bullet : _listBullet)
		delete bullet;
	_listBullet.clear();
}

RECT Helit::getBound()
{
	RECT bound;

	bound.left = _posX - 19;
	bound.right = _posX + 19;
	bound.top = _posY - 18;
	bound.bottom = _posY + 37 / 2.0f;

	return bound;
}

void Helit::update(float dt)
{
	for (auto& bullet : _listBullet)
		bullet->update(dt);

	if (_isAllowDraw == false)
		return;

	BaseObject::update(dt);

	if (_isDie == true)
		_pAnimDie->update(dt);
	else
		_pAnim->update(dt);

	if (_pHelitData->helitState != NULL)
		_pHelitData->helitState->update(dt);
}

void Helit::onCollision(BaseObject* obj)
{
	if (obj->getObjectType() == BaseObject::ROCK_MAN_BULLET && _isDie == false)
	{
		_HP -= obj->getDamage();
		if (_HP <= 0)
		{
			_isDie = true;
			setState(new HelitDie(_pHelitData));
		}

		//
		int num = (rand() % 999) % 4;
		if (num == 1)
		{
			auto item = new SmallBloodItem();
			_listBullet.push_back(item);
			item->setPosition(_posX, _posY);
			item->setObjectType(BaseObject::ITEM);
		}
		else if (num == 2)
		{
			auto item = new SmallSubtankItem();
			_listBullet.push_back(item);
			item->setPosition(_posX, _posY);
			item->setObjectType(BaseObject::ITEM);
		}
	}
}

void Helit::draw(Camera* camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter, D3DCOLOR color)
{
	if (_isDie == false)
	{
		if (GameCollision::isCollision(this->getBound(), camera->getBound()) == false)
			_isAllowDraw = false;
		else
			_isAllowDraw = true;
	}

	for (auto& bullet : _listBullet)
		bullet->draw(camera);

	if (_isAllowDraw == false)
		return;

	if (_isDie == true)
	{
		_pAnimDie->setPosition(this->getPosition());

		if (camera != NULL)
			_pAnimDie->draw(_pAnimDie->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
		else
			_pAnimDie->draw(_pAnimDie->getPosition());
	}
	else
	{
		_pAnim->setReverse(_isReverse);
		_pAnim->setPosition(this->getPosition());

		if (camera != NULL)
			_pAnim->draw(_pAnim->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
		else
			_pAnim->draw(_pAnim->getPosition());
	}
}

void Helit::setState(HelitState* newState)
{
	if (_currentState == newState->getState())
		return;

	SAFE_DELETE(_pHelitData->helitState);

	_pHelitData->helitState = newState;
	_currentState = newState->getState();
	changeAnimation(newState->getState());
}

void Helit::changeAnimation(eHelitState state)
{
	switch (state)
	{
		case HELIT_STAND:
			{
				_pAnim->setAnimation(0, 4, 0.15f);
				_pAnim->setFrame(39, 36);
				break;
			}

		case HELIT_ATTACK:
			{
				_pAnim->setAnimation(1, 4, 0.15f);
				_pAnim->setFrame(39, 36);
				break;
			}

		case HELIT_DIE:
			{
				_pAnimDie->setAnimation(0, 8, 0.05f, false);
				break;
			}

		default: break;
	}

	_width = _pAnim->getWidth();
	_height = _pAnim->getHeight();
}