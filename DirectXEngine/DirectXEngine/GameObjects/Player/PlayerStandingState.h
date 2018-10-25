#pragma once
#include "PlayerState.h"

class PlayerStandingState : public PlayerState
{
public:
    PlayerStandingState(PlayerData *playerData);
    ~PlayerStandingState();

    void HandleKeyboard(std::map<int, bool> keys) override;

	StateName GetState() override;
};

