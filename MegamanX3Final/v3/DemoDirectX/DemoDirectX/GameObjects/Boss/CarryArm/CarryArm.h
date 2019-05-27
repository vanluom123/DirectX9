#ifndef CARRY_ARM_H
#define CARRY_ARM_H
#include "../../Entity/BaseObject.h"
#include "../../../GameComponents/Animation.h"
#include "../../../GameComponents/Camera.h"
#include "Box.h"


class CarryArm :public BaseObject
{
public:

	enum eCarryArmState
	{
		CARRY_ARM_STAND,
		CARRY_ARM_MOVE_DOWN,
		CARRY_ARM_MOVE_UP,
		CARRY_ARM_EVENT_MOVE_UP,
		CARRY_ARM_EVENT_MOVE_UP_2,
		CARRY_ARM_UNKNOWN
	};

	CarryArm();
	~CarryArm();

	void Draw(Camera* camera, RECT r = RECT(), GVec2 scale = GVec2(), float angle = 0, GVec2 rotateCenter = GVec2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) override;
	RECT GetBound() override;
	void Update(float dt) override;
	void OnCollision(BaseObject* obj) override;
	void SetState(eCarryArmState state);
	eCarryArmState GetState() { return m_currentState; }
	void UpdateState(float dt);

private:
	Animation* m_anim;
	eCarryArmState m_currentState;
	Animation* m_animDie;
};

#endif // !CARRY_ARM_H
