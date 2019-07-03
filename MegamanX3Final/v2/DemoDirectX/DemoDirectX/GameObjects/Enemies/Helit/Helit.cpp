#include "Helit.h"
#include "HelitState/HelitDie/HelitDie.h"
#include "HelitState/HelitStand/HelitStand.h"
#include "../../../GameComponents/GameCollision.h"
#include "../../Item/SmallBlood.h"
#include "../../Item/SmallSubtankItem.h"

Helit::Helit()
{
	_objectType = eObject_Enemy;
	_pAnim = new Animation(Define::HELIT_SPRITE_SHEET, 2, 4, 39, 37, 0.1f, D3DCOLOR_XRGB(100, 100, 100));
	_pAnimDie = new Animation(Define::EXPLOSIONS, 1, 8, 35, 30);
	_isReverse = false;
	_isDie = false;
	_isAllowDraw = true;
	_MaxHP = 4;
	_HP = _MaxHP;
	_Damage = 3;
	setState(new HelitStand(this));
}

void Helit::newObject()
{
	_posX = _startx;
	_posY = _starty;
	_isReverse = false;
	_isDie = false;
	_isAllowDraw = true;
	_HP = _MaxHP;
	m_state = eHelit_None;
	setState(new HelitStand(this));
}

Helit::~Helit()
{
	delete m_pState;
	delete _pAnim;
	delete _pAnimDie;
	for (auto& bullet : _listBullet)
		delete bullet;
	if (!_listBullet.empty())
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

	if (_isAllowDraw)
	{
		BaseObject::update(dt);

		if (_isDie)
			_pAnimDie->update(dt);
		else
			_pAnim->update(dt);

		if (m_pState)
			m_pState->update(dt);
	}
}

void Helit::onCollision(BaseObject* obj)
{
	if (obj->getObjectType() == eObject_RockMan_Bullet && !_isDie)
	{
		_HP -= obj->getDamage();
		if (_HP <= 0)
		{
			_isDie = true;
			setState(new HelitDie(this));
		}

		// number of enemy throw item
		int num = (rand() % 999) % 4;
		if (num == 1)
		{
			auto item = new SmallBloodItem();
			_listBullet.push_back(item);
			item->setPosition(_posX, _posY);
			item->setObjectType(eObject_Item);
		}
		else if (num == 2)
		{
			auto item = new SmallSubtankItem();
			_listBullet.push_back(item);
			item->setPosition(_posX, _posY);
			item->setObjectType(eObject_Item);
		}
	}
}

void Helit::draw(Camera* camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter, D3DCOLOR color)
{
	if (!_isDie)
	{
		if (!GameCollision::isCollision(this->getBound(), camera->getBound()))
			_isAllowDraw = false;
		else
			_isAllowDraw = true;
	}

	for (auto& bullet : _listBullet)
		bullet->draw(camera);

	if (_isAllowDraw)
	{
		if (_isDie)
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

void Helit::setState(HelitState* newState)
{
	if (m_state == newState->getState())
		return;

	delete m_pState;
	m_pState = newState;
	m_state = newState->getState();
	changeAnimation(newState->getState());
}

void Helit::changeAnimation(Helit_State state)
{
	switch (state)
	{
		case eHelit_Stand:
			_pAnim->setAnimation(0, 4, 0.15f);
			_pAnim->setFrame(39, 36);
			break;

		case eHelit_Attack:
			_pAnim->setAnimation(1, 4, 0.15f);
			_pAnim->setFrame(39, 36);
			break;

		case eHelit_Death:
			_pAnimDie->setAnimation(0, 8, 0.05f, false);
			break;

		default:
			break;
	}

	setWidth(_pAnim->getWidth());
	setHeight(_pAnim->getHeight());
}
