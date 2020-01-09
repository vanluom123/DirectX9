#include "Genjibo.h"
#include "../../../GameDefines/GameDefine.h"
#include "../../../GameComponents/GameCollision.h"
#include "../../Item/BigBloodItem.h"

Genjibo::Genjibo()
{
	this->_objectType = Enumerator::Object_Type::BOSS;
	this->_isAllowDraw = false;
	this->timeStand = 0.0f;
	this->timeMove = 0.0f;
	this->posY = _posY;
	this->transY = 15.0f;
	this->count = 0;
	this->_MaxHP = 30;
	this->_HP = this->_MaxHP;
	this->_Damage = 4;
	this->anim = new Animation(Define::GENJIBO_SHURIKEIN, 8, 17, 49, 49, 0.01f);
	this->animGenjinbo = new Animation(Define::SHURIKEN, 2, 2, 32, 68, 0.01f);
	this->animDie = new Animation(Define::EXPLOSIONS, 1, 8, 35, 30, 0.05f);
	this->sideGen = Enumerator::Side_Collision::NONE;
	this->change = false;
	this->setState(Enumerator::Shurikein_State::APPEAR);
}


Genjibo::~Genjibo()
{
	delete this->anim;
	delete this->animGenjinbo;
	delete this->animDie;
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

	if (this->_isDestroy)
	{
		if (this->animDie->getPause())
			return;
		this->animDie->update(dt);
	}
	else
		this->anim->update(dt);

	this->animGenjinbo->update(dt);
	this->updateState(dt);
	BaseObject::update(dt);
}

void Genjibo::onCollision(BaseObject* obj)
{
	if (obj->getObjectType() == Enumerator::Object_Type::ROCKMAN_BULLET)
	{
		this->_HP -= 2;
		if (this->_HP < 0)
		{
			this->_isDestroy = true;
			this->setState(Enumerator::Shurikein_State::DEATH);

			auto item = new BigBloodItem();
			this->_listBullet.push_back(item);
			item->setPosition(_posX, _posY);
			item->setObjectType(Enumerator::Object_Type::ITEM);
			return;
		}

		if (this->shurikeinState == Enumerator::Shurikein_State::ATTACK_2 && currentState == Enumerator::Genjibo_State::MOVE)
		{
			this->currentState = Enumerator::Genjibo_State::JUMP;
			this->_vy = Define::ENEMY_MIN_JUMP_VELOCITY;
		}
	}
}

void Genjibo::onCollision(Side_Collision side)
{
	switch (this->shurikeinState)
	{
	case Enumerator::Shurikein_State::STAND:
		break;
	case Enumerator::Shurikein_State::ATTACK_1:
	{
		//Attack Around
		if (this->_side_x == Enumerator::Side_Collision::NONE && _side_y != Enumerator::Side_Collision::NONE)
		{
			this->change = true;
			if (this->_vy > 0.0f)
				this->sideGen = Enumerator::Side_Collision::BOTTOM;
			else
				this->sideGen = Enumerator::Side_Collision::TOP;
		}
		else if (this->_side_x != Enumerator::Side_Collision::NONE && this->_side_y == Enumerator::Side_Collision::NONE)
		{
			this->change = true;
			if (_vx > 0.0f)
				this->sideGen = Enumerator::Side_Collision::RIGHT;
			else
				this->sideGen = Enumerator::Side_Collision::LEFT;
		}
		else if (this->_side_x != Enumerator::Side_Collision::NONE && this->_side_y != Enumerator::Side_Collision::NONE && this->change)
		{
			this->change = false;
			if (this->sideGen == Enumerator::Side_Collision::TOP || this->sideGen == Enumerator::Side_Collision::BOTTOM)
				this->_vy *= -1;
			else
				this->_vx *= -1;
		}
		else if (this->_side_x == Enumerator::Side_Collision::NONE && this->_side_y == Enumerator::Side_Collision::NONE && this->change)
		{
			this->change = false;
			if (this->sideGen == Enumerator::Side_Collision::TOP || this->sideGen == Enumerator::Side_Collision::BOTTOM)
				this->_vx *= -1;
			else
				this->_vy *= -1;
		}
		break;
	}

	case Enumerator::Shurikein_State::ATTACK_2:
	case Enumerator::Shurikein_State::ATTACK_3:
	{
		if (side == Enumerator::Side_Collision::BOTTOM)
			this->currentState = Enumerator::Genjibo_State::MOVE;
		else
			if (side == Enumerator::Side_Collision::LEFT || side == Enumerator::Side_Collision::RIGHT)
				this->_vx = -this->_vx;
		break;
	}

	default:
		break;
	}
}

