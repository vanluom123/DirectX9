#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <map>
#include "../../Entity/BaseObject.h"
#include "../Player.h"

class PlayerState
{
public:
	PlayerState(PlayerData* playerData)
	{
		_playerData = playerData;
	}

	virtual void Update(float dt) { }

	virtual void KeyBoardEventHandler(std::map<int, bool> keys, float dt) { }

	// The side will collide with player
	virtual void onCollision(BaseObject::eSideCollision side) { }

	virtual Player::ePlayerState getState() = 0;

protected:
	PlayerData* _playerData;

};
#endif // !GAME_STATE_H

