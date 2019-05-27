#ifndef _TAG_PLAYER_DATA_H
#define _TAG_PLAYER_DATA_H

class Player;
class PlayerState;

typedef struct tagPlayerData
{
	Player* player;
	PlayerState* state;
}PLAYERDATA;

#endif