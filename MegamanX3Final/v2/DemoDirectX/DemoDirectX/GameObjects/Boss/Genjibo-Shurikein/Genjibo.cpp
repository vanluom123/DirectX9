#include "Genjibo.h"
#include "../../../GameDefines/GameDefine.h"
#include "../../../GameComponents/GameCollision.h"
#include "../../Item/BigBloodItem.h"

Genjibo::Genjibo()
{
	_objectType = eObject_Boss;
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
	sideGen = eSide_None;
	change = false;
	setState(eShurikein_Appear);
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

void Genjibo::onCollision(BaseObject* obj)
{
	if (obj->getObjectType() == eObject_RockMan_Bullet)
	{
		_HP -= 2;
		if (_HP < 0)
		{
			_isDie = true;
			setState(eShurikein_Death);

			auto item = new BigBloodItem();
			_listBullet.push_back(item);
			item->setPosition(_posX, _posY);
			item->setObjectType(eObject_Item);
			return;
		}

		if (shurikeinState == eShurikein_Attack_2 && currentState == eGenjibo_Move)
		{
			currentState = eGenjibo_Jump;
			_vy = Define::ENEMY_MIN_JUMP_VELOCITY;
		}
	}
}

void Genjibo::onCollision(Side_Collision side)
{
	switch (shurikeinState)
	{
		case eShurikein_Stand:
			break;
		case eShurikein_Attack_1:
		{
			//Attack Around
			if (_side_x == eSide_None && _side_y != eSide_None)
			{
				change = true;
				if (_vy > 0)
					sideGen = eSide_Bottom;
				else
					sideGen = eSide_Top;
			}
			else if (_side_x != eSide_None && _side_y == eSide_None)
			{
				change = true;
				if (_vx > 0)
					sideGen = eSide_Right;
				else
					sideGen = eSide_Left;
			}
			else if (_side_x != eSide_None && _side_y != eSide_None && change)
			{
				change = false;
				if (sideGen == eSide_Top || sideGen == eSide_Bottom)
					_vy *= -1;
				else
					_vx *= -1;
			}
			else if (_side_x == eSide_None && _side_y == eSide_None && change)
			{
				change = false;
				if (sideGen == eSide_Top || sideGen == eSide_Bottom)
					_vx *= -1;
				else
					_vy *= -1;
			}
			break;
		}

		case eShurikein_Attack_2:
		case eShurikein_Attack_3:
		{
			if (side == eSide_Bottom)
				currentState = eGenjibo_Move;
			else
				if (side == eSide_Left || side == eSide_Right)
					_vx = -_vx;
			break;
		}

		default:
			break;
	}
}

void Genjibo::draw(Camera* camera, RECT r, GVec2 scale, float angle, GVec2 rotate, D3DCOLOR color)
{
	if (shurikeinState == eShurikein_Appear)
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

void Genjibo::setState(Shurikein_State keinState)
{
	if (shurikeinState == keinState)
		return;

	shurikeinState = keinState;

	switch (shurikeinState)
	{
		case eShurikein_Appear:
		{
			_vx = 0;
			_vy = 150;
			anim->setAnimation(1, 10, 0.05);
			animGenjinbo->setAnimation(0, 2, 0.05);
			posY = 920;
			break;
		}
		case eShurikein_Stand:
		{
			_vx = 0;
			_vy = 150;
			anim->setAnimation(7, 17, 0.005);
			break;
		}
		case eShurikein_Attack_1:
		{
			_vx = -150;
			_vy = 150;
			sideGen = eSide_Bottom;
			currentState = eGenjibo_None;
			anim->setAnimation(5, 10, 0.03);
			break;
		}
		case eShurikein_Attack_2:
		{
			currentState = eGenjibo_Move;
			anim->setAnimation(6, 10, 0.03);
			_vx = -150;
			_vy = 150;
			break;
		}
		case eShurikein_Attack_3:
		{
			currentState = eGenjibo_Move;
			anim->setAnimation(7, 17, 0.01);
			_vx = -80;
			_vy = 150;
			break;
		}
		case eShurikein_Death:
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
		case eShurikein_Appear:
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
					setState(eShurikein_Stand);
					return;
				}
			}
			else
				posY += 100 * dt;

			break;
		}
		case eShurikein_Stand:
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
					setState(eShurikein_Attack_1);
				else if (Num == 1)
					setState(eShurikein_Attack_2);
				else
					setState(eShurikein_Attack_3);
			}
			break;
		}
		case eShurikein_Attack_1:
		{
			timeMove += dt;
			if (timeMove > 6)
			{
				timeMove = 0;
				setState(eShurikein_Stand);
				return;
			}
			break;
		}
		case eShurikein_Attack_2:
		case eShurikein_Attack_3:
		{
			timeMove += dt;
			if (timeMove > 6)
			{
				timeMove = 0;
				setState(eShurikein_Stand);
				return;
			}
			switch (currentState)
			{
				case eGenjibo_Move:
					_vy = 150;
					if (shurikeinState == eShurikein_Attack_3)
					{
						currentState = eGenjibo_Jump;
						_vy = Define::ENEMY_MIN_JUMP_VELOCITY;
						return;
					}
					break;
				case eGenjibo_Jump:
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
