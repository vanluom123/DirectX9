#pragma once
#include "../GameState.h"

class GamePlayer;

class RunState : public GameState
{
	float accelerationX;
public:
	RunState() = default;
	explicit RunState(GamePlayer *gp);
	~RunState() override = default;

	void Update(float dt) override;
	void HandleKeyboard(std::map<int, bool> keys) override;
	MegaManState::StateName getState() override;
	void OnCollision(Entity::CollisionReturn data, Entity::SideCollisions side) override;
};
