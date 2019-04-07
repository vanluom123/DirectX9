#include "Banger.h"
#include "../../../GameDefines/GameDefine.h"
#include "BangerState/BangerFall/BangerFall.h"
#include "BangerState/BangerDie/BangerDie.h"
#include "BangerState/BangerStand/BangerStand.h"
#include "../../../GameComponents/GameCollision.h"
#include "../../Item/SmallBlood.h"
#include "../../Item/SmallSubtank.h"

Banger::Banger()
{
	tag = ENEMY;
	pAnimationDie = new Animation(Define::EXPLOSIONS, 1, 8, 35, 30);
	pCurrentAnim = new Animation(Define::NOTOR_BANGER_SPRITE, 3, 4, 48, 48);
	MaxHP = 4;
	HP = MaxHP;
	Damage = 3;
	isReverse = true;
	allowDraw = true;
	isDie = false;
	currentState = NONE;

	pData = new BangerData();
	pData->SetBanger(this);
	SetState(new BangerFall(pData));
}

void Banger::NewEntity()
{
	x = startx;
	y = starty;
	HP = MaxHP;
	isReverse = true;
	allowDraw = true;
	isDie = false;
	currentState = NONE;
	SetState(new BangerFall(pData));
}

Banger::~Banger()
{
	delete pData;
	delete pCurrentAnim;
	delete pAnimationDie;
	for (auto& bullet : listBullet)
		delete bullet;
	listBullet.clear();
}

void Banger::ChangeAnimation(BangerStateName state)
{
	switch (state)
	{
	case BangerStateName::STAND:
		pCurrentAnim->setAnimation(0, 2, 0.1);
		break;

	case BangerStateName::JUMP:
		pCurrentAnim->setAnimation(1, 2, 0.15, false);
		break;

	case BangerStateName::FALL:
		pCurrentAnim->setAnimation(1, 2, 0.15, false);
		break;

	case BangerStateName::ATTACK:
		pCurrentAnim->setAnimation(2, 3, 0.15, false);
		break;

	case DIE:
		pAnimationDie->setAnimation(0, 8, 0.05, false);
		break;

	default: break;
	}

	this->SetWidth(pCurrentAnim->getWidth());
	this->SetHeight(pCurrentAnim->getHeight());
}


void Banger::SetState(BangerState * newState)
{
	if (currentState == newState->GetStateName())
		return;

	if (pData->GetBangerState()) {
		delete pData->GetBangerState();
		pData->SetBangerState(nullptr);
	}

	pData->SetBangerState(newState);
	currentState = newState->GetStateName();
	ChangeAnimation(newState->GetStateName());
}

RECT Banger::GetBound()
{
	RECT r;

	r.left = x - 15;
	r.right = x + 15;
	r.top = y - 20;
	r.bottom = y + 48 / 2.0f;

	return r;
}

void Banger::Draw(Camera * camera, RECT rect, D3DXVECTOR2 scale, float angle, D3DXVECTOR2 rotationCenter, D3DCOLOR transColor)
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
		pAnimationDie->setPosition(GetPosition());

		if (camera != NULL)
			pAnimationDie->draw(pAnimationDie->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, transColor);
		else
			pAnimationDie->draw(pAnimationDie->getPosition());
	}
	else
	{
		pCurrentAnim->setReverse(isReverse);
		pCurrentAnim->setPosition(GetPosition());

		if (camera != NULL)
			pCurrentAnim->draw(pCurrentAnim->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, transColor);
		else
			pCurrentAnim->draw(pCurrentAnim->getPosition());
	}
}

void Banger::Update(float gameTime)
{
	OnNoCollisionWithBottom();

	for (auto& bullet : listBullet)
		bullet->Update(gameTime);

	if (allowDraw == false)
		return;

	pCurrentAnim->update(gameTime);
	pAnimationDie->update(gameTime);
	Entity::Update(gameTime);

	if (pData->GetBangerState() != NULL)
		pData->GetBangerState()->Update(gameTime);
}

void Banger::OnCollision(SideCollisions side)
{
	if (pData->GetBangerState() != NULL)
		pData->GetBangerState()->OnCollision(side);
}

void Banger::OnCollision(Entity * obj)
{
	if (obj->GetTag() == Entity::ROCK_MAN_BULLET && !isDie)
	{
		HP -= obj->GetDamage();
		if (HP <= 0)
		{
			isDie = true;
			this->SetState(new BangerDie(pData));

			//
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

void Banger::OnNoCollisionWithBottom()
{
	if (sideY != BOTTOM)
	{
		switch (currentState)
		{
		case STAND:
		case ATTACK:
			SetState(new BangerFall(pData));
			break;
		default:break;
		}
	}
}
