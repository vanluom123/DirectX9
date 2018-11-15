﻿#pragma once
#include "../../GameState.h"

class SlideHorizontalState : public GameState
{
	float translateX;
	float countPress;

public:
	SlideHorizontalState() = default;
	explicit SlideHorizontalState(GamePlayer *gp);
	~SlideHorizontalState() override = default;

	void Update(float dt) override;

	void HandleKeyboard(std::map<int, bool> keys, float dt) override;

	void OnCollision(Entity::SideCollisions side) override;

	MegaManState::StateName getState() override;
};
