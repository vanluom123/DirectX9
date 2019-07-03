#ifndef CARRY_ARM_H
#define CARRY_ARM_H
#include "../../Entity/BaseObject.h"
#include "../../../GameComponents/Animation.h"
#include "../../../GameComponents/Camera.h"
#include "Box.h"


class CarryArm :public BaseObject
{
public:
	CarryArm();
	~CarryArm();

	Box* boxC;
	void draw(Camera* camera, RECT r = RECT(), GVec2 scale = GVec2(), float angle = 0, GVec2 rotateCenter = GVec2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) override;
	RECT getBound() override;
	void update(float dt) override;
	void onCollision(BaseObject* obj) override;
	void setState(Carry_State state);
	Carry_State getState();
	void updateState(float dt);

private:
	Animation* _pAnim;
	Carry_State _curState;
	Animation* _pAnimDie;
};

#endif // !CARRY_ARM_H
