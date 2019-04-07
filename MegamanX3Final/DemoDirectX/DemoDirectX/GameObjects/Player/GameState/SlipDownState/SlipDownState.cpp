#include "SlipDownState.h"
#include "../StandState/StandState.h"
#include "../FallState/FallState.h"
#include "../../../../GameDefines/GameDefine.h"

SlipDownState::SlipDownState(PlayerData* data) : GameState(data)
{
	pData->GetGamePlayer()->SetVy(Define::PLAYER_MAX_JUMP_VELOCITY / 4);
	isSlide = true;
}

void SlipDownState::update(float dt)
{
	if (!isSlide)
		pData->GetGamePlayer()->SetState(new FallState(pData));

	isSlide = false;
}

void SlipDownState::handlerKeyBoard(std::map<int, bool> keys, float dt)
{
	pData->GetGamePlayer()->SetVy(Define::PLAYER_MAX_JUMP_VELOCITY / 4);
	if (keys[VK_RIGHT])
	{
		pData->GetGamePlayer()->SetReverse(false);
		pData->GetGamePlayer()->SetVx(Define::PLAYER_MAX_RUNNING_SPEED);
	}
	else if (keys[VK_LEFT])
	{
		pData->GetGamePlayer()->SetReverse(true);
		pData->GetGamePlayer()->SetVx(-Define::PLAYER_MAX_RUNNING_SPEED);
	}
	else
	{
		pData->GetGamePlayer()->SetVx(0);
		pData->GetGamePlayer()->SetState(new FallState(pData));
	}
}

void SlipDownState::onCollision(Entity::SideCollisions side)
{
	switch (side)
	{
	case Entity::LEFT:
	case Entity::RIGHT:
	{
		isSlide = true;
		break;
	}
	case Entity::BOTTOM:
	{
		pData->GetGamePlayer()->SetState(new StandState(pData));
		break;
	}
	default: break;
	}
}

GamePlayer::StateName SlipDownState::GetState()
{
	return GamePlayer::SLIP_DOWN;
}
