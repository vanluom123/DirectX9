#include "BlastBullet.h"
#include "../../../GameComponents/Camera.h"

BlastBullet::BlastBullet()
{
	tag       = Tag::ENEMY_BULLET;
	isReverse = true;	
	Damage    = 3;
	MaxHP     = 4;
	HP        = MaxHP;

	BlastBullet::ChangeState(BulletStateName::FIRE);
}

BlastBullet::~BlastBullet()
{
	delete anim;
}

RECT BlastBullet::GetBound()
{
	RECT r;

	r.left = x - width / 2;
	r.top = y - height / 2;
	r.right = r.left + width;
	r.bottom = r.top + height;

	return r;
}

void BlastBullet::NewEntity()
{
	if (isReverse == false)
	{
		SetReverse(true);
		SetVx(-80);
	}
	else
	{
		SetReverse(false);
		SetVx(80);
	}

	//isBurst = false;
	allowDraw = true;
	ChangeState(BulletStateName::FIRE);
}

void BlastBullet::Update(float dt)
{
	if (allowDraw == false)
		return;

	//if (!isBurst)
	//{
	//	//vx += accelerateX;
	//	if (vx > 300)
	//		vx = 300;
	//	else if (vx < -300)
	//		vx = -300;
	//}
	//else if (anim->getPause())
	//	allowDraw = false;

	anim->update(dt);
	Entity::Update(dt);
}

void BlastBullet::OnCollision(SideCollisions side)
{
	vx = 0;
	vy = 0;
	//isBurst = true;
	ChangeState(BulletStateName::EXPLOSIONS);
}

void BlastBullet::OnCollision(Entity* obj)
{
	OnCollision(SideCollisions::NONE);
}

void BlastBullet::Draw(Camera* camera, RECT rect, D3DXVECTOR2 scale, float angle, D3DXVECTOR2 rotationCenter,
	D3DCOLOR color)
{
	if (allowDraw == false)
		return;

	anim->setPosition(GetPosition());
	anim->setReverse(isReverse);
	if (camera)
		anim->draw(GetPosition(), rect, scale, camera->getTrans(), 0, rotationCenter, color);
	else
		anim->draw(GetPosition());
}

void BlastBullet::ChangeState(BulletStateName state)
{
	switch (state)
	{
	case BulletStateName::EXPLOSIONS:
		anim = new Animation("Resources/Enemies/BlastHornet/Burst/BurstAnimation.png", 1, 6, 34, 34, 0.05, D3DCOLOR_XRGB(6, 113, 158));
		anim->setAnimation(0, 6, 0.05, false);
		break;

	default:
		anim = new Animation("Resources/Enemies/BlastHornet/Bullet/BulletAnim.png", 1, 3, 24, 22, 0.05, D3DCOLOR_XRGB(6, 113, 158));
		anim->setAnimation(0, 3);
		break;
	}

	width = anim->getWidth();
	height = anim->getHeight();

	bulletState = state;
}
