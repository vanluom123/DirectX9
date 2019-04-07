#include "BangerBullet.h"
#include "../../../../GameDefines/GameDefine.h"
#include "../../../../GameComponents/Camera.h"
#include "../../../../GameComponents/GameCollision.h"


BangerBullet::BangerBullet()
{
	tag = ENEMY_BULLET;
	anim = new Animation(Define::NOTOR_BANGER_BULLET, 2, 3, 8, 8, D3DCOLOR_XRGB(0, 100, 100));
	animExplosions = new Animation(Define::EXPLOSIONS, 1, 8, 35, 30, 0.1);
	BangerBullet::ChangeState(FIRE);
	HP = 3;
	Damage = 2;
	bulletY = 25.0f;

	allowDraw = true;
}

BangerBullet::~BangerBullet()
{
	delete anim;
	delete animExplosions;
}

RECT BangerBullet::GetBound()
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
		r.left = x - 4;
		r.top = y - 4;
		r.right = x + 4;
		r.bottom = y + 4;
		break;
	}

	return r;
}

void BangerBullet::NewEntity()
{
	tag = ENEMY_BULLET;
	vy = -450;
	if (isReverse == true)
	{
		//vx = 70;
		vx = 100;

	}
	else
	{
		//vx = -70;
		vx = -100;

	}
	ChangeState(FIRE);
	isDie = false;
	allowDraw = true;
}

void BangerBullet::Update(float dt)
{
	if (allowDraw == false)
		return;

	if (isDie == false)
	{
		vy += bulletY;
		if (vy > 300)
			vy = 300;

	}
	else if (anim->getPause() == true || animExplosions->getPause() == true)// da chay xong animation no
		allowDraw = false;

	if (bulletState == EXPLOSIONS)
		animExplosions->update(dt);
	else
		anim->update(dt);

	Entity::Update(dt);
}

void BangerBullet::OnCollision(SideCollisions side)
{}

void BangerBullet::OnCollision(Entity * obj)
{
	if (obj->GetTag() == ENEMY)
		return;
	vx = 0;
	vy = 0;
	isDie = true;
	ChangeState(EXPLOSIONS);
}

void BangerBullet::ChangeState(BulletStateName state)
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
		anim->setAnimation(0, 1);
		this->SetWidth(anim->getWidth());
		this->SetHeight(anim->getHeight());
		break;
	}
}