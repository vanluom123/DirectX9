#ifndef BANGER_BULLET_H
#define BANGER_BULLET_H
#include "../../../Entity/BaseObject.h"
#include "../../Gunner/GunnerBullet/GunnerBullet.h"

class BangerBullet :
	public GunnerBullet
{
public:
	BangerBullet();
	~BangerBullet();

	RECT getBound() override;
	void newObject() override;
	void update(float dt) override;
	void onCollision(eSideCollision side) override;
	void onCollision(BaseObject* obj) override;

protected:
	void setState(eBulletState state) override;

private:
	float _bulletY;	// The bullet translate to y axis
};
#endif // !BANGER_BULLET_H
