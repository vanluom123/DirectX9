#ifndef PLANET_H
#define PLANET_H
#include "../../Entity/BaseObject.h"
#include "../../../GameComponents/Animation.h"
#include "../../../GameComponents/Camera.h"
#include "../../Player/Player.h"
#include "Pixton.h"
#include "CarryArms.h"

class Planet :public BaseObject
{
private:
	Animation* anim;
	Animation* animAttack;
	Animation* animBullet;
	Pixton* pixton;
	float posY;
	float posX;
	float timeAttack;
	bool isMove;
	Player* rockman;
	CarryArms* carryArms;
	Box* box1;
	Box* box2;
	bool isAttack;
	float timeplay;
public:
	Planet(Player* gp);
	~Planet();
	RECT GetBound() override;
	void Draw(Camera* camera, RECT r = RECT(), GVec2 scale = GVec2(), float angle = 0, GVec2 rotate = GVec2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) override;
	void Update(float gameTime);
	void MoveDown(float gameTime);
};

#endif // !PLANET_H
