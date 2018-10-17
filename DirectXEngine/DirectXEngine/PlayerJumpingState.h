#ifndef _PLAYER_JUMPING_STATE_H
#define _PLAYER_JUMPING_STATE_H
#include "PlayerState.h"
#include "Player.h"

class PlayerJumpingState :public PlayerState
{
public:

	void Update(float dt) override;

	void HandlerKeyBoard(std::map<int, bool> keys) override;

	void OnCollision(Entity* impact, Entity::CollisionReturn data, Entity::SideCollision side) override;

	StateName GetState() override;

	explicit PlayerJumpingState(PlayerData* playerData);

	~PlayerJumpingState();


private:
	bool isPressed;
	float acceleratorX, acceleratorY;
};

#endif