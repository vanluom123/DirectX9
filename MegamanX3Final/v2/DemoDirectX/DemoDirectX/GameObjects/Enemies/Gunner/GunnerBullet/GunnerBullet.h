#ifndef _HEAD_GUNNER_BULLET_H
#define _HEAD_GUNNER_BULLET_H
#include "../../../Entity/BaseObject.h"
#include "../../../../GameComponents/Animation.h"

class GunnerBullet : public BaseObject
{
public:

	GunnerBullet();
	~GunnerBullet();

	RECT getBound() override;
	void newObject()override;
	void update(float dt) override;
	void onCollision(Side_Collision side) override;
	void onCollision(BaseObject* obj) override;
	void draw(Camera* camera, RECT rect = RECT(), GVec2 scale = GVec2(), float angle = 0, GVec2 rotationCenter = GVec2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) override;
	void setBulletX(float bulletX) { this->_bulletX = bulletX; }

protected:
	virtual void setState(EnemyBullet_State state);

	Animation* _pAnim;
	Animation* _pAnimExplosion;
	float _bulletX, _timeFire;
	EnemyBullet_State _bulletState;
};

#endif
