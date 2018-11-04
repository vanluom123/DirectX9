#pragma once
#include "PlayerData.h"
#include <map>
#include "../Entity/Entity.h"

class PlayerState
{
protected:
	explicit PlayerState(PlayerData *playerData);
	PlayerState();

	PlayerData *mPlayerData;

public:
    enum StateName
    {
		Appear,
        Standing,
		StandingShoot,
        Running,
		RunningShoot,
        Falling,
		FallingShoot,
        Jumping,
		JumpingShoot,
		Cling,
		ClingShoot,
		Climb,
		ClimbShoot,
		SlideVertical,
		SlideHorizontal,
		Win,
        Die
    };

	virtual ~PlayerState();

    virtual void Update(float dt);

    virtual void HandleKeyboard(std::map<int, bool> keys);

    //Sides will collide with player
    virtual void OnCollision(Entity::SideCollisions side, Entity::CollisionReturn data);

    virtual StateName GetState() = 0;

};

