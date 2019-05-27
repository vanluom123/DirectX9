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
	_pAnim = new Animation(Define::HEAD_GUNNER_SPRITE, 4, 4, 51, 45, 0.15, D3DCOLOR_XRGB(100, 100, 100));
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

	this->SetState(new GunnerFall(_pGunnerData));
}

void Gunner::NewEntity()
{
	_posX = _startx;
	_posY = _starty;
	_isReverse = false;
	_isAllowDraw = true;
	_isDie = false;
	_HP = _MaxHP;
	_curState = GUNNER_NONE;
	SetState(new GunnerFall(_pGunnerData));
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

RECT Gunner::GetBound()
{
	RECT bound;

	bound.left = _posX - 15;
	bound.right = _posX + 15;
	bound.top = _posY - 21;
	bound.bottom = _posY + 45 / 2.0f;

	return bound;
}

void Gunner::Update(float dt)
{
	OnNoCollisionWithBottom();

	for (auto& bullet : _listBullet)
		bullet->Update(dt);

	if (_isAllowDraw == false)
		return;

	if (_isDie == false)
		_pAnim->Update(dt);
	else
		_pAnimDie->Update(dt);

	BaseObject::Update(dt);

	if (_pGunnerData->gunnerState != NULL)
		_pGunnerData->gunnerState->Update(dt);
}

void Gunner::OnCollision(eSideCollision side)
{
	if (_pGunnerData->gunnerState != NULL)
		_pGunnerData->gunnerState->OnCollision(side);
}

void Gunner::OnCollision(BaseObject * obj)
{
	if (obj->GetObjectType() == BaseObject::ROCK_MAN_BULLET && !_isDie)
	{
		_HP -= obj->GetDamage();
		if (_HP <= 0)
		{
			_isDie = true;
			this->SetState(new GunnerDie(_pGunnerData));

			int num = (rand() % 999) % 4;
			if (num == 1)
			{
				auto* item = new SmallBloodItem();
				_listBullet.push_back(item);
				item->SetPosition(_posX, _posY);
				item->SetObjectType(BaseObject::ITEM);
			}
			else if (num == 2)
			{
				auto* item = new SmallSubtankItem();
				_listBullet.push_back(item);
				item->SetPosition(_posX, _posY);
				item->SetObjectType(BaseObject::ITEM);
			}
		}
	}
}

void Gunner::OnNoCollisionWithBottom()
{
	if (_sideY != BOTTOM)
	{
		switch (_curState)
		{
		case GUNNER_STAND:
		case GUNNER_ATTACK:
		case GUNNER_ATTACK_ROCKET:
		case GUNNER_ATTACK_BULLET:
			SetState(new GunnerFall(_pGunnerData));
			break;
		default: break;
		}
	}
}

void Gunner::Draw(Camera * camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter,
	D3DCOLOR color)
{
	if (_isDie == false)
	{
		if (GameCollision::IsCollision(this->GetBound(), camera->GetBound()) == false)
			_isAllowDraw = false;
		else
			_isAllowDraw = true;
	}

	for (auto& bullet : _listBullet)
		bullet->Draw(camera);

	if (_isAllowDraw == false)
		return;

	if (_isDie == true)
	{
		_pAnimDie->SetPosition(this->GetPosition());
		_pAnimDie->SetReverse(_isReverse);

		if (camera != NULL)
			_pAnimDie->Draw(_pAnimDie->GetPosition(), rect, scale, camera->GetTrans(), angle, rotationCenter, color);
		else
			_pAnimDie->Draw(_pAnimDie->GetPosition());

		return;
	}

	_pAnim->SetPosition(this->GetPosition());
	_pAnim->SetReverse(_isReverse);

	if (camera != NULL)
		_pAnim->Draw(_pAnim->GetPosition(), rect, scale, camera->GetTrans(), angle, rotationCenter, color);
	else
		_pAnim->Draw(_pAnim->GetPosition());
}

void Gunner::ChangeAnimation(eGunnerState stateName)
{
	switch (stateName)
	{
	case GUNNER_STAND:
		_pAnim->SetAnimation(0, 1);
		break;

	case GUNNER_ATTACK:
		_pAnim->SetAnimation(2, 3, 0.15, false);
		break;

	case GUNNER_ATTACK_ROCKET:
		_pAnim->SetAnimation(1, 3, 0.15, false);
		break;

	case GUNNER_ATTACK_BULLET:
		_pAnim->SetAnimation(0, 1);
		break;

	case GUNNER_FALL:
		_pAnim->SetAnimation(0, 1);
		break;

	case GUNNER_DIE:
		_pAnimDie->SetAnimation(0, 8, 0.05, false);
		break;

	default: break;
	}

	this->SetWidth(_pAnim->GetWidth());
	this->SetHeight(_pAnim->GetHeight());
}

void Gunner::SetState(GunnerState * state)
{
	if (_curState == state->GetState())
		return;

	SAFE_DELETE(_pGunnerData->gunnerState);

	_pGunnerData->gunnerState = state;
	_curState = state->GetState();
	this->ChangeAnimation(state->GetState());
}
