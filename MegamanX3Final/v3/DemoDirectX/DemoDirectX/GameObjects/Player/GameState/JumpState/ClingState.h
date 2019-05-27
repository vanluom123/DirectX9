#ifndef __CLING_STATE_H__
#define __CLING_STATE_H__
#include "../PlayerState.h"

class ClingState : public PlayerState
{

public:
	ClingState(PlayerData* playerData, bool dash = false);

	void Update(float dt) override;
	void KeyBoardEventHandler(std::map<int, bool> keys, float dt) override;
	void OnCollision(BaseObject::eSideCollision side) override;
	Player::ePlayerState GetState() override;

private:
	float m_accelerateY;
	float m_speed, m_countPress;
	bool m_isPressed;

};
#endif