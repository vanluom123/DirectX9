#include "Banger.h"
#include "../../../GameDefines/GameDefine.h"
#include "BangerState/BangerFall/BangerFall.h"
#include "BangerState/BangerDie/BangerDie.h"
#include "BangerState/BangerStand/BangerStand.h"
#include "../../../GameComponents/GameCollision.h"
#include "../../Item/SmallBlood.h"
#include "../../Item/SmallSubtankItem.h"

Banger::Banger()
{
	_objectType = ENEMY;
	_anim_die = new Animation(Define::EXPLOSIONS, 1, 8, 35, 30);
	_current_anim = new Animation(Define::NOTOR_BANGER_SPRITE, 3, 4, 48, 48);
	_MaxHP = 4;
	_HP = _MaxHP;
	_Damage = 3;
	_isReverse = true;
	_isAllowDraw = true;
	_isDie = false;
	_currentState = BANGER_NONE;

	_pBangerData = new BangerData;
	_pBangerData->banger = this;
	_pBangerData->bangerState = NULL;

	this->setState(new BangerFall(_pBangerData));
}

void Banger::newObject()
{
	_posX = _startx;
	_posY = _starty;
	_HP = _MaxHP;
	_isReverse = true;
	_isAllowDraw = true;
	_isDie = false;
	_currentState = BANGER_NONE;
	this->setState(new BangerFall(_pBangerData));
}

Banger::~Banger()
{
	delete _pBangerData;
	delete _current_anim;
	delete _anim_die;
	for (auto& bullet : _listBullet)
		delete bullet;
	_listBullet.clear();
}

void Banger::changeAnimation(eBangerState state)
{
	switch (state)
	{
	case eBangerState::BANGER_STAND:
		_current_anim->setAnimation(0, 2, 0.1);
		break;

	case eBangerState::BANGER_JUMP:
		_current_anim->setAnimation(1, 2, 0.15, false);
		break;

	case eBangerState::BANGER_FALL:
		_current_anim->setAnimation(1, 2, 0.15, false);
		break;

	case eBangerState::BANGER_ATTACK:
		_current_anim->setAnimation(2, 3, 0.15, false);
		break;

	case BANGER_DIE:
		_anim_die->setAnimation(0, 8, 0.05, false);
		break;

	default: 
		break;
	}

	this->setWidth(_current_anim->getWidth());
	this->setHeight(_current_anim->getHeight());
}


void Banger::setState(BangerState* newState)
{
	if (_currentState == newState->GetStateName())
		return;

	SAFE_DELETE(_pBangerData->bangerState);

	_pBangerData->bangerState = newState;
	_currentState = newState->GetStateName();
	changeAnimation(newState->GetStateName());
}

RECT Banger::getBound()
{
	RECT bound;

	bound.left = _posX - 15;
	bound.right = _posX + 15;
	bound.top = _posY - 20;
	bound.bottom = _posY + 48 / 2.0f;

	return bound;
}

void Banger::draw(Camera* camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter, D3DCOLOR transColor)
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
		_anim_die->setPosition(getPosition());

		if (camera != NULL)
			_anim_die->draw(_anim_die->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, transColor);
		else
			_anim_die->draw(_anim_die->getPosition());
	}
	else
	{
		_current_anim->setReverse(_isReverse);
		_current_anim->setPosition(getPosition());

		if (camera != NULL)
			_current_anim->draw(_current_anim->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, transColor);
		else
			_current_anim->draw(_current_anim->getPosition());
	}
}

void Banger::update(float gameTime)
{
	onNoCollisionWithBottom();

	for (auto& bullet : _listBullet)
		bullet->update(gameTime);

	if (_isAllowDraw == false)
		return;

	_current_anim->update(gameTime);
	_anim_die->update(gameTime);
	BaseObject::update(gameTime);

	if (_pBangerData->bangerState != NULL)
		_pBangerData->bangerState->Update(gameTime);
}

void Banger::onCollision(eSideCollision side)
{
	if (_pBangerData->bangerState != NULL)
		_pBangerData->bangerState->OnCollision(side);
}

void Banger::onCollision(BaseObject* obj)
{
	if (obj->getObjectType() == BaseObject::ROCK_MAN_BULLET && !_isDie)
	{
		_HP -= obj->getDamage();
		if (_HP <= 0)
		{
			_isDie = true;
			this->setState(new BangerDie(_pBangerData));

			//
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

void Banger::onNoCollisionWithBottom()
{
	if (_side_y != BOTTOM)
	{
		switch (_currentState)
		{
		case BANGER_STAND:
		case BANGER_ATTACK:
			this->setState(new BangerFall(_pBangerData));
			break;
		default:break;
		}
	}
}
