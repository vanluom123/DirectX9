#include "HelitBullet.h"
#include "../../../../GameDefines/GameDefine.h"
#include "../../../../GameComponents/Camera.h"
#include "../../../../GameComponents/GameCollision.h"

HelitBullet::HelitBullet()
{
	tag = ENEMY_BULLET;
	anim = new Animation(Define::HELIT_BULLET, 1, 1, 15, 10);
	animExplosions = new Animation(Define::EXPLOSIONS, 1, 8, 35, 30);
	HP = 3;
	Damage = 2;
	HelitBullet::ChangeState(FIRE);

	isReverse = false;
	isDie = false;
	allowDraw = true;
	bulletX = 25.0f;
}

HelitBullet::~HelitBullet()
{
	delete anim;
	delete animExplosions;
}

void HelitBullet::NewEntity()
{
	if (isReverse == true)
	{
		SetReverse(true);
		SetVx(80);
		SetBulletX(25.0f);
	}
	else
	{
		SetReverse(false);
		SetVx(-80);
		SetBulletX(-25.0f);
	}

	ChangeState(FIRE);
	isDie = false;
	allowDraw = true;
}

RECT HelitBullet::GetBound()
{
	RECT r = RECT();

	switch (bulletState)
	{
	default:
	{
		r.left = x - 7;
		r.right = x + 8;
		r.top = y - 5;
		r.bottom = y + 5;
		break;
	}

	case EXPLOSIONS:
	{
		r.left = x - 25;
		r.right = x + 25;
		r.top = y - 22;
		r.bottom = y + 23;
		break;
	}
	}

	return r;
}

void HelitBullet::Update(float dt)
{
	if (allowDraw == false)
		return;

	if (isDie == false)
	{
		vx += bulletX;
		if (vx > 300)
			vx = 300;
		else if (vx < -300)
			vx = -300;
	}
	else if (anim->getPause() == true || animExplosions->getPause() == true)
		allowDraw = false;

	if (bulletState == EXPLOSIONS)
		animExplosions->update(dt);
	else
		anim->update(dt);

	Entity::Update(dt);
}

void HelitBullet::OnCollision(SideCollisions side)
{}

void HelitBullet::OnCollision(Entity * obj)
{
	if (obj->GetTag() == ENEMY)
		return;
	vx = 0;
	vy = 0;
	isDie = true;
	ChangeState(EXPLOSIONS);
}

void HelitBullet::Draw(Camera * camera, RECT rect, D3DXVECTOR2 scale, float angle, D3DXVECTOR2 rotationCenter,
	D3DCOLOR color)
{
	if (GameCollision::IsCollision(camera->getBound(), GetBound()) == false)
	{
		allowDraw = false;
		isDie = true;
	}

	if (allowDraw == false)
		return;

	switch (bulletState)
	{
	default:
	{
		anim->setReverse(isReverse);
		anim->setPosition(this->GetPosition());
		if (camera)
			anim->draw(anim->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
		else
			anim->draw(anim->getPosition());
		break;
	}

	case EXPLOSIONS:
	{
		animExplosions->setPosition(this->GetPosition());
		if (camera)
			animExplosions->draw(animExplosions->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
		else
			animExplosions->draw(animExplosions->getPosition());
		break;
	}
	}
}

void HelitBullet::ChangeState(BulletStateName state)
{
	bulletState = state;

	switch (state)
	{
	default:
	{
		anim->setAnimation(0, 1);
		this->SetWidth(anim->getWidth());
		this->SetHeight(anim->getHeight());
		break;
	}
	case EXPLOSIONS:
	{
		animExplosions->setAnimation(0, 8, 0.05, false);
		this->SetWidth(animExplosions->getWidth());
		this->SetHeight(animExplosions->getHeight());
		break;
	}
	}
}
