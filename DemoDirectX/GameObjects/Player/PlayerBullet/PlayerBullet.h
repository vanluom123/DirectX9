#ifndef PLAYER_BULLET_H
#define PLAYER_BULLET_H

#include "../../Entity/BaseObject.h"
#include "../../../GameComponents/Animation.h"
#include <map>

class PlayerBullet :
	public BaseObject
{
private:
	float _bulletX;
	bool _isExplosion;

	Enumerator::PlayerBullet_Type _bulletType;
	Enumerator::PlayerBullet_State _bulletState;

	Animation* m_pBullet;
	Animation* m_pBulletLevel1;
	Animation* m_pBulletLevel2;
	Animation* m_pExplosion;
	Animation* m_pExplosionLevel1;
	Animation* m_pExplosionLevel2;
	Animation* m_pCurrentAnimation;

public:

	PlayerBullet();
	~PlayerBullet();

	void newBullet(float bx, float by, bool direction, PlayerBullet_Type type);
	RECT getBound() override;
	void draw(Camera* camera, RECT rect = RECT(), GVec2 scale = GVec2(), float angle = 0, GVec2 rotationCenter = GVec2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) override;
	void update(float dt) override;
	void onCollision(BaseObject* obj) override;
	void changeBullet(PlayerBullet_State state, PlayerBullet_Type type);

	bool getExplosion() const;
	void setBulletX(float bulletX);

	// Getting bullet type
	PlayerBullet_Type getPlayerBulletType() const;

	// Load Animated Sprite
	void loadSprite();

};
#endif // !PLAYER_BULLET_H
