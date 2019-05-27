#ifndef PLAYER_BULLET_H
#define PLAYER_BULLET_H

#include "../../Entity/BaseObject.h"
#include "../../../GameComponents/Animation.h"
#include "../../../GameComponents/GameDebugDraw.h"

class Camera;

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

	bool GetExplosion() const { return m_isExplosion; }
	void SetBulletX(float bulletX) { this->m_playerBulletX = bulletX; }

	void NewBullet(float bx, float by, bool direction, eBulletType type);
	void ChangeBullet(eBulletState state, eBulletType type);

	RECT GetBound() override;

	void Draw(Camera* camera, RECT rect = RECT(), GVec2 scale = GVec2(), float angle = 0, GVec2 rotationCenter = GVec2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) override;
	void Update(float dt) override;
	void OnCollision(eSideCollision side) override;
	void OnCollision(BaseObject* obj) override;

private:

	float			m_playerBulletX;
	bool			m_isExplosion;

	eBulletType		m_playerBulletType;
	eBulletState	m_playerBulletState;

	Animation*		m_anim;

	GameDebugDraw* m_gameDebug;
};
#endif // !PLAYER_BULLET_H
