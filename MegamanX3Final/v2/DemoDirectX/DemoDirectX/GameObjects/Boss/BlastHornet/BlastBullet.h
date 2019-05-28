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
	void OnCollision(eSideCollision side) override;
	void OnCollision(BaseObject* obj) override;
	void Draw(Camera* camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter,
		D3DCOLOR color) override;

	void ChangeState(eBulletState state) override;
};

#endif
