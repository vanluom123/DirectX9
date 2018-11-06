#pragma once
#include <map>
#include "GameObjects/Entity/Entity.h"
#include "GameDefines/GameDefine.h"


class GamePlayer;

class GameState
{
protected:
	GamePlayer *gp;

public:
	explicit GameState(GamePlayer *gp);
	GameState() = default;

	MegaManState::StateName _StateName;

	virtual ~GameState() = default;

	virtual void Update(float dt);

	virtual void HandleKeyboard(std::map<int, bool> keys);

	// The side will collide with player
	virtual void OnCollision(Entity::CollisionReturn data, Entity::SideCollisions side);

	virtual MegaManState::StateName getState() = 0;
};
