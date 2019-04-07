#include "GunnerBullet.h"
#include "../../../../GameDefines/GameDefine.h"
#include "../../../../GameComponents/Camera.h"
#include "../../../../GameComponents/GameCollision.h"

GunnerBullet::GunnerBullet()
{
	tag = ENEMY_BULLET;
	anim = new Animation(Define::HEAD_GUNNER_BULLET, 1, 2, 23, 7, 0.1);
	animExplosions = new Animation(Define::EXPLOSIONS, 1, 8, 35, 30, 0.1);

	isReverse = true;
	HP = 3;
	Damage = 3;
	bulletX = 25.0f;
	timeFire = 0.0f;

	GunnerBullet::ChangeState(FIRE);
}

GunnerBullet::~GunnerBullet()
{
	delete anim;
	delete animExplosions;
}

RECT GunnerBullet::GetBound()
{
	RECT r = RECT();

	switch (bulletState)
	{
	case EXPLOSIONS:
		r.left = x - 25;
		r.right = x + 25;
		r.top = y - 22;
		r.bottom = y + 23;
		break;

	default:
		r.left = x - 10;
		r.right = x + 13;
		r.top = y - 3;
		r.bottom = y + 4;
		break;	
	}

	return r;
}

void GunnerBullet::NewEntity()
{
	if (isReverse == false)
	{
		SetReverse(false);
		SetVx(-80);
		SetBulletX(-25.0f);
	}
	else
	{
		SetReverse(true);
		SetVx(80);
		SetBulletX(25.0f);
	}

	ChangeState(FIRE);
	isDie = false;
	allowDraw = true;
}

void GunnerBullet::Update(float dt)
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

void GunnerBullet::OnCollision(SideCollisions side)
{}

void GunnerBullet::OnCollision(Entity * obj)
{
	if (obj->GetTag() == ENEMY)
		return;

	vx = 0;
	vy = 0;
	isDie = true;
	ChangeState(EXPLOSIONS);
}

void GunnerBullet::Draw(Camera * camera, RECT rect, D3DXVECTOR2 scale, float angle, D3DXVECTOR2 rotationCenter,
	D3DCOLOR color)
{
	if (allowDraw == false)
		return;

	switch (bulletState)
	{
	case EXPLOSIONS:
		animExplosions->setPosition(this->GetPosition());
		if (camera)
			animExplosions->draw(animExplosions->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
		else
			animExplosions->draw(animExplosions->getPosition());
		break;

	default:
		anim->setReverse(isReverse);
		anim->setPosition(this->GetPosition());

		if (camera)
			anim->draw(anim->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
		else
			anim->draw(anim->getPosition());
		break;	
	}
}

void GunnerBullet::ChangeState(BulletStateName state)
{
	bulletState = state;

	switch (state)
	{
	case EXPLOSIONS:
		animExplosions->setAnimation(0, 8, 0.05, false);
		this->SetWidth(animExplosions->getWidth());
		this->SetHeight(animExplosions->getHeight());
		break;

	default:
		anim->setAnimation(0, 2);
		this->SetWidth(anim->getWidth());
		this->SetHeight(anim->getHeight());
		break;
	
	}
}
