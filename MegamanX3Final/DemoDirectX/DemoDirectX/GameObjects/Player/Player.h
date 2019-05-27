#ifndef __GAME_PLAYER_H__
#define __GAME_PLAYER_H__
#include "../Entity/BaseObject.h"
#include "../../GameComponents/Camera.h"
#include "../../GameComponents/Animation.h"
#include <map>
#include "PlayerBullet\PlayerBullet.h"
#include "../Bar/HPBar.h"
#include "../../GameComponents/Sound.h"
#include "../../tagPlayerData.h"

class Player : public BaseObject
{
public:
	Player();
	~Player();

	enum StateName
	{
		APPEAR,
		STAND,
		RUN,
		FALL,
		JUMP,
		CLING,
		CLIMB,
		SLIP_DOWN,
		DASH,
		BLEED,
		WIN,
		DIE
	};

	void ChangeAnimation(StateName state);

	void handlerKeyBoard(const std::map<int, bool>& keys, float dt);
	void onKeyDown(std::map<int, bool> keys, int Key);
	void onKeyUp(int Key);

	RECT GetBound() override;

	void Update(float dt) override;
	void Draw(Camera* camera, RECT rect = RECT(), GVec2 scale = GVec2(), float angle = 0.0f, GVec2 rotationCenter = GVec2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) override;
	void drawHP();

	void OnCollision(eSideCollision side) override;
	void OnNoCollisionWithBottom() override;
	void OnCollision(BaseObject* enemies) override;

	void PlayerShoot(PlayerBullet::BulletType bulletType);

	// SUB-FUNCTION
public:

	void SetState(PlayerState* newState);

	Animation* GetAnimation() const;

	float GetHP() const;

	void SetHP(float hp);

	void addHP(float hp);

	std::vector<PlayerBullet*>* GetPlayerBullet();

	void SetLock(bool lock);

	PLAYERDATA* GetPlayerData() const;

private:

	// STRUCT PLAYER DATA
	PLAYERDATA* _playerData;

	Animation* _pAnimation;
	Animation* _pAniEfectCharge;
	Animation* _pAniEfectDash;
	Animation* _pAniEfectSlide;

	float _timeShoot;
	float _timeCurrentShoot;
	float _timeChangeShoot;
	float _timeAlive;

	bool _isShoot;
	bool _allowJump;
	bool _allowShoot;
	bool _allowDash;
	bool _alive;
	bool _islock;
	float _posSlideDown;

	StateName _currentState;
	HPBar* _hpbar;
	std::vector<PlayerBullet*> _listBullet;
};

#endif