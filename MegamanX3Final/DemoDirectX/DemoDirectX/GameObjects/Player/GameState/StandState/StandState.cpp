#include "StandState.h"
#include "../RunState/RunState.h"
#include "../../../../GameDefines/GameDefine.h"

StandState::StandState(PlayerData* data) : GameState(data)
{
	pData->GetGamePlayer()->SetVx(0);
	timeStand = 0.0f;
	isMove = false;
}

void StandState::update(float dt)
{
	timeStand += dt;
	if (timeStand > 1.50f)
	{
		pData->GetGamePlayer()->GetAnimation()->setAnimation(1, 4, 0.1, false);
		timeStand = 0.0f;
	}

	if (isMove)
		pData->GetGamePlayer()->SetState(new RunState(pData));
}

void StandState::handlerKeyBoard(std::map<int, bool> keys, float dt)
{
	pData->GetGamePlayer()->SetVx(0);
	pData->GetGamePlayer()->SetVy(Define::PLAYER_MAX_JUMP_VELOCITY);
	isMove = false;

	if (keys[VK_RIGHT])
	{
		isMove = true;
		pData->GetGamePlayer()->SetVx(Define::PLAYER_MAX_RUNNING_SPEED);
	}
	else if (keys[VK_LEFT])
	{
		isMove = true;
		pData->GetGamePlayer()->SetVx(-Define::PLAYER_MAX_RUNNING_SPEED);
	}
}

void StandState::onCollision(Entity::SideCollisions side)
{
	switch (side)
	{
	case Entity::LEFT:
	case Entity::RIGHT:
	{
		isMove = false;
	}
	default: break;
	}
}

GamePlayer::StateName StandState::GetState()
{
	return GamePlayer::STAND;
}
