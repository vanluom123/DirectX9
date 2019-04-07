#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <map>
#include "../../Entity/Entity.h"
#include "../GamePlayer.h"

class GameState
{
public:
	virtual ~GameState() = default;
	explicit GameState(PlayerData* data);

	virtual void update(float dt);

	virtual void handlerKeyBoard(std::map<int, bool> keys, float dt);

	// The side will collide with player
	virtual void onCollision(Entity::SideCollisions side);

	virtual GamePlayer::StateName GetState() = 0;

protected:
	PlayerData* pData;

};
#endif // !GAME_STATE_H

