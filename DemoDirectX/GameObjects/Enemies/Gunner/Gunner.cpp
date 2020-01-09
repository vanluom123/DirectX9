#include "Gunner.h"
#include "../../../GameDefines/GameDefine.h"
#include "GunnerState/GunnerFall/GunnerFall.h"
#include "../../Player/Player.h"
#include "GunnerState/GunnerDie/GunnerDie.h"
#include "../../../GameComponents/GameCollision.h"
#include "../../Item/SmallBlood.h"
#include "../../Item/SmallSubtankItem.h"
#include "GunnerState/GunnerStand/GunnerStand.h"

Gunner::Gunner()
{
	_objectType = Enumerator::Object_Type::ENEMY;
	_pAnim = new Animation(Define::HEAD_GUNNER_SPRITE, 4, 4, 51, 45, 0.15f, D3DCOLOR_XRGB(100, 100, 100));
	_pAnimDie = new Animation(Define::EXPLOSIONS, 1, 8, 35, 30);
	_isReverse = false;
	_isAllowDraw = true;
	_isDestroy = false;
	_MaxHP = 6;
	_Damage = 3;
	_HP = _MaxHP;
	setState(new GunnerFall(this));
}

void Gunner::newObject()
{
	_posX = _startx;
	_posY = _starty;
	_isReverse = false;
	_isAllowDraw = true;
	_isDestroy = false;
	_HP = _MaxHP;
	_curState = Enumerator::Gunner_State::NONE;
	setState(new GunnerFall(this));
}

Gunner::~Gunner()
{
	delete _pAnim;
	delete _pAnimDie;
	delete m_pState;
	for (auto bullet : _listBullet)
		delete bullet;
	if (!_listBullet.empty())
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

	for (auto bullet : _listBullet)
		bullet->update(dt);

	if (_isAllowDraw)
	{
		if (!_isDestroy)
			_pAnim->update(dt);
		else
			_pAnimDie->update(dt);

		BaseObject::update(dt);

		if (m_pState)
			m_pState->Update(dt);
	}
}

void Gunner::onCollision(Side_Collision side)
{
	if (m_pState)
		m_pState->OnCollision(side);
}

void Gunner::onCollision(BaseObject* obj)
{
	if (obj->getObjectType() == Enumerator::Object_Type::ROCKMAN_BULLET && !_isDestroy)
	{
		_HP -= obj->getDamage();
		if (_HP <= 0)
		{
			_isDestroy = true;
			this->setState(new GunnerDie(this));

			int num = (rand() % 999) % 4;
			if (num == 1)
			{
				auto* item = new SmallBloodItem();
				_listBullet.push_back(item);
				item->setPosition(_posX, _posY);
				item->setObjectType(Enumerator::Object_Type::ITEM);
			}
			else if (num == 2)
			{
				auto* item = new SmallSubtankItem();
				_listBullet.push_back(item);
				item->setPosition(_posX, _posY);
				item->setObjectType(Enumerator::Object_Type::ITEM);
			}
		}
	}
}

void Gunner::onNoCollisionWithBottom()
{
	if (_side_y != Enumerator::Side_Collision::BOTTOM)
	{
		switch (_curState)
		{
			case Enumerator::Gunner_State::STAND:
			case Enumerator::Gunner_State::ATTACK:
			case Enumerator::Gunner_State::ATTACK_ROCKET:
			case Enumerator::Gunner_State::ATTACK_BULLET:
				setState(new GunnerFall(this));
				break;
			default:
				break;
		}
	}
}

void Gunner::draw(Camera* camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter,
	D3DCOLOR color)
{
	if (!_isDestroy)
	{
		if (!GameCollision::getInstance()->AABBCheck(this->getBound(), camera->getBound()))
			_isAllowDraw = false;
		else
			_isAllowDraw = true;
	}

	for (auto& bullet : _listBullet)
		bullet->draw(camera);

	if (_isAllowDraw)
	{
		if (_isDestroy)
		{
			_pAnimDie->setPosition(this->getPosition());
			_pAnimDie->setReverse(_isReverse);

			if (camera)
				_pAnimDie->draw(_pAnimDie->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
			else
				_pAnimDie->draw(_pAnimDie->getPosition());
		}
		else
		{
			_pAnim->setPosition(this->getPosition());
			_pAnim->setReverse(_isReverse);

			if (camera)
				_pAnim->draw(_pAnim->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
			else
				_pAnim->draw(_pAnim->getPosition());
		}
	}
}

void Gunner::changeAnimation(Gunner_State stateName)
{
	switch (stateName)
	{
		case Enumerator::Gunner_State::STAND:
			_pAnim->setAnimation(0, 1);
			break;

		case Enumerator::Gunner_State::ATTACK:
			_pAnim->setAnimation(2, 3, 0.15f, false);
			break;

		case Enumerator::Gunner_State::ATTACK_ROCKET:
			_pAnim->setAnimation(1, 3, 0.15f, false);
			break;

		case Enumerator::Gunner_State::ATTACK_BULLET:
			_pAnim->setAnimation(0, 1);
			break;

		case Enumerator::Gunner_State::FALL:
			_pAnim->setAnimation(0, 1);
			break;

		case Enumerator::Gunner_State::DEATH:
			_pAnimDie->setAnimation(0, 8, 0.05f, false);
			break;

		default: break;
	}

	this->setWidth(_pAnim->getWidth());
	this->setHeight(_pAnim->getHeight());
}

void Gunner::setState(GunnerState* state)
{
	if (_curState == state->getState())
		return;

	delete m_pState;
	m_pState = state;
	_curState = state->getState();
	changeAnimation(state->getState());
}
