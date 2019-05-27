#ifndef __RUN_STATE_H__
#define __RUN_STATE_H__
#include "../PlayerState.h"

class RunState : public PlayerState
{
public:
	RunState(PlayerData* playerData);

	void KeyBoardEventHandler(std::map<int, bool> keys, float dt) override;

	void OnCollision(BaseObject::eSideCollision side) override;

	Player::ePlayerState GetState() override;

private:
	bool m_isBoot;

};
#endif
