#ifndef __APPEAR_STATE_H__
#define __APPEAR_STATE_H__
#include "../GameState.h"

class AppearState : public GameState
{
public:
	explicit AppearState(PlayerData* data);
	~AppearState() = default;

	void update(float dt) override;

	void handlerKeyBoard(std::map<int, bool> keys, float dt) override;

	void onCollision(Entity::SideCollisions side) override;

	GamePlayer::StateName GetState() override;

protected:
	float translateY;
};

#endif
