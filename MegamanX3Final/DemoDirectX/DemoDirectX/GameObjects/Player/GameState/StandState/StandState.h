#ifndef __STAND_STATE_H__
#define __STAND_STATE_H__
#include "../GameState.h"

class StandState : public GameState
{
protected:
	float timeStand;
	bool isMove;

public:
	explicit StandState(PlayerData* data);
	~StandState() = default;

	void update(float dt) override;
	void handlerKeyBoard(std::map<int, bool> keys, float dt) override;
	void onCollision(Entity::SideCollisions side) override;
	GamePlayer::StateName GetState() override;
};
#endif