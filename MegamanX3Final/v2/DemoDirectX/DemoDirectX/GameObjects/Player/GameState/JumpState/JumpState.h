#ifndef __JUMP_STATE_H__
#define __JUMP_STATE_H__
#include "../PlayerState.h"

class JumpState : public PlayerState
{
public:
	JumpState(PlayerData* playerData);

	void Update(float dt) override;
	void KeyBoardEventHandler(std::map<int, bool> keys, float dt) override;
	void onCollision(BaseObject::eSideCollision side) override;
	Player::ePlayerState getState() override;

private:
	float _accelerateY;
	bool _pressed;
	float _timePress;


};
#endif