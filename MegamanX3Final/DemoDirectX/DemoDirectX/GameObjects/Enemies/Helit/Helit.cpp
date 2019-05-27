#include "Helit.h"
#include "../../../GameDefines/GameDefine.h"
#include "HelitState/HelitDie/HelitDie.h"
#include "HelitState/HelitStand/HelitStand.h"
#include "../../../GameComponents/GameCollision.h"
#include "../../Item/SmallBlood.h"
#include "../../Item/SmallSubtankItem.h"

Helit::Helit()
{
	_objectType = ENEMY;
	_pAnim = new Animation(Define::HELIT_SPRITE_SHEET, 2, 4, 39, 37, 0.1, D3DCOLOR_XRGB(100, 100, 100));
	_pAnimDie = new Animation(Define::EXPLOSIONS, 1, 8, 35, 30);
	_isReverse = false;
	_isDie = false;
	_isAllowDraw = true;
	_MaxHP = 4;
	_HP = _MaxHP;
	_Damage = 3;
	_currentState = HELIT_UNKNOWN;

	_pHelitData = new HelitData;
	_pHelitData->helit = this;
	_pHelitData->helitState = NULL;

	this->SetState(new HelitStand(_pHelitData));
}

void Helit::NewEntity()
{
	_posX = _startx;
	_posY = _starty;

	_isReverse = false;
	_isDie = false;
	_isAllowDraw = true;
	_HP = _MaxHP;
	_currentState = HELIT_UNKNOWN;
	SetState(new HelitStand(_pHelitData));
}

Helit::~Helit()
{
	delete _pHelitData;
	delete _pAnim;
	delete _pAnimDie;
	for (auto& bullet : _listBullet)
		delete bullet;
	_listBullet.clear();
}

RECT Helit::GetBound()
{
	RECT r;

	r.left = _posX - 19;
	r.right = _posX + 19;
	r.top = _posY - 18;
	r.bottom = _posY + 37 / 2.0f;

	return r;
}

void Helit::Update(float dt)
{
	for (auto& bullet : _listBullet)
		bullet->Update(dt);

	if (_isAllowDraw == false)
		return;

	BaseObject::Update(dt);

	if (_isDie == true)
		_pAnimDie->Update(dt);
	else
		_pAnim->Update(dt);

	if (_pHelitData->helitState != NULL)
		_pHelitData->helitState->Update(dt);
}

void Helit::OnCollision(BaseObject* obj)
{
	if (obj->GetObjectType() == BaseObject::ROCK_MAN_BULLET && _isDie == false)
	{
		_HP -= obj->GetDamage();
		if (_HP <= 0)
		{
			_isDie = true;
			SetState(new HelitDie(_pHelitData));
		}

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

void Helit::Draw(Camera* camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter, D3DCOLOR color)
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

		if (camera != NULL)
			_pAnimDie->Draw(_pAnimDie->GetPosition(), rect, scale, camera->GetTrans(), angle, rotationCenter, color);
		else
			_pAnimDie->Draw(_pAnimDie->GetPosition());
	}
	else
	{
		_pAnim->SetReverse(_isReverse);
		_pAnim->SetPosition(this->GetPosition());

		if (camera != NULL)
			_pAnim->Draw(_pAnim->GetPosition(), rect, scale, camera->GetTrans(), angle, rotationCenter, color);
		else
			_pAnim->Draw(_pAnim->GetPosition());
	}
}

void Helit::SetState(HelitState* newState)
{
	if (_currentState == newState->GetState())
		return;

	SAFE_DELETE(_pHelitData->helitState);

	_pHelitData->helitState = newState;
	_currentState = newState->GetState();
	ChangeAnimation(newState->GetState());
}

void Helit::ChangeAnimation(eHelitState state)
{
	switch (state)
	{
	case HELIT_STAND:
		_pAnim->SetAnimation(0, 4, 0.15);
		_pAnim->SetFrame(39, 36);
		break;

	case HELIT_ATTACK:
		_pAnim->SetAnimation(1, 4, 0.15);
		_pAnim->SetFrame(39, 36);
		break;

	case HELIT_DIE:
		_pAnimDie->SetAnimation(0, 8, 0.05, false);
		break;

	default: break;
	}

	_width = _pAnim->GetWidth();
	_height = _pAnim->GetHeight();
}