#ifndef _PLAYER_STANDING_STATE_H
#define _PLAYER_STANDING_STATE_H
#include "PlayerState.h"
#include "Player.h"

class PlayerStandingState :public PlayerState
{
public:
	explicit PlayerStandingState(PlayerData* playerData);

	void Update(float dt) override;

	void HandlerKeyBoard(std::map<int, bool> keys) override;

	StateName GetState() override;

	~PlayerStandingState();
};
#endif

