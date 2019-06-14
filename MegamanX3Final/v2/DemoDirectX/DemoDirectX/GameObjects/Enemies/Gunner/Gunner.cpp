#include "Gunner.h"
#include "../../../GameDefines/GameDefine.h"
#include "GunnerState/GunnerFall/GunnerFall.h"
#include "../../Player/Player.h"
#include "GunnerState/GunnerDie/GunnerDie.h"
#include "../../../GameComponents/GameCollision.h"
#include "../../Item/SmallBlood.h"
#include "../../Item/SmallSubtankItem.h"

Gunner::Gunner()
{
	_objectType = ENEMY;
	_pAnim = new Animation(Define::HEAD_GUNNER_SPRITE, 4, 4, 51, 45, 0.15f, D3DCOLOR_XRGB(100, 100, 100));
	_pAnimDie = new Animation(Define::EXPLOSIONS, 1, 8, 35, 30);
	_isReverse = false;
	_isAllowDraw = true;
	_isDie = false;
	_MaxHP = 6;
	_Damage = 3;
	_HP = _MaxHP;
	_curState = GUNNER_NONE;

	_pGunnerData = new GunnerData;
	_pGunnerData->gunner = this;
	_pGunnerData->gunnerState = NULL;

	this->setState(new GunnerFall(_pGunnerData));
}

void Gunner::newObject()
{
	_posX = _startx;
	_posY = _starty;
	_isReverse = false;
	_isAllowDraw = true;
	_isDie = false;
	_HP = _MaxHP;
	_curState = GUNNER_NONE;
	setState(new GunnerFall(_pGunnerData));
}

Gunner::~Gunner()
{
	delete _pAnim;
	delete _pAnimDie;
	delete _pGunnerData;
	for (auto& bullet : _listBullet)
		delete bullet;
	_listBullet.clear();
}

RECT Gunner::getBound()
{
	RECT bound;

	bound.left = _posX - 15;
	bound.right = _posX + 15;
	bound.top = _posY - 21;
	bound.bottom = _posY + 45 / 2.0f;

	return bound;
}

void Gunner::update(float dt)
{
	onNoCollisionWithBottom();

	for (auto& bullet : _listBullet)
		bullet->update(dt);

	if (_isAllowDraw == false)
		return;

	if (_isDie == false)
		_pAnim->update(dt);
	else
		_pAnimDie->update(dt);

	BaseObject::update(dt);

	if (_pGunnerData->gunnerState != NULL)
		_pGunnerData->gunnerState->Update(dt);
}

void Gunner::onCollision(eSideCollision side)
{
	if (_pGunnerData->gunnerState != NULL)
		_pGunnerData->gunnerState->OnCollision(side);
}

void Gunner::onCollision(BaseObject* obj)
{
	if (obj->getObjectType() == BaseObject::ROCK_MAN_BULLET && !_isDie)
	{
		_HP -= obj->getDamage();
		if (_HP <= 0)
		{
			_isDie = true;
			this->setState(new GunnerDie(_pGunnerData));

			int num = (rand() % 999) % 4;
			if (num == 1)
			{
				auto* item = new SmallBloodItem();
				_listBullet.push_back(item);
				item->setPosition(_posX, _posY);
				item->setObjectType(BaseObject::ITEM);
			}
			else if (num == 2)
			{
				auto* item = new SmallSubtankItem();
				_listBullet.push_back(item);
				item->setPosition(_posX, _posY);
				item->setObjectType(BaseObject::ITEM);
			}
		}
	}
}

void Gunner::onNoCollisionWithBottom()
{
	if (_side_y != BOTTOM)
	{
		switch (_curState)
		{
			case GUNNER_STAND:
			case GUNNER_ATTACK:
			case GUNNER_ATTACK_ROCKET:
			case GUNNER_ATTACK_BULLET:
				setState(new GunnerFall(_pGunnerData));
				break;
			default:
				break;
		}
	}
}

void Gunner::draw(Camera* camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter,
	D3DCOLOR color)
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
		_pAnimDie->setReverse(_isReverse);

		if (camera != NULL)
			_pAnimDie->draw(_pAnimDie->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
		else
			_pAnimDie->draw(_pAnimDie->getPosition());

		return;
	}

	_pAnim->setPosition(this->getPosition());
	_pAnim->setReverse(_isReverse);

	if (camera != NULL)
		_pAnim->draw(_pAnim->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
	else
		_pAnim->draw(_pAnim->getPosition());
}

void Gunner::ChangeAnimation(eGunnerState stateName)
{
	switch (stateName)
	{
		case GUNNER_STAND:
			{
				_pAnim->setAnimation(0, 1);
				break;
			}

		case GUNNER_ATTACK:
			{
				_pAnim->setAnimation(2, 3, 0.15f, false);
				break;
			}

		case GUNNER_ATTACK_ROCKET:
			{
				_pAnim->setAnimation(1, 3, 0.15f, false);
				break;
			}

		case GUNNER_ATTACK_BULLET:
			{
				_pAnim->setAnimation(0, 1);
				break;
			}

		case GUNNER_FALL:
			{
				_pAnim->setAnimation(0, 1);
				break;
			}

		case GUNNER_DIE:
			{
				_pAnimDie->setAnimation(0, 8, 0.05f, false);
				break;
			}

		default: break;
	}

	this->setWidth(_pAnim->getWidth());
	this->setHeight(_pAnim->getHeight());
}

void Gunner::setState(GunnerState* state)
{
	if (_curState == state->GetState())
		return;

	SAFE_DELETE(_pGunnerData->gunnerState);

	_pGunnerData->gunnerState = state;
	_curState = state->GetState();
	this->ChangeAnimation(state->GetState());
}
