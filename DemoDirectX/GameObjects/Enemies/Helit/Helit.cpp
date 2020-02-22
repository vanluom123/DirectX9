#include "Helit.h"
#include "../../../GameComponents/GameCollision.h"
#include "../../Item/SmallBlood.h"
#include "../../Item/SmallSubtankItem.h"

Helit::Helit()
{
	_objectType = Enumerator::Object_Type::ENEMY;
	_pAnim = new Animation(Define::HELIT_SPRITE_SHEET, 2, 4, 39, 37, 0.1f, D3DCOLOR_XRGB(100, 100, 100));
	_pAnimDie = new Animation(Define::EXPLOSIONS, 1, 8, 35, 30);
	_isReverse = false;
	_isDestroy = false;
	_isAllowDraw = true;
	_MaxHP = 4;
	_HP = _MaxHP;
	_Damage = 3;
	changeStatus(Helit_State::STAND);
}

void Helit::newObject()
{
	_position.x = _startPosition.x;
	_position.y = _startPosition.y;
	_isReverse = false;
	_isDestroy = false;
	_isAllowDraw = true;
	_HP = _MaxHP;
	m_state = Helit_State::NONE;
	changeStatus(Helit_State::STAND);
}

Helit::~Helit()
{
	delete _pAnim;
	delete _pAnimDie;
	for (auto bullet : _listBullet)
		delete bullet;
	if (!_listBullet.empty())
		_listBullet.clear();
}

RECT Helit::getBound()
{
	RECT bound;

	bound.left = _position.x - 19;
	bound.right = _position.x + 19;
	bound.top = _position.y - 18;
	bound.bottom = _position.y + 37 / 2.0f;

	return bound;
}

void Helit::update(float dt)
{
	for (auto bullet : _listBullet)
		bullet->update(dt);

	if (_isAllowDraw)
	{
		BaseObject::update(dt);

		if (_isDestroy)
			_pAnimDie->update(dt);
		else
			_pAnim->update(dt);

		if (m_state != Helit_State::NONE)
			updateStatus(dt);
	}
}

void Helit::onCollision(BaseObject* obj)
{
	if (obj->getObjectType() == Enumerator::Object_Type::ROCKMAN_BULLET && !_isDestroy)
	{
		_HP -= obj->getDamage();
		if (_HP <= 0)
		{
			_isDestroy = true;
			changeStatus(Helit_State::DEATH);

			// number of enemy throw item
			int num = (rand() % 999) % 4;
			if (num == 1)
			{
				auto item = new SmallBloodItem();
				_listBullet.push_back(item);
				item->setPosition(_position.x, _position.y);
				item->setObjectType(Enumerator::Object_Type::ITEM);
			}
			else if (num == 2)
			{
				auto item = new SmallSubtankItem();
				_listBullet.push_back(item);
				item->setPosition(_position.x, _position.y);
				item->setObjectType(Enumerator::Object_Type::ITEM);
			}
		}
	}
}

void Helit::draw(Camera* camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter, D3DCOLOR color)
{
	if (!_isDestroy)
	{
		if (!GameCollision::getInstance()->AABBCheck(this->getBound(), camera->getBound()))
			_isAllowDraw = false;
		else
			_isAllowDraw = true;
	}

	for (auto bullet : _listBullet)
		bullet->draw(camera);

	if (_isAllowDraw)
	{
		if (_isDestroy)
		{
			_pAnimDie->setPosition(this->getPosition());

			if (camera)
				_pAnimDie->draw(_pAnimDie->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
			else
				_pAnimDie->draw(_pAnimDie->getPosition());
		}
		else
		{
			_pAnim->setReverse(_isReverse);
			_pAnim->setPosition(this->getPosition());

			if (camera)
				_pAnim->draw(_pAnim->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
			else
				_pAnim->draw(_pAnim->getPosition());
		}
	}
}

void Helit::changeAnimation(Helit_State state)
{
	switch (state)
	{
		case Helit_State::STAND:
			_pAnim->setAnimation(0, 4, 0.15f);
			_pAnim->setFrame(39, 36);
			break;

		case Helit_State::ATTACK:
			_pAnim->setAnimation(1, 4, 0.15f);
			_pAnim->setFrame(39, 36);
			break;

		case Helit_State::DEATH:
			_pAnimDie->setAnimation(0, 8, 0.05f, false);
			break;

		default:
			break;
	}

	setWidth(_pAnim->getWidth());
	setHeight(_pAnim->getHeight());
}

void Helit::updateStatus(float dt)
{
	switch (m_state)
	{
		case Helit_State::STAND:
			updateStand(dt);
			break;

		case Helit_State::ATTACK:
			updateAttack(dt);
			break;

		case Helit_State::DEATH:
			updateDeath(dt);
			break;

		default: break;
	}
}

void Helit::updateStand(float dt)
{
	_timeStand += dt;

	if (_timeStand > 2.0f)
		changeStatus(Helit_State::ATTACK);
	else
	{
		if (_timeStand > 1.0f)
			_velocity.y = 60.0f;
	}
}

void Helit::updateAttack(float dt)
{
	_timeAttack += dt;
	if (_timeAttack >= 0.4f)
	{
		_timeAttack = 0.0f;
		_count++;

		if (_count > 1)
		{
			changeStatus(Helit_State::STAND);
			return;
		}

		if (_listBullet.size() < 2)
		{
			auto* bullet = new HelitBullet();
			_listBullet.push_back(bullet);
		}

		float posX = 0;
		float posY = this->getBound().top + 35;

		if (_isReverse)
			posX = this->getBound().right - 10;
		else
			posX = this->getBound().left + 10;


		_listBullet.at(_count)->setPosition(posX, posY);
		_listBullet.at(_count)->setReverse(_isReverse);
		_listBullet.at(_count)->newObject();
	}
}

void Helit::updateDeath(float dt)
{
	addVy(_accelerateY);

	_timeDie += dt;
	if (_timeDie >= 0.45f)
		this->setDraw(false);
}

void Helit::initStand()
{
	_timeStand = 0.0f;
	_velocity.x = 0.0f;
	_velocity.y = -60.0f;
}

void Helit::initAttack()
{
	_velocity.x = 0.0f;
	_velocity.y = 0.0f;
	_timeAttack = 0.0f;
	_count = -1;
}

void Helit::initDeath()
{
	_timeDie = 0.0f;
	_accelerateY = 25.0f;
	_velocity.y = Define::ENEMY_MIN_JUMP_VELOCITY;
}

void Helit::initStatus(Helit_State status)
{
	switch (status)
	{
		case Helit_State::STAND:
			initStand();
			break;

		case Helit_State::ATTACK:
			initAttack();
			break;

		case Helit_State::DEATH:
			initDeath();
			break;

		default: break;
	}
}

void Helit::changeStatus(Helit_State status)
{
	if (m_state == status)
		return;

	m_state = status;
	changeAnimation(status);
	initStatus(status);
}
