#ifndef __RUN_STATE_H__
#define __RUN_STATE_H__
#include "../PlayerState.h"

class RunState : public PlayerState
{
public:
	RunState(PlayerData* playerData);

	void KeyBoardEventHandler(std::map<int, bool> keys, float dt) override;

	void onCollision(BaseObject::eSideCollision side) override;

	Player::ePlayerState getState() override;

private:
	bool _isBoot;

};
#endif
