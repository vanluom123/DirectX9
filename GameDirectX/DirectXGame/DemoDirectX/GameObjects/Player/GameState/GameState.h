#pragma once
#include <map>
#include "../../../GameDefines/GameDefine.h"
#include "../../Entity/Entity.h"


class GamePlayer;

class GameState
{
protected:
	GamePlayer *gp;
	MegaManState::StateName state;

public:
	explicit GameState(GamePlayer *gp);
	GameState() = default;

	virtual ~GameState() = default;

	virtual void Update(float dt);

	virtual void HandleKeyboard(std::map<int, bool> keys);

	// The side will collide with player
	virtual void OnCollision(Entity::CollisionReturn data, Entity::SideCollisions side);

	virtual MegaManState::StateName getState() = 0;
};
