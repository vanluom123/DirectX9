#ifndef _PLAYER_DATA_H
#define _PLAYER_DATA_H

class PlayerState;
class Player;


class PlayerData
{
public:
	PlayerData();
	~PlayerData();

	Player* player;
	PlayerState* state;
};
#endif