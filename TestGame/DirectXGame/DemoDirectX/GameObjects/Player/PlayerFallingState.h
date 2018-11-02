#pragma once
#include "PlayerState.h"


class PlayerFallingState : public PlayerState
{
protected:
	float acceleratorY;
	float acceleratorX;

	//First Velocity equal zero in case speed won't decrease 
	bool allowMoveX;

	bool isLeftOrRightKeyPressed;

public:
	explicit PlayerFallingState(PlayerData *playerData);
    ~PlayerFallingState();

    void Update(float dt) override;

    void HandleKeyboard(std::map<int, bool> keys) override;

    void OnCollision(Entity::SideCollisions side, Entity::CollisionReturn data) override;

	StateName GetState() override;

};

