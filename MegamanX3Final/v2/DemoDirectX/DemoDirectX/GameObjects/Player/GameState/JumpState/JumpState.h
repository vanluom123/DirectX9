#ifndef __JUMP_STATE_H__
#define __JUMP_STATE_H__
#include "../PlayerState.h"

class JumpState : public PlayerState
{
public:
	JumpState(PLAYERDATA* playerData);

	void Update(float dt) override;
	void KeyBoardEventHandler(std::map<int, bool> keys, float dt) override;
	void OnCollision(BaseObject::eSideCollision side) override;
	Player::ePlayerState GetState() override;

protected:
	float _accelerateY;
	bool _pressed;
	float _timePress;


};
#endif