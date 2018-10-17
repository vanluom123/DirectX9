#ifndef _PLAYER_FALLING_STATE_H
#define _PLAYER_FALLING_STATE_H
#include "PlayerState.h"

class PlayerFallingState :public PlayerState
{
public:
	explicit PlayerFallingState(PlayerData* playerData);

	~PlayerFallingState();

	void Update(float dt) override;

	void HandlerKeyBoard(std::map<int, bool> keys) override;

	void OnCollision(Entity* impact, Entity::CollisionReturn data, Entity::SideCollision side) override;

	StateName GetState() override;

protected:
	float acceleratorX, acceleratorY;
	bool allowMoveX;
	bool isLeftOrRightKeyPressed;
};

#endif