#ifndef _TAG_PLAYER_DATA_H
#define _TAG_PLAYER_DATA_H

class Player;
class PlayerState;

struct PlayerData
{
	Player* player;
	PlayerState* state;
};

#endif