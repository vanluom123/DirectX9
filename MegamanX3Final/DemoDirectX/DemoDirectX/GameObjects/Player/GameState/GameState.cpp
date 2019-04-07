#include "GameState.h"

GameState::GameState(PlayerData* data)
{
	pData = data;
}

void GameState::update(float dt) { }

void GameState::handlerKeyBoard(std::map<int, bool> keys, float dt) { }

void GameState::onCollision(Entity::SideCollisions side) { }
