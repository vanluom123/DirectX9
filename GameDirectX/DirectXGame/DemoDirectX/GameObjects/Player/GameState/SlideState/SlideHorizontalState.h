#pragma once
#include "../GameState.h"

class SlideHorizontalState : public GameState
{
public:
	explicit SlideHorizontalState(GamePlayer *gp);
	SlideHorizontalState() = default;
	~SlideHorizontalState() override = default;
	void Update(float dt) override;
	void HandleKeyboard(std::map<int, bool> keys) override;
	void OnCollision(Entity::CollisionReturn data, Entity::SideCollisions side) override;
	MegaManState::StateName getState() override;
};