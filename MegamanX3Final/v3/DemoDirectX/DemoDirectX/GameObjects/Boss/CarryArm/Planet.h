#ifndef PLANET_H
#define PLANET_H
#include "../../Entity/BaseObject.h"
#include "../../../GameComponents/Animation.h"
#include "../../../GameComponents/Camera.h"
#include "../../Player/Player.h"
#include "Pixton.h"
#include "CarryArm.h"

class Planet :public BaseObject
{
public:
	Planet(Player* gp);
	~Planet();

	RECT GetBound() override;
	void Draw(Camera* camera, RECT r = RECT(), GVec2 scale = GVec2(), float angle = 0, GVec2 rotate = GVec2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) override;
	void Update(float gameTime);
	void MoveDown(float gameTime);


private:
	Animation* m_anim;
	Animation* m_animAttack;
	Animation* m_animBullet;
	Pixton* m_pixton;
	float m_planetPosY;
	float m_planetPosX;
	float m_timeAttack;
	bool m_isMove;
	Player* m_rockMan;
	CarryArm* m_carryArm;
	Box* m_box1;
	Box* m_box2;
	bool m_isAttack;
	float m_timeplay;
};

#endif // !PLANET_H
