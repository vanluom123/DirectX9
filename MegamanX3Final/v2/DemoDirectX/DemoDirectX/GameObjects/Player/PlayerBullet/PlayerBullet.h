#ifndef PLAYER_BULLET_H
#define PLAYER_BULLET_H

#include "../../Entity/BaseObject.h"
#include "../../../GameComponents/Animation.h"
#include "../../../GameComponents/Camera.h"

class PlayerBullet :public BaseObject
{
public:
	enum eBulletType
	{
		BULLET_TYPE_NORMAL,
		BULLET_TYPE_EXPLOSION_NORMAL,
		BULLET_TYPE_FIRST_LEVEL,
		BULLET_TYPE_EXPLOSION_FIRST_LEVEL,
		BULLET_TYPE_SECOND_LEVEL,
		BULLET_TYPE_EXPLOSION_SECOND_LEVEL
	};

	enum eBulletState
	{
		BULLET_STATE_FIRE,
		BULLET_STATE_EXPLOSION
	};

	PlayerBullet();
	~PlayerBullet();

	bool getExplosion() const { return _isExplosion; }
	void setBulletX(float bulletX) { this->_bulletX = bulletX; }

	void newBullet(float bx, float by, bool direction, eBulletType type);
	void changeBullet(eBulletState state, eBulletType type);

	RECT getBound() override;

	void draw(Camera* camera, RECT rect = RECT(), GVec2 scale = GVec2(), float angle = 0, GVec2 rotationCenter = GVec2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) override;
	void update(float dt) override;
	void onCollision(eSideCollision side) override;
	void onCollision(BaseObject* obj) override;

private:

	float			_bulletX;
	bool			_isExplosion;

	eBulletType		_bulletType;
	eBulletState	_bulletState;

	Animation*		_animation_bullet;
};
#endif // !PLAYER_BULLET_H
