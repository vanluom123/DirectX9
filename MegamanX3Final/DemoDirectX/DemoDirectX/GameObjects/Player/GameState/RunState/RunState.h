#ifndef __RUN_STATE_H__
#define __RUN_STATE_H__
#include "../PlayerState.h"

class RunState : public PlayerState
{
public:
	RunState(PLAYERDATA* playerData);

	void handlerKeyBoard(std::map<int, bool> keys, float dt) override;

	void onCollision(BaseObject::eSideCollision side) override;

	Player::StateName GetState() override;

protected:
	bool boot;

};
#endif
