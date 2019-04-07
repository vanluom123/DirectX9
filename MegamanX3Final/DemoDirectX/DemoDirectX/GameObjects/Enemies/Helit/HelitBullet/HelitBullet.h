#ifndef HELIT_BULLET_H
#define HELIT_BULLET_H
#include "../../Gunner/GunnerBullet/GunnerBullet.h"

class HelitBullet :public GunnerBullet
{
public:
	HelitBullet();
	~HelitBullet();

	void NewEntity() override;
	RECT GetBound() override;
	void Update(float dt) override;
	void OnCollision(SideCollisions side) override;
	void OnCollision(Entity* obj) override;
	void Draw(Camera* camera, RECT rect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) override;

protected:
	void ChangeState(BulletStateName state) override;

private:
	BulletStateName bulletState;
	Animation* animExplosions;
};

#endif
