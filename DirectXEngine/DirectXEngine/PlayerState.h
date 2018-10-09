#ifndef _PLAYER_STATE_H
#define _PLAYER_STATE_H
#include <map>
#include "PlayerData.h"

class Player;

class PlayerState
{
public:
	enum StateName
	{
		Standing,
		Running,
		Falling,
		Jumping,
		Die
	};

	virtual void Update(float dt);
	virtual void HandlerKeyBoard(std::map<int, bool> keys);
	virtual StateName GetState() = 0;

	virtual ~PlayerState();
	PlayerState(PlayerData* playerData);
	PlayerState();
protected:
	PlayerData *mPlayerData;
};
#endif