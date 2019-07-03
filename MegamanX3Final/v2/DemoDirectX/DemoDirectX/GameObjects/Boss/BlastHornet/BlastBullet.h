#ifndef BLAST_BULLET_H
#define BLAST_BULLET_H
#include "../../Enemies/Gunner/GunnerBullet/GunnerBullet.h"

class BlastBullet :public GunnerBullet
{
public:
	BlastBullet();
	~BlastBullet();

	RECT getBound() override;
	void newObject() override;
	void update(float dt) override;
	void onCollision(Side_Collision side) override;
	void onCollision(BaseObject* obj) override;
	void draw(Camera* camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter,
		D3DCOLOR color) override;

	void setState(EnemyBullet_State state) override;
};

#endif
