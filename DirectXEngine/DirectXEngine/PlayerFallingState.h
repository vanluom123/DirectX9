#ifndef _PLAYER_FALLING_STATE_H
#define _PLAYER_FALLING_STATE_H
#include "PlayerState.h"

class PlayerFallingState :public PlayerState
{
public:
	PlayerFallingState(PlayerData* playerData);

	~PlayerFallingState();

	void Update(float dt) override;

	void HandlerKeyBoard(std::map<int, bool> keys) override;

	StateName GetState() override;

private:
	float acceleratorX, acceleratorY;
	bool allowMoveX;
	bool isLeftOrRightKeyPressed;
};

#endif