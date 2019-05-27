#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <map>
#include "../../Entity/BaseObject.h"
#include "../Player.h"

class PlayerState
{
public:
	PlayerState(PLAYERDATA* playerData);

	virtual void update(float dt);

	virtual void handlerKeyBoard(std::map<int, bool> keys, float dt);

	// The side will collide with player
	virtual void onCollision(BaseObject::eSideCollision side);

	virtual Player::StateName GetState() = 0;

protected:
	PLAYERDATA* _playerData;

};
#endif // !GAME_STATE_H

