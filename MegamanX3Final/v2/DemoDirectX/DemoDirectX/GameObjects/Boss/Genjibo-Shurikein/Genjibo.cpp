#include "Genjibo.h"
#include "../../../GameDefines/GameDefine.h"
#include "../../../GameComponents/GameCollision.h"
#include "../../Item/BigBloodItem.h"

Genjibo::Genjibo()
{
	_objectType = eObjectType::BOSS;
	_isAllowDraw = false;
	timeStand = 0;
	timeMove = 0;
	posY = _posY;
	transY = 15;
	count = 0;
	_MaxHP = 30;
	_HP = _MaxHP;
	_Damage = 4;
	anim = new Animation(Define::GENJIBO_SHURIKEIN, 8, 17, 49, 49, 0.01f);
	animGenjinbo = new Animation(Define::SHURIKEN, 2, 2, 32, 68, 0.01f);
	animDie = new Animation(Define::EXPLOSIONS, 1, 8, 35, 30, 0.05);
	sideGen = NONE;
	change = false;
	shurikeinState = Shurikein::STAND;
	setState(Shurikein::APPEAR);
}


Genjibo::~Genjibo()
{
	delete anim;
	delete animGenjinbo;
	delete animDie;
}

RECT Genjibo::getBound()
{
	RECT bound;
	bound.left = _posX - _width / 2.0f;
	bound.right = bound.left + _width;
	bound.top = _posY - _height / 2.0f;
	bound.bottom = bound.top + _height;
	return bound;
}

void Genjibo::update(float dt)
{
	for (auto& bullet : _listBullet)
		bullet->update(dt);

	if (_isDie == true)
	{
		if (animDie->getPause() == true)
			return;
		animDie->update(dt);
	}
	else
		anim->update(dt);

	animGenjinbo->update(dt);
	updateState(dt);
	BaseObject::update(dt);
}

void Genjibo::onCollision(BaseObject * obj)
{
	if (obj->getObjectType() == eObjectType::ROCK_MAN_BULLET)
	{
		_HP -= 2;
		if (_HP < 0)
		{
			_isDie = true;
			setState(Shurikein::DIE);

			auto item = new BigBloodItem();
			_listBullet.push_back(item);
			item->setPosition(_posX, _posY);
			item->setObjectType(BaseObject::ITEM);
			return;
		}

		if (shurikeinState == Shurikein::ATTACK_2 && currentState == GenjiboState::MOVE)
		{
			currentState = GenjiboState::JUMP;
			_vy = Define::ENEMY_MIN_JUMP_VELOCITY;
		}
	}
}

void Genjibo::onCollision(eSideCollision side)
{
	switch (shurikeinState)
	{
	case Shurikein::STAND:
		break;
	case Shurikein::ATTACK_1:
	{
		//Attack Around
		if (_side_x == BaseObject::NONE && _side_y != BaseObject::NONE)
		{
			change = true;
			if (_vy > 0)
				sideGen = BaseObject::BOTTOM;
			else
				sideGen = BaseObject::TOP;
		}
		else if (_side_x != BaseObject::NONE && _side_y == BaseObject::NONE)
		{
			change = true;
			if (_vx > 0)
				sideGen = BaseObject::RIGHT;
			else
				sideGen = BaseObject::LEFT;
		}
		else if (_side_x != BaseObject::NONE && _side_y != BaseObject::NONE && change)
		{
			change = false;
			if (sideGen == TOP || sideGen == BOTTOM)
				_vy *= -1;
			else
				_vx *= -1;
		}
		else if (_side_x == BaseObject::NONE && _side_y == BaseObject::NONE && change)
		{
			change = false;
			if (sideGen == TOP || sideGen == BOTTOM)
				_vx *= -1;
			else
				_vy *= -1;
		}
		break;
	}

	case Shurikein::ATTACK_2:
	case Shurikein::ATTACK_3:
	{
		if (side == BaseObject::BOTTOM)
			currentState = GenjiboState::MOVE;
		else
			if (side == BaseObject::LEFT || side == BaseObject::RIGHT)
				_vx = -_vx;
		break;
	}

	default:
		break;
	}
}

