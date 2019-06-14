#ifndef __APPEAR_STATE_H__
#define __APPEAR_STATE_H__
#include "../PlayerState.h"

class AppearState : public PlayerState
{
public:
	AppearState(PlayerData* playerData);

	void Update(float dt) override;

	void KeyBoardEventHandler(std::map<int, bool> keys, float dt) override;

	void onCollision(BaseObject::eSideCollision side) override;

	Player::ePlayerState getState() override;

private:
	float _accelerateY;
};

#endif
