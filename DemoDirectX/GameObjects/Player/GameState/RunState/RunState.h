#ifndef __RUN_STATE_H__
#define __RUN_STATE_H__
#include "../PlayerState.h"

class RunState : public PlayerState
{
private:
	bool _isBoot;

public:
	RunState(Player* player);
	~RunState();
	void KeyBoardEventHandler(map<int, bool> keys, float dt) override;
	void onCollision(Side_Collision side) override;
	Player_State getState() override;


};
#endif
