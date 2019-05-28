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
	_pAnimationDie = new Animation(Define::EXPLOSIONS, 1, 8, 35, 30);
	_pCurrentAnim = new Animation(Define::NOTOR_BANGER_SPRITE, 3, 4, 48, 48);
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

	this->SetState(new BangerFall(_pBangerData));
}

void Banger::NewEntity()
{
	_posX = _startx;
	_posY = _starty;
	_HP = _MaxHP;
	_isReverse = true;
	_isAllowDraw = true;
	_isDie = false;
	_currentState = BANGER_NONE;
	this->SetState(new BangerFall(_pBangerData));
}

Banger::~Banger()
{
	delete _pBangerData;
	delete _pCurrentAnim;
	delete _pAnimationDie;
	for (auto& bullet : _listBullet)
		delete bullet;
	_listBullet.clear();
}

void Banger::ChangeAnimation(eBangerState state)
{
	switch (state)
	{
	case eBangerState::BANGER_STAND:
		_pCurrentAnim->SetAnimation(0, 2, 0.1);
		break;

	case eBangerState::BANGER_JUMP:
		_pCurrentAnim->SetAnimation(1, 2, 0.15, false);
		break;

	case eBangerState::BANGER_FALL:
		_pCurrentAnim->SetAnimation(1, 2, 0.15, false);
		break;

	case eBangerState::BANGER_ATTACK:
		_pCurrentAnim->SetAnimation(2, 3, 0.15, false);
		break;

	case BANGER_DIE:
		_pAnimationDie->SetAnimation(0, 8, 0.05, false);
		break;

	default: break;
	}

	this->SetWidth(_pCurrentAnim->GetWidth());
	this->SetHeight(_pCurrentAnim->GetHeight());
}


void Banger::SetState(BangerState * newState)
{
	if (_currentState == newState->GetStateName())
		return;

	SAFE_DELETE(_pBangerData->bangerState);

	_pBangerData->bangerState = newState;
	_currentState = newState->GetStateName();
	ChangeAnimation(newState->GetStateName());
}

RECT Banger::GetBound()
{
	RECT bound;

	bound.left = _posX - 15;
	bound.right = _posX + 15;
	bound.top = _posY - 20;
	bound.bottom = _posY + 48 / 2.0f;

	return bound;
}

void Banger::Draw(Camera * camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter, D3DCOLOR transColor)
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
		_pAnimationDie->SetPosition(GetPosition());

		if (camera != NULL)
			_pAnimationDie->Draw(_pAnimationDie->GetPosition(), rect, scale, camera->GetTrans(), angle, rotationCenter, transColor);
		else
			_pAnimationDie->Draw(_pAnimationDie->GetPosition());
	}
	else
	{
		_pCurrentAnim->SetReverse(_isReverse);
		_pCurrentAnim->SetPosition(GetPosition());

		if (camera != NULL)
			_pCurrentAnim->Draw(_pCurrentAnim->GetPosition(), rect, scale, camera->GetTrans(), angle, rotationCenter, transColor);
		else
			_pCurrentAnim->Draw(_pCurrentAnim->GetPosition());
	}
}

void Banger::Update(float gameTime)
{
	OnNoCollisionWithBottom();

	for (auto& bullet : _listBullet)
		bullet->Update(gameTime);

	if (_isAllowDraw == false)
		return;

	_pCurrentAnim->Update(gameTime);
	_pAnimationDie->Update(gameTime);
	BaseObject::Update(gameTime);

	if (_pBangerData->bangerState != NULL)
		_pBangerData->bangerState->Update(gameTime);
}

void Banger::OnCollision(eSideCollision side)
{
	if (_pBangerData->bangerState != NULL)
		_pBangerData->bangerState->OnCollision(side);
}

void Banger::OnCollision(BaseObject * obj)
{
	if (obj->GetObjectType() == BaseObject::ROCK_MAN_BULLET && !_isDie)
	{
		_HP -= obj->GetDamage();
		if (_HP <= 0)
		{
			_isDie = true;
			this->SetState(new BangerDie(_pBangerData));

			//
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

void Banger::OnNoCollisionWithBottom()
{
	if (_sideY != BOTTOM)
	{
		switch (_currentState)
		{
		case BANGER_STAND:
		case BANGER_ATTACK:
			this->SetState(new BangerFall(_pBangerData));
			break;
		default:break;
		}
	}
}
