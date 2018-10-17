#ifndef _PLAYER_RUNNING_STATE_H
#define _PLAYER_RUNNING_STATE_H
#include "PlayerState.h"
#include "Player.h"

class PlayerRunningState : public PlayerState
{
	float acceleratorX;

public:
	explicit  PlayerRunningState(PlayerData* playerData);

	void HandlerKeyBoard(std::map<int, bool> keys) override;

	StateName GetState() override;

	void OnCollision(Entity* Impact, Entity::CollisionReturn data, Entity::SideCollision side) override;

	~PlayerRunningState();

};

#endif