#pragma once
#include "PlayerState.h"
#include "Player.h"

class PlayerRunningState : public PlayerState
{
protected:
	float acceleratorX;

public:
	explicit PlayerRunningState(PlayerData *playerData);
    ~PlayerRunningState();

    void HandleKeyboard(std::map<int, bool> keys) override;

    void OnCollision(Entity::SideCollisions side, Entity::CollisionReturn data) override;

	StateName GetState() override;

};

