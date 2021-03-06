#ifndef __CLING_STATE_H__
#define __CLING_STATE_H__
#include "../PlayerState.h"

class ClingState : public PlayerState
{

public:
	ClingState(Player* player, bool dash = false);
	~ClingState();
	void update(float dt) override;
	void KeyBoardEventHandler(std::map<int, bool> keys, float dt) override;
	void onCollision(Side_Collision side) override;
	Player_State getState() override;

private:
	float _accelerateY;
	float _speed, _countPress;
	bool _pressed;

};
#endif