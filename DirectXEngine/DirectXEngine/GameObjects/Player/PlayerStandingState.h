#pragma once
#include "PlayerState.h"

class PlayerStandingState : public PlayerState
{
public:
	explicit PlayerStandingState(PlayerData * pData);
    ~PlayerStandingState();

    void HandleKeyboard(std::map<int, bool> keys) override;

	StateName GetState() override;
};

