#ifndef CARRY_ARM_H
#define CARRY_ARM_H
#include "../../Entity/BaseObject.h"
#include "../../../GameComponents/Animation.h"
#include "../../../GameComponents/Camera.h"
#include "Box.h"

enum class eCarryArmState
{
	CARRY_ARM_STAND,
	CARRY_ARM_MOVE_DOWN,
	CARRY_ARM_MOVE_UP,
	CARRY_ARM_EVENT_MOVE_UP,
	CARRY_ARM_EVENT_MOVE_UP_2,
	CARRY_ARM_NONE
};

class CarryArm :public BaseObject
{
public:
	CarryArm();
	~CarryArm();

	Box* boxC;
	void Draw(Camera* camera, RECT r = RECT(), GVec2 scale = GVec2(), float angle = 0, GVec2 rotateCenter = GVec2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) override;
	RECT GetBound() override;
	void Update(float dt) override;
	void OnCollision(BaseObject* obj) override;
	void SetState(eCarryArmState state);
	eCarryArmState GetState() { return _curState; }
	void UpdateState(float dt);

private:
	Animation* _pAnim;
	eCarryArmState _curState;
	Animation* _pAnimDie;
};

#endif // !CARRY_ARM_H
