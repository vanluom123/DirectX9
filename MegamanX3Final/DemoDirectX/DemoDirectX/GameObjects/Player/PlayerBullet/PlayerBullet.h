#ifndef PLAYER_BULLET_H
#define PLAYER_BULLET_H

#include "../../Entity/BaseObject.h"
#include "../../../GameComponents/Animation.h"
#include "../../../GameComponents/GameDebugDraw.h"

class Camera;

class PlayerBullet :public BaseObject
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

	bool GetExplosion() const { return _isExplosions; }
	void SetBulletX(float bulletX) { this->_bulletX = bulletX; }

	void NewBullet(float bx, float by, bool direction, BulletType type);
	void ChangeBullet(BulletState state, BulletType type);

	RECT GetBound() override;

	void Draw(Camera* camera, RECT rect = RECT(), GVec2 scale = GVec2(), float angle = 0, GVec2 rotationCenter = GVec2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) override;
	void Update(float dt) override;
	void OnCollision(eSideCollision side) override;
	void OnCollision(BaseObject* obj) override;

private:

	float			_bulletX;
	bool			_isExplosions;

	BulletType		_bulletType;
	BulletState		_bulletState;

	Animation* _pAnim;

	GameDebugDraw* _gameDebug;
};
#endif // !PLAYER_BULLET_H
