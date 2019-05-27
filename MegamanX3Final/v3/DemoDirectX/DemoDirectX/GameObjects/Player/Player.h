#ifndef __GAME_PLAYER_H__
#define __GAME_PLAYER_H__
#include "../Entity/BaseObject.h"
#include "../../GameComponents/Camera.h"
#include "../../GameComponents/Animation.h"
#include <map>
#include "PlayerBullet\PlayerBullet.h"
#include "../Bar/HPBar.h"
#include "../../GameComponents/Sound.h"
#include "../../PlayerData.h"

class Player : public BaseObject
{
public:
	Player();
	~Player();

	enum ePlayerState
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

	void ChangeAnimation(ePlayerState state);

	void KeyBoardEventHandler(const std::map<int, bool>& keys, float dt);
	void OnKeyDown(std::map<int, bool> keys, int Key);
	void OnKeyUp(int Key);

	RECT GetBound() override;

	void Update(float dt) override;
	void Draw(Camera* camera, RECT rect = RECT(), GVec2 scale = GVec2(), float angle = 0.0f, GVec2 rotationCenter = GVec2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) override;
	void DrawHP();

	void OnCollision(eSideCollision side) override;
	void OnNoCollisionWithBottom() override;
	void OnCollision(BaseObject* enemies) override;

	void PlayerShoot(PlayerBullet::eBulletType bulletType);

	// SUB-FUNCTION
public:

	void SetState(PlayerState* newState);

	Animation* GetAnimation() const;

	float GetHP() const;

	void SetHP(float hp);

	void addHP(float hp);

	std::vector<PlayerBullet*>* GetPlayerBullet();

	void SetLock(bool lock);

	PlayerData* GetPlayerData() const;

	ePlayerState GetCurrentState() const;

private:

	// STRUCT PLAYER DATA
	PlayerData* m_playerData;

	Animation* m_animation;
	Animation* m_animationEfectCharge;
	Animation* m_animationEfectDash;
	Animation* m_animationEfectSlide;

	float m_timeShoot;
	float m_timeCurrentShoot;
	float m_timeChangeShoot;
	float m_timeAlive;

	bool m_isShoot;
	bool m_allowJump;
	bool m_allowShoot;
	bool m_allowDash;
	bool m_alive;
	bool m_islock;
	float m_posSlideDown;

	ePlayerState m_currentState;
	HPBar* m_HPBar;
	std::vector<PlayerBullet*> m_listPlayerBullet;
};

#endif