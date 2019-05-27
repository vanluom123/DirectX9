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

	RECT GetBound() override;
	void NewEntity() override;
	void Update(float dt) override;
	void OnCollision(eSideCollision side) override;
	void OnCollision(BaseObject* obj) override;

protected:
	void ChangeState(eBulletState state) override;

private:
	float m_bulletY;	// The bullet translate to y axis
};
#endif // !BANGER_BULLET_H
