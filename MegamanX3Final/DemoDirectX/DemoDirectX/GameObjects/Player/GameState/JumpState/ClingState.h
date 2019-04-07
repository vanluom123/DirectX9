#ifndef __CLING_STATE_H__
#define __CLING_STATE_H__
#include "../GameState.h"

class ClingState : public GameState
{

public:
	explicit ClingState(PlayerData* data, bool dash = false);
	~ClingState() = default;


	void update(float dt) override;
	void handlerKeyBoard(std::map<int, bool> keys, float dt) override;
	void onCollision(Entity::SideCollisions side) override;
	GamePlayer::StateName GetState() override;

protected:

	float translateY;
	float speed, countPress;
	bool Pressed;

};
#endif