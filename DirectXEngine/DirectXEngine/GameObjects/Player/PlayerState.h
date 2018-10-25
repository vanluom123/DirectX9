#pragma once
#include "PlayerData.h"
#include "../Entity.h"
#include "../../GameComponents/GameCollision.h"
#include <map>

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

	virtual ~PlayerState();

    virtual void Update(float dt);

    virtual void HandleKeyboard(std::map<int, bool> keys);

    //side va cham voi pPlayer
    virtual void OnCollision(Entity::SideCollisions side, Entity::CollisionReturn data);

    virtual StateName GetState() = 0;

protected:
	explicit PlayerState(PlayerData *playerData);
    PlayerState();

    PlayerData *pData;
};

