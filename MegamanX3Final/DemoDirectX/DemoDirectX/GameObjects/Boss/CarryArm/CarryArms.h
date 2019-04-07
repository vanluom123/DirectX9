#ifndef CARRY_ARM_H
#define CARRY_ARM_H
#include "../../Entity/Entity.h"
#include "../../../GameComponents/Animation.h"
#include "../../../GameComponents/Camera.h"
#include "Box.h"

enum class CarryArmsState
{
	STAND,
	MOVE_DOWN,
	MOVE_UP,
	EVENT_MOVE_UP,
	EVENT_MOVE_UP_2,
	NONE
};

class CarryArms :public Entity
{
protected:
	Animation* anim;
	CarryArmsState curState;
	Animation* pAnimationDie;
public:
	CarryArms();
	~CarryArms();
	Box* boxC;
	void Draw(Camera* camera, RECT r = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotateCenter = D3DXVECTOR2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) override;
	RECT GetBound() override;
	void Update(float dt) override;
	void OnCollision(Entity* obj) override;
	void SetState(CarryArmsState state);
	CarryArmsState GetState() { return curState; }
	void ManageState(float dt);
};

#endif // !CARRY_ARM_H
