#include "PlayerBullet.h"
#include "../../../GameDefines/GameDefine.h"
#include "../../../GameComponents/Camera.h"
#include "../../../GameComponents/GameCollision.h"

PlayerBullet::PlayerBullet()
{
	tag = ROCK_MAN_BULLET;
	bulletX = 25.0f;
}

PlayerBullet::~PlayerBullet()
{
	delete anim;
}

void PlayerBullet::newBullet(float bx, float by, bool direction, BulletType type)
{
	x             = bx;
	y             = by;
	allowDraw     = true;
	isExplosions  = false;
	bulletState   = FIRE;
	bulletType    = type;

	SetReverse(direction);
	if (direction == true)
		vx        = -300;
	else
		vx        = 300;

	changeBullet(FIRE, type);
}

void PlayerBullet::changeBullet(BulletState state, BulletType type)
{
	switch (state)
	{
		default: break;

		case FIRE:
		{
			switch (type)
			{
				case NORMAL:
					Damage = 1;
					anim = new Animation("Resources/rockman/bullet.png", 1, 1, 8, 6);
					break;

				case FIRST_LEVEL:
					Damage = 2;
					anim = new Animation("Resources/rockman/bullet_level_1.png", 1, 5, 46, 24, 0.15);
					break;

				case SECOND_LEVEL:
					Damage = 4;
					anim = new Animation("Resources/rockman/bullet_level_2.png", 1, 4, 46, 31, 0.15);
					break;

				default: break;
			}
		}
		case EXPLOSIONS:
		{
			switch (type)
			{
				case EXPLOSIONS_NORMAL:
					anim = new Animation("Resources/rockman/explosions_bullet.png", 1, 2, 15, 15, 0.15);
					anim->setLoopAnimation(false);
					break;

				case EXPLOSIONS_FIRST_LEVEL:
					anim = new Animation("Resources/rockman/explosion_level_1.png", 1, 2, 24, 24, 0.15);
					anim->setLoopAnimation(false);
					break;

				case EXPLOSIONS_SECOND_LEVEL:
					anim = new Animation("Resources/rockman/explosions_level_2.png", 1, 2, 24, 26, 0.15);
					anim->setLoopAnimation(false);
					break;

				default: break;
			}
		}
	}

	width = anim->getWidth();
	height = anim->getHeight();
}

RECT PlayerBullet::GetBound()
{
	RECT rect;

	rect.left = x - GetWidth() / 2.0f;
	rect.top = y - GetHeight() / 2.0f;
	rect.right = rect.left + GetWidth();
	rect.bottom = rect.top + GetHeight();

	return rect;
}

void PlayerBullet::Draw(Camera* camera, RECT rect, D3DXVECTOR2 scale, float angle, D3DXVECTOR2 rotationCenter,
	D3DCOLOR color)
{
	if (GameCollision::IsCollision(GetBound(), camera->getBound()) == false)
	{
		allowDraw = false;
		isExplosions = true;
	}

	if (allowDraw == false)
		return;

	anim->setReverse(isReverse);
	anim->setPosition(GetPosition());

	if (camera != NULL)
		anim->draw(GetPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
	else
		anim->draw(GetPosition());
}

void PlayerBullet::Update(float dt)
{
	if (allowDraw == false)
		return;

	if (isExplosions == false)
	{
		//vx += bulletX;
		//if (vx > 250)
		//	vx = 250;
		//else if (vx < -250)
		//	vx = -250;
	}
	else if (anim->getPause() == true)
		allowDraw = false;

	Entity::Update(dt);
	anim->update(dt);
}

void PlayerBullet::OnCollision(SideCollisions side)
{}

void PlayerBullet::OnCollision(Entity* obj)
{
	if (obj->GetTag() != ENEMY 
		&& obj->GetTag() != BOSS 
		&& obj->GetTag() != BOX)
		return;

	if (obj->GetHP() <= 0)
		return;

	isExplosions = true;
	vx = vy = 0;
	bulletState = EXPLOSIONS;

	switch (bulletType)
	{
		case NORMAL:
			bulletType = EXPLOSIONS_NORMAL;
			break;

		case FIRST_LEVEL:
			bulletType = EXPLOSIONS_FIRST_LEVEL;
			break;

		case SECOND_LEVEL:
			bulletType = EXPLOSIONS_SECOND_LEVEL;
			break;

		default: break;
	}

	changeBullet(bulletState, bulletType);
}