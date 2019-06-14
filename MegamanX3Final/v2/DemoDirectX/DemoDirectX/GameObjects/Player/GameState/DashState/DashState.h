#ifndef __DASH_STATE_H__
#define __DASH_STATE_H__
#include "../PlayerState.h"

class DashState : public PlayerState
{
public:
	DashState(PlayerData* playerData);

	void KeyBoardEventHandler(std::map<int, bool> keys, float dt) override;

	void onCollision(BaseObject::eSideCollision side) override;

	Player::ePlayerState getState() override;

private:
	float _accelerateX;
	float _timePress;

};
#endif