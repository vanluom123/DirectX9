#pragma once
class PlayerState;
class Player;

class PlayerData
{
public:
    PlayerData();
    ~PlayerData();

    Player      *pPlayer;
    PlayerState *pState;
};

