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
	_currentState = eBlastState::BLAST_STATE_UNKNOWN;
	_pHPBar = new HPBar(_objectType);

	_pBlastHornetData = new BlastHornetData;
	_pBlastHornetData->blastHornet = this;
	_pBlastHornetData->blastHornetState = NULL;

	this->SetState(new BlastAppear(_pBlastHornetData));
}


BlastHornet::~BlastHornet()
{
	delete _pAnim;
	delete _pBlastHornetData;
	for (auto&i : _listBullet)
		delete i;
	_listBullet.clear();
}

RECT BlastHornet::GetBound()
{
	RECT bound;
	bound.left = _posX - 20;
	bound.right = _posX + 30;
	bound.top = _posY - 30;
	bound.bottom = _posY + 45;
	return bound;
}

void BlastHornet::Update(float dt)
{
	for (auto&i : _listBullet)
		i->Update(dt);

	if (!_isAllowDraw)
		return;

	_pAnim->Update(dt);
	BaseObject::Update(dt);

	if (_pBlastHornetData->blastHornetState)
		_pBlastHornetData->blastHornetState->Update(dt);
}

void BlastHornet::OnCollision(eSideCollision side)
{
	if (_pBlastHornetData->blastHornetState) 
		_pBlastHornetData->blastHornetState->OnCollision(side);
}

void BlastHornet::OnCollision(BaseObject* obj)
{
	if (obj->GetObjectType() == eObjectType::ROCK_MAN_BULLET && !_isDie)
	{
		_HP -= 1 + obj->GetDamage() / 2;
			
		if (_HP <= 0)
		{
			SetState(new BlastDie(_pBlastHornetData));
			_isDie = true;
		}
	}
}

void BlastHornet::Draw(Camera* camera, RECT r, GVec2 scale, float angle, GVec2 rotate, D3DCOLOR color)
{
	for (auto& i : _listBullet)
		i->Draw(camera, r, scale, angle, rotate, color);

	_pHPBar->draw(_HP, _MaxHP);

	if (!_isAllowDraw)
		return;

	_pAnim->SetPosition(GetPosition());
	_pAnim->SetReverse(_isReverse);
	if (camera)
		_pAnim->Draw(_pAnim->GetPosition(), r, scale, camera->GetTrans(), angle, rotate, color);
	else
		_pAnim->Draw(_pAnim->GetPosition());
}

void BlastHornet::SetState(BlastHornetState* newState)
{
	if (_currentState == newState->GetState())
		return;

	SAFE_DELETE(_pBlastHornetData->blastHornetState);
	_pBlastHornetData->blastHornetState = newState;
	_currentState = newState->GetState();
	ChangeAnimation(newState->GetState());
}

void BlastHornet::ChangeAnimation(eBlastState state)
{
	if (state == eBlastState::BLAST_STATE_STAND || state == eBlastState::BLAST_STATE_MOVE)
	{
		_pAnim = new Animation("Resources/Enemies/BlastHornet/State/Stand/standspritesheet.png", 1, 4, 96, 96, 0.05, D3DCOLOR_XRGB(0, 128, 128));
		_pAnim->SetAnimation(0, 4, 0.05);
	}
	else if (state == eBlastState::BLAST_STATE_APPEAR)
	{
		_pAnim = new Animation("Resources/Enemies/BlastHornet/State/Appear/AppearSpriteSheet.png", 4, 9, 102, 104, 0.05, D3DCOLOR_XRGB(0, 128, 128));
		//anim->setAnim(36, 4, 9, 0.015, 0, false);
	}
	else if (state == eBlastState::BLAST_STATE_ATTACK)
	{
		_pAnim = new Animation("Resources/Enemies/BlastHornet/State/Attack/attackspritesheet.png", 4, 9, 102, 104, 0.05, D3DCOLOR_XRGB(0, 128, 128));
		//anim->setAnim(36, 4, 9, 0.05, 0, false);
	}
	else if (state == eBlastState::BLAST_STATE_SHOOTER)
	{
		_pAnim = new Animation("Resources/Enemies/BlastHornet/State/Shooter/shooterspirtesheet.png", 1, 15, 96, 96, 0.05, D3DCOLOR_XRGB(0, 128, 128));
		_pAnim->SetAnimation(0, 15, 0.05, false);
	}
	else if (state == eBlastState::BLAST_STATE_DIE)
	{
		_pAnim = new Animation(Define::EXPLOSIONS, 1, 8, 35, 30, 0.05);
		_pAnim->SetAnimation(0, 8, 0.05, false);
	}

	this->SetWidth(_pAnim->GetWidth());
	this->SetHeight(_pAnim->GetHeight());
}

Animation* BlastHornet::GetAnimation() const
{
	return _pAnim;
}

std::vector<BlastBullet*>* BlastHornet::GetListBullet()
{
	return &_listBullet;
}
