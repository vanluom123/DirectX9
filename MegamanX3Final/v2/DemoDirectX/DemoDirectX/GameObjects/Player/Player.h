#ifndef __GAME_PLAYER_H__
#define __GAME_PLAYER_H__
#include "../Entity/BaseObject.h"
#include "../../GameComponents/Camera.h"
#include "../../GameComponents/Animation.h"
#include <map>
#include "PlayerBullet\PlayerBullet.h"
#include "../Bar/HPBar.h"
#include "../../GameComponents/Sound.h"
#include "PlayerData.h"
#include <memory>

class Player : public BaseObject
{
public:
	Player();
	~Player();

	enum ePlayerState
	{
		APPEAR = 0,
		STAND = 1,
		RUN = 2,
		FALL = 3,
		JUMP = 4,
		CLING = 5,
		CLIMB = 6,
		SLIP_DOWN = 7,
		DASH = 8,
		BLEED = 9,
		WIN = 10,
		DIE = 11
	};

	void changeAnimation(ePlayerState state);

	void KeyBoardEventHandler(const std::map<int, bool>& keys, float dt);
	void OnKeyDown(std::map<int, bool> keys, int Key);
	void OnKeyUp(int Key);

	RECT getBound() override;

	void update(float dt) override;
	void draw(Camera* camera, RECT rect = RECT(), GVec2 scale = GVec2(), float angle = 0.0f, GVec2 rotationCenter = GVec2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) override;
	void DrawHP();

	void onCollision(eSideCollision side) override;
	void onNoCollisionWithBottom() override;
	void onCollision(BaseObject* enemies) override;

	void playerShoot(PlayerBullet::eBulletType bulletType);

	// SUB-FUNCTION
public:
	void setState(PlayerState* newState);
	Animation* getAnimation() const;
	float getHP() const;
	void setHP(float hp);
	void addHP(float hp);
	void setLock(bool lock);
	PlayerData* getPlayerData() const;
	ePlayerState getCurrentState() const;
	std::vector<PlayerBullet*>* getPlayerBullet();

private:

	// STRUCT PLAYER DATA
	PlayerData* _playerData;

	HPBar* _hpbar;
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

	ePlayerState _currentState;
	std::vector<PlayerBullet*> _listBullet;
};

#endif