void Genjibo::draw(Camera * camera, RECT r, GVec2 scale, float angle, GVec2 rotate, D3DCOLOR color)
{
	if (shurikeinState == Shurikein::APPEAR)
	{
		animGenjinbo->setPosition(_posX, posY);
		animGenjinbo->draw(animGenjinbo->getPosition(), r, scale, camera->getTrans(), angle, rotate, color);
	}

	for (auto& bullet : _listBullet)
		bullet->draw(camera);

	if (_isAllowDraw == false) return;

	if (_isDie == true)
	{
		if (animDie->getPause() == true)
			return;
		animDie->setPosition(getPosition());
		animDie->draw(animDie->getPosition(), r, scale, camera->getTrans(), angle, rotate, color);
	}
	else
	{
		anim->setPosition(getPosition());
		anim->draw(anim->getPosition(), r, scale, camera->getTrans(), angle, rotate, color);
	}
}

void Genjibo::setState(Shurikein keinState)
{
	if (shurikeinState == keinState)
		return;

	shurikeinState = keinState;

	switch (shurikeinState)
	{
	case Shurikein::APPEAR:
	{
		_vx = 0;
		_vy = 150;
		anim->setAnimation(1, 10, 0.05);
		animGenjinbo->setAnimation(0, 2, 0.05);
		posY = 920;
		break;
	}
	case Shurikein::STAND:
	{
		_vx = 0;
		_vy = 150;
		anim->setAnimation(7, 17, 0.005);
		break;
	}
	case Shurikein::ATTACK_1:
	{
		_vx = -150;
		_vy = 150;
		sideGen = BaseObject::BOTTOM;
		currentState = GenjiboState::NONE;
		anim->setAnimation(5, 10, 0.03);
		break;
	}
	case Shurikein::ATTACK_2:
	{
		currentState = GenjiboState::MOVE;
		anim->setAnimation(6, 10, 0.03);
		_vx = -150;
		_vy = 150;
		break;
	}
	case Shurikein::ATTACK_3:
	{
		currentState = GenjiboState::MOVE;
		anim->setAnimation(7, 17, 0.01);
		_vx = -80;
		_vy = 150;
		break;
	}
	case Shurikein::DIE:
		animDie->setAnimation(0, 8, 0.05, false);
		_vx = 0;
		_vy = 0;
		break;
	default:
		break;
	}

	_width = anim->getWidth();
	_height = anim->getHeight();
}

void Genjibo::updateState(float dt)
{
	switch (shurikeinState)
	{
	case Shurikein::APPEAR:
	{
		if (posY >= _posY - 8)
		{
			posY = _posY - 8;
			if (animGenjinbo->getCurrentRow() != 1)
			{
				animGenjinbo->setAnimation(1, 2, 0.05);
				_isAllowDraw = true;
			}
			timeMove += dt;
			if (timeMove > 2)
			{
				timeMove = 0;
				setState(Shurikein::STAND);
				return;
			}
		}
		else
			posY += 100 * dt;

		break;
	}
	case Shurikein::STAND:
	{
		_vx = 0;
		_vy = 150;
		timeStand += dt;
		if (timeStand > 2.0f)
		{
			timeStand = 0.0f;
			int Num = count % 3;
			count++;
			if (Num == 0)
				setState(Shurikein::ATTACK_1);
			else if (Num == 1)
				setState(Shurikein::ATTACK_2);
			else
				setState(Shurikein::ATTACK_3);
		}
		break;
	}
	case Shurikein::ATTACK_1:
	{
		timeMove += dt;
		if (timeMove > 6)
		{
			timeMove = 0;
			setState(Shurikein::STAND);
			return;
		}
		break;
	}
	case Shurikein::ATTACK_2:
	case Shurikein::ATTACK_3:
	{
		timeMove += dt;
		if (timeMove > 6)
		{
			timeMove = 0;
			setState(Shurikein::STAND);
			return;
		}
		switch (currentState)
		{
		case GenjiboState::MOVE:
			_vy = 150;
			if (shurikeinState == Shurikein::ATTACK_3)
			{
				currentState = GenjiboState::JUMP;
				_vy = Define::ENEMY_MIN_JUMP_VELOCITY;
				return;
			}
			break;
		case GenjiboState::JUMP:
		{
			addVy(transY);
			if (_vy > Define::ENEMY_MAX_JUMP_VELOCITY)
				_vy = Define::ENEMY_MAX_JUMP_VELOCITY;
		}
		default:
			break;
		}
		break;
	}
	default:
		break;
	}

}
