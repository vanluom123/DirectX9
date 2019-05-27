#ifndef _HEAD_GUNNER_BULLET_H
#define _HEAD_GUNNER_BULLET_H
#include "../../../Entity/BaseObject.h"
#include "../../../../GameComponents/Animation.h"

class GunnerBullet :public BaseObject
{
public:
	enum eBulletState
	{
		BULLET_FIRE,
		BULLET_EXPLOSION
	};

	GunnerBullet();
	~GunnerBullet();

	RECT GetBound() override;

	void NewEntity()override;
	void Update(float dt) override;
	void OnCollision(eSideCollision side) override;
	void OnCollision(BaseObject* obj) override;

	void Draw(Camera* camera, RECT rect = RECT(), GVec2 scale = GVec2(), float angle = 0, GVec2 rotationCenter = GVec2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) override;

	void SetBulletX(float bulletX) { this->m_bulletX = bulletX; }

protected:
	virtual void ChangeState(eBulletState state);

	Animation* m_anim;
	Animation* m_animExplosion;
	float m_bulletX, m_timeFire;
	eBulletState m_bulletState;
};

#endif
