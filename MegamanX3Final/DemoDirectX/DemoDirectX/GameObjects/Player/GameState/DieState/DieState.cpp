#include "DieState.h"


DieState::DieState(PLAYERDATA* playerData) : PlayerState(playerData)
{
	_playerData->player->SetVx(0);
	_playerData->player->SetVy(0);
	_timeDie = 0.0f;
}

void DieState::update(float dt)
{
	_timeDie += dt;

	Sound::getInstance()->play("RockmanDie", false, _timeDie);
	Sound::getInstance()->setVolume(95);

	if (_timeDie >= 3.0f)
	{
		_playerData->player->GetAnimation()->SetAnimation(20, 3, 0.3);
		_playerData->player->SetDraw(false);
	}
}

Player::StateName DieState::GetState()
{
	return Player::DIE;
}
