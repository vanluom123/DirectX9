#ifndef HELIT_BULLET_H
#define HELIT_BULLET_H
#include "../../Gunner/GunnerBullet/GunnerBullet.h"

class HelitBullet :public GunnerBullet
{
public:
	HelitBullet();
	~HelitBullet();

	void newObject() override;
	RECT getBound() override;
	void update(float dt) override;
	void onCollision(eSideCollision side) override;
	void onCollision(BaseObject* obj) override;
	void draw(Camera* camera, RECT rect = RECT(), GVec2 scale = GVec2(), float angle = 0, GVec2 rotationCenter = GVec2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) override;

protected:
	void setState(eBulletState state) override;

};

#endif
