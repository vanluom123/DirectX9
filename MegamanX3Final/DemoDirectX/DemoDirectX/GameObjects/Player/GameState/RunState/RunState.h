#ifndef __RUN_STATE_H__
#define __RUN_STATE_H__
#include "../GameState.h"

class RunState : public GameState
{
public:
	explicit RunState(PlayerData* data);
	~RunState() = default;

	void handlerKeyBoard(std::map<int, bool> keys, float dt) override;

	void onCollision(Entity::SideCollisions side) override;

	GamePlayer::StateName GetState() override;

protected:
	bool boot;

};
#endif
