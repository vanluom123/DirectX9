#include "Gunner.h"
#include "../../../GameDefines/GameDefine.h"
#include "GunnerState/GunnerFall/GunnerFall.h"
#include "../../Player/GamePlayer.h"
#include "GunnerState/GunnerDie/GunnerDie.h"
#include "../../../GameComponents/GameCollision.h"
#include "../../Item/SmallBlood.h"
#include "../../Item/SmallSubtank.h"

Gunner::Gunner()
{
	tag = ENEMY;
	anim = new Animation(Define::HEAD_GUNNER_SPRITE, 4, 4, 51, 45, 0.15, D3DCOLOR_XRGB(100, 100, 100));
	animDie = new Animation(Define::EXPLOSIONS, 1, 8, 35, 30);
	isReverse = false;
	allowDraw = true;
	isDie = false;
	MaxHP = 6;
	Damage = 3;
	HP = MaxHP;
	curState = NONE;

	pData = new GunnerData();
	pData->SetGunner(this);
	SetState(new GunnerFall(pData));
}

void Gunner::NewEntity()
{
	x = startx;
	y = starty;
	isReverse = false;
	allowDraw = true;
	isDie = false;
	HP = MaxHP;
	curState = NONE;
	SetState(new GunnerFall(pData));
}

Gunner::~Gunner()
{
	delete anim;
	delete animDie;
	delete pData;
	for (auto& bullet : listBullet)
		delete bullet;
	listBullet.clear();
}

RECT Gunner::GetBound()
{
	RECT rect;

	rect.left = x - 15;
	rect.right = x + 15;
	rect.top = y - 21;
	rect.bottom = y + 45 / 2.0f;

	return rect;
}

void Gunner::Update(float dt)
{
	OnNoCollisionWithBottom();

	for (auto& bullet : listBullet)
		bullet->Update(dt);

	if (allowDraw == false)
		return;

	if (isDie == false)
		anim->update(dt);
	else
		animDie->update(dt);

	Entity::Update(dt);

	if (pData->GetGunnerState() != NULL)
		pData->GetGunnerState()->update(dt);
}

void Gunner::OnCollision(SideCollisions side)
{
	if (pData->GetGunnerState() != NULL)
		pData->GetGunnerState()->onCollision(side);
}

void Gunner::OnCollision(Entity * obj)
{
	if (obj->GetTag() == Entity::ROCK_MAN_BULLET && !isDie)
	{
		HP -= obj->GetDamage();
		if (HP <= 0)
		{
			isDie = true;
			this->SetState(new GunnerDie(pData));

			int num = (rand() % 999) % 4;
			if (num == 1)
			{
				auto* item = new SmallBloodItem();
				listBullet.push_back(item);
				item->SetPosition(x, y);
				item->SetTag(Entity::ITEM);
			}
			else if (num == 2)
			{
				auto* item = new SmallSubtank();
				listBullet.push_back(item);
				item->SetPosition(x, y);
				item->SetTag(Entity::ITEM);
			}
		}
	}
}

void Gunner::OnNoCollisionWithBottom()
{
	if (sideY != BOTTOM)
	{
		switch (curState)
		{
		case STAND:
		case ATTACK:
		case ATTACK_ROCKET:
		case ATTACK_BULLET:
			SetState(new GunnerFall(pData));
			break;
		default: break;
		}
	}
}

void Gunner::Draw(Camera * camera, RECT rect, D3DXVECTOR2 scale, float angle, D3DXVECTOR2 rotationCenter,
	D3DCOLOR color)
{
	if (isDie == false)
	{
		if (GameCollision::IsCollision(this->GetBound(), camera->getBound()) == false)
			allowDraw = false;
		else
			allowDraw = true;
	}

	for (auto& bullet : listBullet)
		bullet->Draw(camera);

	if (allowDraw == false)
		return;

	if (isDie == true)
	{
		animDie->setPosition(this->GetPosition());
		animDie->setReverse(isReverse);

		if (camera != NULL)
			animDie->draw(animDie->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
		else
			animDie->draw(animDie->getPosition());

		return;
	}

	anim->setPosition(this->GetPosition());
	anim->setReverse(isReverse);

	if (camera != NULL)
		anim->draw(anim->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
	else
		anim->draw(anim->getPosition());
}

void Gunner::ChangeAnimation(GunnerStateName stateName)
{
	switch (stateName)
	{
	case STAND:
		anim->setAnimation(0, 1);
		break;

	case ATTACK:
		anim->setAnimation(2, 3, 0.15, false);
		break;

	case ATTACK_ROCKET:
		anim->setAnimation(1, 3, 0.15, false);
		break;

	case ATTACK_BULLET:
		anim->setAnimation(0, 1);
		break;

	case FALL:
		anim->setAnimation(0, 1);
		break;

	case DIE:
		animDie->setAnimation(0, 8, 0.05, false);
		break;

	default: break;
	}

	this->SetWidth(anim->getWidth());
	this->SetHeight(anim->getHeight());
}

void Gunner::SetState(GunnerState * state)
{
	if (curState == state->getState())
		return;

	if (pData->GetGunnerState()) {
		delete pData->GetGunnerState();
		pData->SetGunnerState(nullptr);
	}

	pData->SetGunnerState(state);
	curState = state->getState();
	ChangeAnimation(state->getState());
}
