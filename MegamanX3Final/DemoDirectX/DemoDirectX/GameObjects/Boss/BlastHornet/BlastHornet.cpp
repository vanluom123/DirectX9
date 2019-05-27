#include "BlastHornet.h"
#include "BlastDie.h"
#include "Move.h"
#include "BlastStand.h"
#include "BlastAppear.h"
#include "../../../GameDefines/GameDefine.h"

BlastHornet::BlastHornet()
{
	_objectType = eObjectType::BOSS;
	_MaxHP = 30;
	_Damage = 3;
	_HP = _MaxHP;
	curState = BlastState::None;
	hpbar = new HPBar(_objectType);

	pData = new BlastHornetData;
	pData->blastHornet = this;
	pData->blastHornetState = NULL;

	this->SetState(new BlastAppear(pData));
}


BlastHornet::~BlastHornet()
{
	delete anim;
	delete pData;
	for (auto&i : list_bullets_)
		delete i;
	list_bullets_.clear();
}

RECT BlastHornet::GetBound()
{
	RECT r;
	r.left = _posX - 20;
	r.right = _posX + 30;
	r.top = _posY - 30;
	r.bottom = _posY + 45;
	return r;
}

void BlastHornet::Update(float dt)
{
	for (auto&i : list_bullets_)
		i->Update(dt);

	if (!_isAllowDraw)
		return;

	anim->Update(dt);
	BaseObject::Update(dt);

	if (pData->blastHornetState)
		pData->blastHornetState->Update(dt);
}

void BlastHornet::OnCollision(eSideCollision side)
{
	if (pData->blastHornetState) 
		pData->blastHornetState->OnCollision(side);
}

void BlastHornet::OnCollision(BaseObject* obj)
{
	if (obj->GetObjectType() == eObjectType::ROCK_MAN_BULLET && !_isDie)
	{
		_HP -= 1 + obj->GetDamage() / 2;
			
		if (_HP <= 0)
		{
			SetState(new BlastDie(pData));
			_isDie = true;
		}
	}
}

void BlastHornet::Draw(Camera* camera, RECT r, GVec2 scale, float angle, GVec2 rotate, D3DCOLOR color)
{
	for (auto&i : list_bullets_)
		i->Draw(camera, r, scale, angle, rotate, color);

	hpbar->draw(_HP, _MaxHP);

	if (!_isAllowDraw) return;

	anim->SetPosition(GetPosition());
	anim->SetReverse(_isReverse);
	if (camera)
		anim->Draw(anim->GetPosition(), r, scale, camera->GetTrans(), angle, rotate, color);
	else
		anim->Draw(anim->GetPosition());
}

void BlastHornet::SetState(BlastHornetState* newState)
{
	if (curState == newState->GetState())
		return;

	SAFE_DELETE(pData->blastHornetState);
	pData->blastHornetState = newState;
	curState = newState->GetState();
	ChangeAnimation(newState->GetState());
}

void BlastHornet::ChangeAnimation(BlastState state)
{
	if (state == BlastState::Stand || state == BlastState::Move)
	{
		anim = new Animation("Resources/Enemies/BlastHornet/State/Stand/standspritesheet.png", 1, 4, 96, 96, 0.05, D3DCOLOR_XRGB(0, 128, 128));
		anim->SetAnimation(0, 4, 0.05);
	}
	else if (state == BlastState::Appear)
	{
		anim = new Animation("Resources/Enemies/BlastHornet/State/Appear/AppearSpriteSheet.png", 4, 9, 102, 104, 0.05, D3DCOLOR_XRGB(0, 128, 128));
		//anim->setAnim(36, 4, 9, 0.015, 0, false);
	}
	else if (state == BlastState::Attack)
	{
		anim = new Animation("Resources/Enemies/BlastHornet/State/Attack/attackspritesheet.png", 4, 9, 102, 104, 0.05, D3DCOLOR_XRGB(0, 128, 128));
		//anim->setAnim(36, 4, 9, 0.05, 0, false);
	}
	else if (state == BlastState::Shooter)
	{
		anim = new Animation("Resources/Enemies/BlastHornet/State/Shooter/shooterspirtesheet.png", 1, 15, 96, 96, 0.05, D3DCOLOR_XRGB(0, 128, 128));
		anim->SetAnimation(0, 15, 0.05, false);
	}
	else if (state == BlastState::Die)
	{
		anim = new Animation(Define::EXPLOSIONS, 1, 8, 35, 30, 0.05);
		anim->SetAnimation(0, 8, 0.05, false);
	}

	this->SetWidth(anim->GetWidth());
	this->SetHeight(anim->GetHeight());
}
