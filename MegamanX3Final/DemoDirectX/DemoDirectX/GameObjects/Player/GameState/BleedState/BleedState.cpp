#include "BleedState.hpp"
#include "../StandState/StandState.h"

BleedState::BleedState(PlayerData* data, int Direction) :GameState(data)
{
	pData->GetGamePlayer()->SetVx(30.0f * Direction);
	pData->GetGamePlayer()->SetVy(5.0f);
	timeBleed = 0.0f;
}

void BleedState::update(float dt)
{
	pData->GetGamePlayer()->SetVx(0);
	pData->GetGamePlayer()->GetAnimation()->setPause(false);
	if (pData->GetGamePlayer()->GetAnimation()->getCurrentColumn() >= 8)
		pData->GetGamePlayer()->SetState(new StandState(pData));
}

GamePlayer::StateName BleedState::GetState()
{
	return GamePlayer::BLEED;
}
