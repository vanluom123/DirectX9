#ifndef __DASH_STATE_H__
#define __DASH_STATE_H__
#include "../GameState.h"

class DashState : public GameState
{
public:
	explicit DashState(PlayerData* data);
	~DashState() = default;

	void handlerKeyBoard(std::map<int, bool> keys, float dt) override;

	void onCollision(Entity::SideCollisions side) override;

	GamePlayer::StateName GetState() override;

protected:
	float translateX;
	float timePress;

};
#endif