#ifndef PLANET_H
#define PLANET_H
#include "../../Entity/BaseObject.h"
#include "../../../GameComponents/Animation.h"
#include "../../Player/Player.h"
#include "Pixton.h"
#include "CarryArm.h"

class Planet :public BaseObject
{
public:
	Planet(Player* gp);
	~Planet();

	RECT getBound() override;
	void draw(Camera* camera, RECT r = RECT(), GVec2 scale = GVec2(), float angle = 0, GVec2 rotate = GVec2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) override;
	void update(float gameTime);
	void MoveDown(float gameTime);


private:
	Animation* _pAnim;
	Animation* _pAnimAttack;
	Animation* _pAnimBullet;
	Pixton* _pPixton;
	float _planetPosY;
	float _planetPosX;
	float _timeAttack;
	bool _isMove;
	Player* _pRockMan;
	CarryArm* _pCarryArm;
	Box* _pBox1;
	Box* _pBox2;
	bool _isAttack;
	float _timeplay;
};

#endif // !PLANET_H
