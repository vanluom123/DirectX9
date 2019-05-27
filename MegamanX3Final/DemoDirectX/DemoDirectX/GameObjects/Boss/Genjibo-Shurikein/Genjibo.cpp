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
	SetState(Shurikein::APPEAR);
}


Genjibo::~Genjibo()
{
	delete anim;
	delete animGenjinbo;
	delete animDie;
}

RECT Genjibo::GetBound()
{
	RECT r;
	r.left = _posX - _width / 2.0f;
	r.right = r.left + _width;
	r.top = _posY - _height / 2.0f;
	r.bottom = r.top + _height;
	return r;
}

void Genjibo::Update(float dt)
{
	for (auto& bullet : _listBullet)
		bullet->Update(dt);

	if (_isDie == true)
	{
		if (animDie->GetPause() == true)
			return;
		animDie->Update(dt);
	}
	else
		anim->Update(dt);

	animGenjinbo->Update(dt);
	ManageState(dt);
	BaseObject::Update(dt);
}

void Genjibo::OnCollision(BaseObject * obj)
{
	if (obj->GetObjectType() == eObjectType::ROCK_MAN_BULLET)
	{
		_HP -= 2;
		if (_HP < 0)
		{
			_isDie = true;
			SetState(Shurikein::DIE);

			auto* item = new BigBloodItem();
			_listBullet.push_back(item);
			item->SetPosition(_posX, _posY);
			item->SetObjectType(BaseObject::ITEM);
			return;
		}

		if (shurikeinState == Shurikein::ATTACK_2 && currentState == GenjiboState::MOVE)
		{
			currentState = GenjiboState::JUMP;
			_vy = Define::ENEMY_MIN_JUMP_VELOCITY;
		}
	}
}

void Genjibo::OnCollision(eSideCollision side)
{
	switch (shurikeinState)
	{
	case Shurikein::STAND:
		break;
	case Shurikein::ATTACK_1:
	{
		//Attack Around
		if (_sideX == BaseObject::NONE && _sideY != BaseObject::NONE)
		{
			change = true;
			if (_vy > 0)
				sideGen = BaseObject::BOTTOM;
			else
				sideGen = BaseObject::TOP;
		}
		else if (_sideX != BaseObject::NONE && _sideY == BaseObject::NONE)
		{
			change = true;
			if (_vx > 0)
				sideGen = BaseObject::RIGHT;
			else
				sideGen = BaseObject::LEFT;
		}
		else if (_sideX != BaseObject::NONE && _sideY != BaseObject::NONE && change)
		{
			change = false;
			if (sideGen == TOP || sideGen == BOTTOM)
				_vy *= -1;
			else
				_vx *= -1;
		}
		else if (_sideX == BaseObject::NONE && _sideY == BaseObject::NONE && change)
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

void Genjibo::Draw(Camera * camera, RECT r, GVec2 scale, float angle, GVec2 rotate, D3DCOLOR color)
{
	if (shurikeinState == Shurikein::APPEAR)
	{
		animGenjinbo->SetPosition(_posX, posY);
		animGenjinbo->Draw(animGenjinbo->GetPosition(), r, scale, camera->GetTrans(), angle, rotate, color);
	}

	for (auto& bullet : _listBullet)
		bullet->Draw(camera);

	if (_isAllowDraw == false) return;

	if (_isDie == true)
	{
		if (animDie->GetPause() == true)
			return;
		animDie->SetPosition(GetPosition());
		animDie->Draw(animDie->GetPosition(), r, scale, camera->GetTrans(), angle, rotate, color);
	}
	else
	{
		anim->SetPosition(GetPosition());
		anim->Draw(anim->GetPosition(), r, scale, camera->GetTrans(), angle, rotate, color);
	}
}

void Genjibo::SetState(Shurikein keinState)
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
		anim->SetAnimation(1, 10, 0.05);
		animGenjinbo->SetAnimation(0, 2, 0.05);
		posY = 920;
		break;
	}
	case Shurikein::STAND:
	{
		_vx = 0;
		_vy = 150;
		anim->SetAnimation(7, 17, 0.005);
		break;
	}
	case Shurikein::ATTACK_1:
	{
		_vx = -150;
		_vy = 150;
		sideGen = BaseObject::BOTTOM;
		currentState = GenjiboState::NONE;
		anim->SetAnimation(5, 10, 0.03);
		break;
	}
	case Shurikein::ATTACK_2:
	{
		currentState = GenjiboState::MOVE;
		anim->SetAnimation(6, 10, 0.03);
		_vx = -150;
		_vy = 150;
		break;
	}
	case Shurikein::ATTACK_3:
	{
		currentState = GenjiboState::MOVE;
		anim->SetAnimation(7, 17, 0.01);
		_vx = -80;
		_vy = 150;
		break;
	}
	case Shurikein::DIE:
		animDie->SetAnimation(0, 8, 0.05, false);
		_vx = 0;
		_vy = 0;
		break;
	default:
		break;
	}

	_width = anim->GetWidth();
	_height = anim->GetHeight();
}

void Genjibo::ManageState(float dt)
{
	switch (shurikeinState)
	{
	case Shurikein::APPEAR:
	{
		if (posY >= _posY - 8)
		{
			posY = _posY - 8;
			if (animGenjinbo->GetCurrentRow() != 1)
			{
				animGenjinbo->SetAnimation(1, 2, 0.05);
				_isAllowDraw = true;
			}
			timeMove += dt;
			if (timeMove > 2)
			{
				timeMove = 0;
				SetState(Shurikein::STAND);
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
				SetState(Shurikein::ATTACK_1);
			else if (Num == 1)
				SetState(Shurikein::ATTACK_2);
			else
				SetState(Shurikein::ATTACK_3);
		}
		break;
	}
	case Shurikein::ATTACK_1:
	{
		timeMove += dt;
		if (timeMove > 6)
		{
			timeMove = 0;
			SetState(Shurikein::STAND);
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
			SetState(Shurikein::STAND);
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
			AddVy(transY);
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
