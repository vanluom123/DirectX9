#include "Helit.h"
#include "../../../GameDefines/GameDefine.h"
#include "HelitState/HelitDie/HelitDie.h"
#include "HelitState/HelitStand/HelitStand.h"
#include "../../../GameComponents/GameCollision.h"
#include "../../Item/SmallBlood.h"
#include "../../Item/SmallSubtank.h"

Helit::Helit()
{
	tag          = ENEMY;
	anim         = new Animation(Define::HELIT_SPRITE_SHEET, 2, 4, 39, 37, 0.1, D3DCOLOR_XRGB(100, 100, 100));
	animDie      = new Animation(Define::EXPLOSIONS, 1, 8, 35, 30);
	isReverse    = false;
	isDie        = false;
	allowDraw    = true;
	MaxHP        = 4;
	HP           = MaxHP;
	Damage       = 3;
	currentState = None;

	pData		 = new HelitData();
	pData->SetHelit(this);
	setState(new HelitStand(pData));
}

void Helit::NewEntity()
{
	x            = startx;
	y            = starty;
	
	isReverse    = false;
	isDie        = false;
	allowDraw    = true;
	HP           = MaxHP;
	currentState = None;
	setState(new HelitStand(pData));
}

Helit::~Helit()
{
	delete pData;
	delete anim;
	delete animDie;
	for (auto& bullet : listBullet)
		delete bullet;
	listBullet.clear();
}

RECT Helit::GetBound()
{
	RECT r;

	r.left   = x - 19;
	r.right  = x + 19;
	r.top    = y - 18;
	r.bottom = y + 37 / 2.0f;

	return r;
}

void Helit::Update(float dt)
{
	for (auto& bullet : listBullet)
		bullet->Update(dt);

	if (allowDraw == false)
		return;

	Entity::Update(dt);

	if (isDie == true)
		animDie->update(dt);
	else
		anim->update(dt);

	if (pData->GetHelitState() != NULL)
		pData->GetHelitState()->update(dt);
}

void Helit::OnCollision(Entity* obj)
{
	if (obj->GetTag() == Entity::ROCK_MAN_BULLET && isDie == false)
	{
		HP -= obj->GetDamage();
		if (HP <= 0)
		{
			isDie = true;
			setState(new HelitDie(pData));
		}

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

void Helit::Draw(Camera* camera, RECT rect, D3DXVECTOR2 scale, float angle, D3DXVECTOR2 rotationCenter, D3DCOLOR color)
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

		if (camera != NULL)
			animDie->draw(animDie->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
		else
			animDie->draw(animDie->getPosition());
	}
	else
	{
		anim->setReverse(isReverse);
		anim->setPosition(this->GetPosition());

		if (camera != NULL)
			anim->draw(anim->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
		else
			anim->draw(anim->getPosition());
	}
}

void Helit::setState(HelitState* newState)
{
	if (currentState == newState->getState())
		return;

	if (pData->GetHelitState()) {
		delete pData->GetHelitState();
		pData->SetHelitState(nullptr);
	}

	pData->SetHelitState(newState);
	currentState = newState->getState();
	changeAnimation(newState->getState());
}

void Helit::changeAnimation(StateName state)
{
	switch (state)
	{
			case Stand:
				anim->setAnimation(0, 4, 0.15);
				anim->setFrames(39, 36);
				break;

			case Attack:
				anim->setAnimation(1, 4, 0.15);
				anim->setFrames(39, 36);
				break;

			case Die:
				animDie->setAnimation(0, 8, 0.05, false);
				break;

			default: break;
	}
	
	width = anim->getWidth();
	height = anim->getHeight();
}