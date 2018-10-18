#pragma once
#include "Player.h"
#include "PlayerState.h"

class PlayerJumpingState : public PlayerState
{
protected:
	float acceleratorY;
	float acceleratorX;
	bool noPressed;
	bool allowMoveRight, allowMoveLeft;

public:
	explicit PlayerJumpingState(PlayerData *playerData);
    ~PlayerJumpingState();

    void Update(float dt) override;

    void HandleKeyboard(std::map<int, bool> keys) override;

    void OnCollision(Entity::SideCollisions side, Entity::CollisionReturn data) override;

	StateName GetState() override;

};

