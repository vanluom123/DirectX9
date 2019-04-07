#ifndef PLANET_H
#define PLANET_H
#include "../../Entity/Entity.h"
#include "../../../GameComponents/Animation.h"
#include "../../../GameComponents/Camera.h"
#include "../../Player/GamePlayer.h"
#include "Pixton.h"
#include "CarryArms.h"

class Planet :public Entity
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
	GamePlayer* rockman;
	CarryArms* carryArms;
	Box* box1;
	Box* box2;
	bool isAttack;
	float timeplay;
public:
	Planet(GamePlayer* gp);
	~Planet();
	RECT GetBound() override;
	void Draw(Camera* camera, RECT r = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotate = D3DXVECTOR2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) override;
	void Update(float gameTime);
	void MoveDown(float gameTime);
};

#endif // !PLANET_H
