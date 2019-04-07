#include "FallState.h"
#include "../RunState/RunState.h"
#include "../StandState/StandState.h"
#include "../SlipDownState/SlipDownState.h"
#include "../../../../GameDefines/GameDefine.h"

FallState::FallState(PlayerData* data, bool dash) : GameState(data)
{
	pData->GetGamePlayer()->SetVy(0);
	translateY = 25.0f;
	Pressed = dash;
}

void FallState::handlerKeyBoard(std::map<int, bool> keys, float dt)
{
	float speed = 0.0f;
	if (keys[VK_RIGHT])
	{
		pData->GetGamePlayer()->SetReverse(false);

		if (Pressed)
			speed = Define::PLAYER_MAX_SLIDE_SPEED;
		else
			speed = Define::PLAYER_MAX_RUNNING_SPEED;
	}
	else if (keys[VK_LEFT])
	{
		pData->GetGamePlayer()->SetReverse(true);
		if (Pressed)
			speed = -Define::PLAYER_MAX_SLIDE_SPEED;
		else
			speed = -Define::PLAYER_MAX_RUNNING_SPEED;
	}
	pData->GetGamePlayer()->SetVx(speed);

	pData->GetGamePlayer()->AddVy(translateY);

	if (pData->GetGamePlayer()->GetVy() > Define::PLAYER_MAX_JUMP_VELOCITY)
		pData->GetGamePlayer()->SetVy(Define::PLAYER_MAX_JUMP_VELOCITY);
}

void FallState::onCollision(Entity::SideCollisions side)
{
	switch (side)
	{
	case Entity::LEFT:
	case Entity::RIGHT:
	{
		pData->GetGamePlayer()->SetState(new SlipDownState(pData));
		break;
	}
	case Entity::BOTTOM:
	{
		Sound::getInstance()->play("FallDownGround", false, 1);
		Sound::getInstance()->setVolume(95);
		pData->GetGamePlayer()->SetState(new StandState(pData));
		break;
	}
	default: break;
	}
}

GamePlayer::StateName FallState::GetState()
{
	return GamePlayer::FALL;
}
