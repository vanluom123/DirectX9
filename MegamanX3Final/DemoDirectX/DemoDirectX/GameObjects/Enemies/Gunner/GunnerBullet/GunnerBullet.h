#ifndef _HEAD_GUNNER_BULLET_H
#define _HEAD_GUNNER_BULLET_H
#include "../../../Entity/Entity.h"
#include "../../../../GameComponents/Animation.h"

class GunnerBullet :public Entity
{
public:
	enum BulletStateName
	{
		FIRE,
		EXPLOSIONS
	};

	GunnerBullet();
	~GunnerBullet();
	RECT GetBound() override;

	void NewEntity()override;
	void Update(float dt) override;
	void OnCollision(SideCollisions side) override;
	void OnCollision(Entity* obj) override;

	void Draw(Camera* camera, RECT rect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) override;

	void SetBulletX(float bulletX) { this->bulletX = bulletX; }

protected:
	virtual void ChangeState(BulletStateName state);

	Animation* anim;
	Animation* animExplosions;
	float bulletX, timeFire;
	BulletStateName	bulletState;
};

#endif
