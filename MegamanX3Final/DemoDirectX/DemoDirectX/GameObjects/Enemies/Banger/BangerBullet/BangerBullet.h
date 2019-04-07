#ifndef BANGER_BULLET_H
#define BANGER_BULLET_H
#include "../../../Entity/Entity.h"
#include "../../Gunner/GunnerBullet/GunnerBullet.h"

class BangerBullet :
	public GunnerBullet
{
public:
	BangerBullet();
	~BangerBullet();

	RECT GetBound() override;
	void NewEntity() override;
	void Update(float dt) override;
	void OnCollision(SideCollisions side) override;
	void OnCollision(Entity* obj) override;

protected:
	void ChangeState(BulletStateName state) override;

private:
	float bulletY;	// The bullet translate to y axis
};
#endif // !BANGER_BULLET_H
