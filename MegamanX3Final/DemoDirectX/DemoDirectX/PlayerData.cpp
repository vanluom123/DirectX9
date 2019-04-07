#include "PlayerData.h"



PlayerData::PlayerData()
{
	gameState = nullptr;
	gamePlayer = nullptr;
}


PlayerData::~PlayerData()
{}

GameState* PlayerData::GetGameState() const
{
	return gameState;
}

void PlayerData::SetGameState(GameState* val)
{
	gameState = val;
}

GamePlayer* PlayerData::GetGamePlayer() const
{
	return gamePlayer;
}

void PlayerData::SetGamePlayer(GamePlayer* val)
{
	gamePlayer = val;
}
