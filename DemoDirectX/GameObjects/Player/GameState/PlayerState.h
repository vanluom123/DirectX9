#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "../Player.h"

class PlayerState
{
protected:
	Player* m_pPlayer;

public:
	PlayerState(Player* player);
	virtual ~PlayerState();

	virtual void update(float dt);
	virtual void KeyBoardEventHandler(map<int, bool> keys, float dt);
	virtual void onCollision(Side_Collision side);
	virtual Player_State getState();
};
#endif // !GAME_STATE_H

