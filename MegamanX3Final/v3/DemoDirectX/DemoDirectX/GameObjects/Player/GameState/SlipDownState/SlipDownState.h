#ifndef __SLIDE_VERTICAL_STATE_H__
#define __SLIDE_VERTICAL_STATE_H__

#include "../PlayerState.h"

class SlipDownState : public PlayerState
{
public:
	SlipDownState(PlayerData* playerData);

	void Update(float dt) override;

	void KeyBoardEventHandler(std::map<int, bool> keys, float dt) override;

	void OnCollision(BaseObject::eSideCollision side) override;

	Player::ePlayerState GetState() override;

private:
	bool m_isSlide;

};
#endif
