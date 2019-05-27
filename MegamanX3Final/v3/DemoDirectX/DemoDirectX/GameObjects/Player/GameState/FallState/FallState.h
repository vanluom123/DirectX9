#ifndef __FALL_STATE_H__
#define __FALL_STATE_H__
#include "../PlayerState.h"

class FallState : public PlayerState
{
public:
	FallState(PlayerData* playerData, bool dash = false);

	void KeyBoardEventHandler(std::map<int, bool> keys, float dt) override;

	void OnCollision(BaseObject::eSideCollision side) override;

	Player::ePlayerState GetState() override;

private:
	float m_accelerateY;
	float m_accelerateX;
	bool m_isPressed;
	//First Velocity equal zero in case speed won't decrease 
	bool m_allowMoveX;

	bool m_isLeftOrRightKeyPressed;

};
#endif
