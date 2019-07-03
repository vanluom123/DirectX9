#ifndef PLAYER_H
#define PLAYER_H

#include "PlayerBullet/PlayerBullet.h"
#include "../Bar/HPBar.h"
#include "../../GameComponents/Sound.h"


class PlayerState;

class Player : public BaseObject
{
public:
	Player();
	~Player();

	void changeAnimation(Player_State state);
	void KeyBoardEventHandler(const map<int, bool>& keys, float dt);
	void OnKeyDown(map<int, bool> keys, int Key);
	void OnKeyUp(int Key);
	RECT getBound() override;
	void update(float dt) override;
	void draw(Camera* camera, RECT rect = RECT(), GVec2 scale = GVec2(), float angle = 0.0f, GVec2 rotationCenter = GVec2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) override;
	void drawHP();
	void onCollision(Side_Collision side) override;
	void onNoCollisionWithBottom() override;
	void onCollision(BaseObject* object) override;
	void playerShoot(PlayerBullet_Type bulletType);

	// SUB-FUNCTION
public:
	void setState(PlayerState* new_state);
	Animation* getAnimation();
	int getHP() const override;
	void setHP(int hp);
	void addHP(int hp);
	void setLock(bool lock);
	Player_State getCurrentState() const;
	vector<PlayerBullet*>* getPlayerBullet();
	PlayerState* getPlayerState();

private:
	PlayerState* m_pState;

	HPBar* _pHPBar;
	Animation* _pAnimation;
	Animation* _pAniEffectCharge;
	Animation* _pAniEffectDash;
	Animation* _pAniEffectSlide;

	float _timeShoot;
	float _timeCurrentShoot;
	float _timeChangeShoot;
	float _timeAlive;

	bool _isShoot;
	bool _allowJump;
	bool _allowShoot;
	bool _allowDash;
	bool _alive;
	bool _isLock;
	float _posSlideDown;

	Player_State _currentState;
	vector<PlayerBullet*> _listPlayerBullet;
};

#endif