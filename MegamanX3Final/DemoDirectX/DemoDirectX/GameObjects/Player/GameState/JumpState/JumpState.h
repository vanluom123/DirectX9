#ifndef __JUMP_STATE_H__
#define __JUMP_STATE_H__
#include "../GameState.h"

class JumpState : public GameState
{
public:
	explicit JumpState(PlayerData* data);
	~JumpState() = default;

	void update(float dt) override;
	void handlerKeyBoard(std::map<int, bool> keys, float dt) override;
	void onCollision(Entity::SideCollisions side) override;
	GamePlayer::StateName GetState() override;

protected:

	float translateY;
	bool Pressed;
	float timePress;


};
#endif