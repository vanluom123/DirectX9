#ifndef __DASH_STATE_H__
#define __DASH_STATE_H__
#include "../PlayerState.h"

class DashState : public PlayerState
{
public:
	DashState(PlayerData* playerData);

	void KeyBoardEventHandler(std::map<int, bool> keys, float dt) override;

	void OnCollision(BaseObject::eSideCollision side) override;

	Player::ePlayerState GetState() override;

private:
	float m_accelerateX;
	float m_timePress;

};
#endif