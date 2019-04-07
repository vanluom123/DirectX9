#ifndef __GAME_PLAYER_H__
#define __GAME_PLAYER_H__
#include "../Entity/Entity.h"
#include "../../GameComponents/Camera.h"
#include "../../GameComponents/Animation.h"
#include <map>
#include "PlayerBullet\PlayerBullet.h"
#include "../Bar/HPBar.h"
#include "../../GameComponents/Sound.h"
#include "../../PlayerData.h"

class GamePlayer : public Entity
{
public:
	GamePlayer();
	~GamePlayer();

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

	void SetState(GameState* newState);

	StateName GetStateName() const {
		return currentState; 
	}

	Animation* GetAnimation() const {
		return pAnimation; 
	}

	float GetHP() const {
		return HP; 
	}

	void SetHP(float hp) {
		HP = hp; 
	}

	void addHP(float hp) {
		HP += hp;
	}

	std::vector<PlayerBullet*>* getPlayerBullet() {
		return &listBullet;
	}

	void handlerKeyBoard(const map<int, bool>& keys, float dt);
	void onKeyDown(std::map<int, bool> keys, int Key);
	void onKeyUp(int Key);

	RECT GetBound() override;

	void Update(float dt) override;
	void Draw(Camera* camera, RECT rect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), float angle = 0.0f, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) override;
	void drawHP();

	void OnCollision(SideCollisions side) override;
	void OnNoCollisionWithBottom() override;
	void OnCollision(Entity* enemies) override;

	void PlayerShoot(PlayerBullet::BulletType bulletType);

	void SetLock(bool lock) {
		islock = lock;
	}

	PlayerData* GetPlayerData() const {
		return pData;
	}

protected:

	PlayerData* pData;

	Animation* pAnimation;
	Animation* pAniEfectCharge;
	Animation* pAniEfectDash;
	Animation* pAniEfectSlide;

	float				timeShoot;
	float				timeCurrentShoot;
	float				timeChangeShoot;
	float				timeAlive;

	bool				isShoot;
	bool				allowJump;
	bool				allowShoot;
	bool				allowDash;
	bool				alive;
	bool				islock;
	float				posSlideDown;

	StateName			currentState;
	HPBar* hpbar;
	std::vector<PlayerBullet*> listBullet;
};

#endif