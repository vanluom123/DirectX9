#ifndef PLAYER_BULLET_H
#define PLAYER_BULLET_H

#include "../../Entity/Entity.h"
#include "../../../GameComponents/Animation.h"

class Camera;

class PlayerBullet :public Entity
{
public:
	enum BulletType
	{
		NORMAL,
		EXPLOSIONS_NORMAL,
		FIRST_LEVEL,
		EXPLOSIONS_FIRST_LEVEL,
		SECOND_LEVEL,
		EXPLOSIONS_SECOND_LEVEL
	};

	enum BulletState
	{
		FIRE,
		EXPLOSIONS
	};

	PlayerBullet();
	~PlayerBullet();

	bool getExplosions() const { return isExplosions; }
	void setBulletX(float bulletX) { this->bulletX = bulletX; }

	void newBullet(float bx, float by, bool direction, BulletType type);
	void changeBullet(BulletState state, BulletType type);

	RECT GetBound() override;

	void Draw(Camera* camera, RECT rect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) override;
	void Update(float dt) override;
	void OnCollision(SideCollisions side) override;
	void OnCollision(Entity* obj) override;

protected:

	float			bulletX;
	bool			isExplosions;

	BulletType		bulletType;
	BulletState		bulletState;

	Animation* anim;
};
#endif // !PLAYER_BULLET_H
