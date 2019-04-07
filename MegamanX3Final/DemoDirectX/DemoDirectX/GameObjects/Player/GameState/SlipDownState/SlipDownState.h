﻿#ifndef __SLIDE_VERTICAL_STATE_H__
#define __SLIDE_VERTICAL_STATE_H__

#include "../GameState.h"

class SlipDownState : public GameState
{
public:
	explicit SlipDownState(PlayerData* data);
	~SlipDownState() = default;

	void update(float dt) override;

	void handlerKeyBoard(std::map<int, bool> keys, float dt) override;

	void onCollision(Entity::SideCollisions side) override;

	GamePlayer::StateName GetState() override;

protected:
	bool isSlide;

};
#endif
