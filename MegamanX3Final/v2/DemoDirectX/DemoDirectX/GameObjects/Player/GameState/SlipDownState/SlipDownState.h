#ifndef __SLIDE_VERTICAL_STATE_H__
#define __SLIDE_VERTICAL_STATE_H__

#include "../PlayerState.h"

class SlipDownState : public PlayerState
{
public:
	SlipDownState(Player* player);
	~SlipDownState();

	void update(float dt) override;
	void KeyBoardEventHandler(map<int, bool> keys, float dt) override;
	void onCollision(Side_Collision side) override;
	Player_State getState() override;

private:
	bool _isSlide;

};
#endif
