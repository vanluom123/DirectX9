#ifndef BLAST_BULLET_H
#define BLAST_BULLET_H
#include "../../Enemies/Gunner/GunnerBullet/GunnerBullet.h"

class BlastBullet :public GunnerBullet
{
public:
	BlastBullet();
	~BlastBullet();

	RECT GetBound() override;
	void NewEntity() override;
	void Update(float dt) override;
	void OnCollision(SideCollisions side) override;
	void OnCollision(Entity* obj) override;
	void Draw(Camera* camera, RECT rect, D3DXVECTOR2 scale, float angle, D3DXVECTOR2 rotationCenter,
		D3DCOLOR color) override;

	void ChangeState(BulletStateName state) override;
};

#endif
