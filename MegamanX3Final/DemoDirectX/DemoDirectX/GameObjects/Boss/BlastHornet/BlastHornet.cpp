#include "BlastHornet.h"
#include "BlastDie.h"
#include "Move.h"
#include "BlastStand.h"
#include "BlastAppear.h"
#include "../../../GameDefines/GameDefine.h"

BlastHornet::BlastHornet()
{
	tag = Tag::BOSS;
	MaxHP = 30;
	Damage = 3;
	HP = MaxHP;
	curState = BlastState::None;
	hpbar = new HPBar(tag);

	pData = new BlastHornetData();
	pData->SetHornet(this);
	SetState(new BlastAppear(pData));
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
	r.left = x - 20;
	r.right = x + 30;
	r.top = y - 30;
	r.bottom = y + 45;
	return r;
}

void BlastHornet::Update(float dt)
{
	for (auto&i : list_bullets_)
		i->Update(dt);

	if (!allowDraw)
		return;

	anim->update(dt);
	Entity::Update(dt);

	if (pData->GetHornetState())
		pData->GetHornetState()->Update(dt);
}

void BlastHornet::OnCollision(SideCollisions side)
{
	if (pData->GetHornetState()) 
		pData->GetHornetState()->OnCollision(side);
}

void BlastHornet::OnCollision(Entity* obj)
{
	if (obj->GetTag() == Tag::ROCK_MAN_BULLET && !isDie)
	{
		HP -= 1 + obj->GetDamage() / 2;
			
		if (HP <= 0)
		{
			SetState(new BlastDie(pData));
			isDie = true;
		}
	}
}

void BlastHornet::Draw(Camera* camera, RECT r, D3DXVECTOR2 scale, float angle, D3DXVECTOR2 rotate, D3DCOLOR color)
{
	for (auto&i : list_bullets_)
		i->Draw(camera, r, scale, angle, rotate, color);

	hpbar->draw(HP, MaxHP);

	if (!allowDraw) return;

	anim->setPosition(GetPosition());
	anim->setReverse(isReverse);
	if (camera)
		anim->draw(anim->getPosition(), r, scale, camera->getTrans(), angle, rotate, color);
	else
		anim->draw(anim->getPosition());
}

void BlastHornet::SetState(BlastHornetState* newState)
{
	if (curState == newState->GetState())
		return;

	if (pData->GetHornetState()) {
		delete pData->GetHornetState();
		pData->SetHornetState(nullptr);
	}

	pData->SetHornetState(newState);
	curState = newState->GetState();
	ChangeAnimation(newState->GetState());
}

void BlastHornet::ChangeAnimation(BlastState state)
{
	if (state == BlastState::Stand || state == BlastState::Move)
	{
		anim = new Animation("Resources/Enemies/BlastHornet/State/Stand/standspritesheet.png", 1, 4, 96, 96, 0.05, D3DCOLOR_XRGB(0, 128, 128));
		anim->setAnimation(0, 4, 0.05);
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
		anim->setAnimation(0, 15, 0.05, false);
	}
	else if (state == BlastState::Die)
	{
		anim = new Animation(Define::EXPLOSIONS, 1, 8, 35, 30, 0.05);
		anim->setAnimation(0, 8, 0.05, false);
	}

	SetWidth(anim->getWidth());
	SetHeight(anim->getHeight());
}
