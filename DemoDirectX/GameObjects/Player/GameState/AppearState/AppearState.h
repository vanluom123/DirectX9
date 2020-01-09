#ifndef __APPEAR_STATE_H__
#define __APPEAR_STATE_H__
#include "../PlayerState.h"

class AppearState : public PlayerState
{
private:
	float _accelerateY;

public:
	AppearState(Player* player);
	~AppearState();
	void update(float dt) override;
	void KeyBoardEventHandler(std::map<int, bool> keys, float dt) override;
	void onCollision(Side_Collision side) override;
	Player_State getState() override;

};

#endif