void Genjibo::draw(Camera* camera, RECT r, GVec2 scale, float angle, GVec2 rotate, D3DCOLOR color)
{
	if (this->shurikeinState == Enumerator::Shurikein_State::APPEAR)
	{
		this->animGenjinbo->setPosition(this->_posX, this->posY);
		this->animGenjinbo->draw(this->animGenjinbo->getPosition(), r, scale, camera->getTrans(), angle, rotate, color);
	}

	for (auto& bullet : _listBullet)
		bullet->draw(camera);

	if (this->_isAllowDraw)
	{
		if (this->_isDestroy)
		{
			if (this->animDie->getPause())
				return;
			this->animDie->setPosition(getPosition());
			this->animDie->draw(this->animDie->getPosition(), r, scale, camera->getTrans(), angle, rotate, color);
		}
		else
		{
			this->anim->setPosition(getPosition());
			this->anim->draw(this->anim->getPosition(), r, scale, camera->getTrans(), angle, rotate, color);
		}
	}
}

void Genjibo::setState(Shurikein_State keinState)
{
	if (this->shurikeinState == keinState)
		return;

	this->shurikeinState = keinState;

	switch (this->shurikeinState)
	{
	case Enumerator::Shurikein_State::APPEAR:
	{
		this->_vx = 0.0f;
		this->_vy = 150.0f;
		this->anim->setAnimation(1, 10, 0.05f);
		this->animGenjinbo->setAnimation(0, 2, 0.05f);
		this->posY = 920.0f;
		break;
	}
	case Enumerator::Shurikein_State::STAND:
	{
		this->_vx = 0.0f;
		this->_vy = 150.0f;
		this->anim->setAnimation(7, 17, 0.005f);
		break;
	}
	case Enumerator::Shurikein_State::ATTACK_1:
	{
		this->_vx = -150.0f;
		this->_vy = 150.0f;
		this->sideGen = Enumerator::Side_Collision::BOTTOM;
		this->currentState = Enumerator::Genjibo_State::NONE;
		this->anim->setAnimation(5, 10, 0.03f);
		break;
	}
	case Enumerator::Shurikein_State::ATTACK_2:
	{
		this->currentState = Enumerator::Genjibo_State::MOVE;
		this->anim->setAnimation(6, 10, 0.03f);
		this->_vx = -150.0f;
		this->_vy = 150.0f;
		break;
	}
	case Enumerator::Shurikein_State::ATTACK_3:
	{
		this->currentState = Enumerator::Genjibo_State::MOVE;
		this->anim->setAnimation(7, 17, 0.01f);
		this->_vx = -80.0f;
		this->_vy = 150.0f;
		break;
	}
	case Enumerator::Shurikein_State::DEATH:
		this->animDie->setAnimation(0, 8, 0.05f, false);
		this->_vx = 0.0f;
		this->_vy = 0.0f;
		break;
	default:
		break;
	}

	this->_width = this->anim->getWidth();
	this->_height = this->anim->getHeight();
}

void Genjibo::updateState(float dt)
{
	switch (this->shurikeinState)
	{
	case Enumerator::Shurikein_State::APPEAR:
	{
		if (this->posY >= this->_posY - 8)
		{
			this->posY = this->_posY - 8;
			if (this->animGenjinbo->getCurrentRow() != 1)
			{
				this->animGenjinbo->setAnimation(1, 2, 0.05f);
				this->_isAllowDraw = true;
			}
			this->timeMove += dt;
			if (this->timeMove > 2.0f)
			{
				this->timeMove = 0.0f;
				this->setState(Enumerator::Shurikein_State::STAND);
				return;
			}
		}
		else
			this->posY += 100 * dt;

		break;
	}
	case Enumerator::Shurikein_State::STAND:
	{
		this->_vx = 0.0f;
		this->_vy = 150.0f;
		this->timeStand += dt;
		if (this->timeStand > 2.0f)
		{
			this->timeStand = 0.0f;
			int Num = count % 3;
			this->count++;
			if (Num == 0)
				this->setState(Enumerator::Shurikein_State::ATTACK_1);
			else if (Num == 1)
				this->setState(Enumerator::Shurikein_State::ATTACK_2);
			else
				this->setState(Enumerator::Shurikein_State::ATTACK_3);
		}
		break;
	}
	case Enumerator::Shurikein_State::ATTACK_1:
	{
		this->timeMove += dt;
		if (this->timeMove > 6.0f)
		{
			this->timeMove = 0.0f;
			this->setState(Enumerator::Shurikein_State::STAND);
			return;
		}
		break;
	}
	case Enumerator::Shurikein_State::ATTACK_2:
	case Enumerator::Shurikein_State::ATTACK_3:
	{
		this->timeMove += dt;
		if (this->timeMove > 6.0f)
		{
			this->timeMove = 0.0f;
			this->setState(Enumerator::Shurikein_State::STAND);
			return;
		}
		switch (this->currentState)
		{
		case Enumerator::Genjibo_State::MOVE:
			this->_vy = 150.0f;
			if (this->shurikeinState == Enumerator::Shurikein_State::ATTACK_3)
			{
				this->currentState = Enumerator::Genjibo_State::JUMP;
				this->_vy = Define::ENEMY_MIN_JUMP_VELOCITY;
				return;
			}
			break;
		case Enumerator::Genjibo_State::JUMP:
		{
			this->addVy(this->transY);
			if (this->_vy > Define::ENEMY_MAX_JUMP_VELOCITY)
				this->_vy = Define::ENEMY_MAX_JUMP_VELOCITY;
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
