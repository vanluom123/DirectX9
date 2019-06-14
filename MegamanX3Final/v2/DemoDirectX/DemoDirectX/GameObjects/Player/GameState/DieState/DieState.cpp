#include "DieState.h"


DieState::DieState(PlayerData* playerData) : PlayerState(playerData)
{
	_playerData->player->setVx(0.0f);
	_playerData->player->setVy(0.0f);
	_timeDie = 0.0f;
}

void DieState::Update(float dt)
{
	_timeDie += dt;

	Sound::getInstance()->play("RockmanDie", false, _timeDie);
	Sound::getInstance()->setVolume(95);

	if (_timeDie >= 3.0f)
	{
		_playerData->player->getAnimation()->setAnimation(20, 3, 0.3f);
		_playerData->player->setDraw(false);
	}
}

Player::ePlayerState DieState::getState()
{
	return Player::DIE;
}
