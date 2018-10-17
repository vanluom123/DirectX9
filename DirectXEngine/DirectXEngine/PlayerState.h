#ifndef _PLAYER_STATE_H
#define _PLAYER_STATE_H
#include <map>
#include "PlayerData.h"
#include "Entity.h"

class Player;

class PlayerState
{
protected:
	PlayerData *mPlayerData;

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

	explicit PlayerState(PlayerData* playerData);

	PlayerState();

	virtual void OnCollision(Entity* ObjectImpact, Entity::CollisionReturn data, Entity::SideCollision side);


};
#endif
