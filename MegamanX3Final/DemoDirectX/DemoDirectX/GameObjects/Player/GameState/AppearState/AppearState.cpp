#include "AppearState.h"
#include "../StandState/StandState.h"
#include "../../../../GameDefines/GameDefine.h"

AppearState::AppearState(PlayerData* data) : GameState(data)
{
	translateY = 25.0f;
}

void AppearState::update(float dt)
{
	if (pData->GetGamePlayer()->GetAnimation()->getCurrentColumn() == 0)
		pData->GetGamePlayer()->GetAnimation()->setPause(true);

	else if (pData->GetGamePlayer()->GetAnimation()->getCurrentColumn() >= 4)
		pData->GetGamePlayer()->SetState(new StandState(pData));
}

void AppearState::handlerKeyBoard(std::map<int, bool> keys, float dt)
{
	pData->GetGamePlayer()->SetVx(0);
	pData->GetGamePlayer()->AddVy(translateY);

	if (pData->GetGamePlayer()->GetVy() > Define::PLAYER_MAX_JUMP_VELOCITY)
		pData->GetGamePlayer()->SetVy(Define::PLAYER_MAX_JUMP_VELOCITY);
}

void AppearState::onCollision(Entity::SideCollisions side)
{
	switch (side)
	{
	case Entity::BOTTOM:
		{
			pData->GetGamePlayer()->GetAnimation()->setPause(false);
			break;
		}
	default: break;
	}
}

GamePlayer::StateName AppearState::GetState()
{
	return GamePlayer::APPEAR;
}
