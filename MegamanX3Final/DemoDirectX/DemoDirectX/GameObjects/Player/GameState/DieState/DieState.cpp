#include "DieState.h"

DieState::DieState(PlayerData* data) :GameState(data)
{
	pData->GetGamePlayer()->SetVx(0);
	pData->GetGamePlayer()->SetVy(0);
	timeDie = 0.0f;
}

void DieState::update(float dt)
{
	timeDie += dt;

	Sound::getInstance()->play("RockmanDie", false, timeDie);
	Sound::getInstance()->setVolume(95);

	if (timeDie >= 3.0f)
	{
		pData->GetGamePlayer()->GetAnimation()->setAnimation(20, 3, 0.3);
		pData->GetGamePlayer()->SetDraw(false);
	}
}

GamePlayer::StateName DieState::GetState()
{
	return GamePlayer::DIE;
}
