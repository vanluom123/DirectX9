#ifndef BLAST_BULLET_H
#define BLAST_BULLET_H
#include "../../Enemies/Gunner/GunnerBullet/GunnerBullet.h"
#include "../../Player/Player.h"

class BlastBullet :
	public GunnerBullet
{
public:
	BlastBullet();
	~BlastBullet();

	RECT getBound() override;
	void newObject() override;
	void update(float dt) override;
	void onCollision(Side_Collision side) override;
	void onCollision(BaseObject* obj) override;
	void draw(Camera* camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter, D3DCOLOR color) override;
	void setState(EnemyBullet_State state) override;
	virtual void changeAnimation(EnemyBullet_State state) override;
	void loadSprite();

	Player* getPlayer() const;
	void setPlayer(Player* val);
private:
	// Delay time to hornet child explosion
	float _timeDelay;

	// Distance of Hornet child with Player
	GVec2 m_towardsPlayer;

	Player* m_pPlayer;
};

#endif
