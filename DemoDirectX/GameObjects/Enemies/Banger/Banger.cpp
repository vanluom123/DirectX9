#include "Banger.h"
#include "../../../GameDefines/GameDefine.h"
#include "BangerState/BangerFall/BangerFall.h"
#include "BangerState/BangerDie/BangerDie.h"
#include "../../../GameComponents/GameCollision.h"
#include "../../Item/SmallBlood.h"
#include "../../Item/SmallSubtankItem.h"

Banger::Banger()
{
	_objectType = Enumerator::Object_Type::ENEMY;
	_anim_die = new Animation(Define::EXPLOSIONS, 1, 8, 35, 30);
	_current_anim = new Animation(Define::NOTOR_BANGER_SPRITE, 3, 4, 48, 48);
	_MaxHP = 4;
	_HP = _MaxHP;
	_Damage = 3;
	_isReverse = true;
	_isAllowDraw = true;
	_isDestroy = false;
	this->setState(new BangerFall(this));
}

void Banger::newObject()
{
	_posX = _startx;
	_posY = _starty;
	_HP = _MaxHP;
	_isReverse = true;
	_isAllowDraw = true;
	_isDestroy = false;
	m_state = Banger_State::NONE;
	this->setState(new BangerFall(this));
}

Banger::~Banger()
{
	delete _current_anim;
	delete _anim_die;
	for (auto& bullet : _listBullet)
		delete bullet;
	if (!_listBullet.empty())
		_listBullet.clear();
}

void Banger::changeAnimation(Banger_State state)
{
	switch (state)
	{
		case Banger_State::STAND:
			_current_anim->setAnimation(0, 2, 0.1f);
			break;

		case Banger_State::JUMP:
			_current_anim->setAnimation(1, 2, 0.15f, false);
			break;

		case Banger_State::FALL:
			_current_anim->setAnimation(1, 2, 0.15f, false);
			break;

		case Banger_State::ATTACK:
			_current_anim->setAnimation(2, 3, 0.15f, false);
			break;

		case Banger_State::DEATH:
			_anim_die->setAnimation(0, 8, 0.05f, false);
			break;

		default:
			break;
	}

	this->setWidth(_current_anim->getWidth());
	this->setHeight(_current_anim->getHeight());
}


void Banger::setState(BangerState* new_state)
{
	if (m_state == new_state->getState())
		return;

	delete m_pState;
	m_pState = new_state;
	m_state = new_state->getState();
	changeAnimation(new_state->getState());
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
			_anim_die->setPosition(getPosition());

			if (camera)
				_anim_die->draw(_anim_die->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, transColor);
			else
				_anim_die->draw(_anim_die->getPosition());
		}
		else
		{
			_current_anim->setReverse(_isReverse);
			_current_anim->setPosition(getPosition());

			if (camera)
				_current_anim->draw(_current_anim->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, transColor);
			else
				_current_anim->draw(_current_anim->getPosition());
		}
	}
}

void Banger::update(float gameTime)
{
	onNoCollisionWithBottom();

	for (auto& bullet : _listBullet)
		bullet->update(gameTime);

	if (_isAllowDraw)
	{
		_current_anim->update(gameTime);
		_anim_die->update(gameTime);
		BaseObject::update(gameTime);

		if (m_pState)
			m_pState->Update(gameTime);
	}
}

void Banger::onCollision(Side_Collision side)
{
	if (m_pState)
		m_pState->OnCollision(side);
}

void Banger::onCollision(BaseObject* obj)
{
	if (obj->getObjectType() == Enumerator::Object_Type::ROCKMAN_BULLET && !_isDestroy)
	{
		_HP -= obj->getDamage();
		if (_HP <= 0)
		{
			_isDestroy = true;
			this->setState(new BangerDie(this));

			// number of enemy throw item
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

void Banger::onNoCollisionWithBottom()
{
	if (_side_y != Enumerator::Side_Collision::BOTTOM)
	{
		if (m_state == Banger_State::STAND || m_state == Banger_State::ATTACK)
			this->setState(new BangerFall(this));
	}
}

Animation* Banger::getAnimation() const { return _current_anim; }
