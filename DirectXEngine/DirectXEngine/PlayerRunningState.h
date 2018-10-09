#ifndef _PLAYER_RUNNING_STATE_H
#define _PLAYER_RUNNING_STATE_H
#include "PlayerState.h"
#include "Player.h"

class PlayerRunningState : public PlayerState
{
public:
	PlayerRunningState(PlayerData* playerData);

	void Update(float dt) override;

	void HandlerKeyBoard(std::map<int, bool> keys) override;

	StateName GetState() override;

	~PlayerRunningState();
private:
	float acceleratorX;
};

#endif