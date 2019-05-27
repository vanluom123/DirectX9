#ifndef __SLIDE_VERTICAL_STATE_H__
#define __SLIDE_VERTICAL_STATE_H__

#include "../PlayerState.h"

class SlipDownState : public PlayerState
{
public:
	SlipDownState(PLAYERDATA* playerData);

	void update(float dt) override;

	void handlerKeyBoard(std::map<int, bool> keys, float dt) override;

	void onCollision(BaseObject::eSideCollision side) override;

	Player::StateName GetState() override;

private:
	bool _isSlide;

};
#endif
