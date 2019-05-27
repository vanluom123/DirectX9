#ifndef __RUN_STATE_H__
#define __RUN_STATE_H__
#include "../PlayerState.h"

class RunState : public PlayerState
{
public:
	RunState(PLAYERDATA* playerData);

	void KeyBoardEventHandler(std::map<int, bool> keys, float dt) override;

	void OnCollision(BaseObject::eSideCollision side) override;

	Player::ePlayerState GetState() override;

protected:
	bool boot;

};
#endif
