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
	void onCollision(Side_Collision side) override;
	void onCollision(BaseObject* obj) override;
	void setState(EnemyBullet_State state) override;
	virtual void changeAnimation(EnemyBullet_State state) override;

private:
	float _bulletY;	// The bullet translate to y axis
};
#endif // !BANGER_BULLET_H
