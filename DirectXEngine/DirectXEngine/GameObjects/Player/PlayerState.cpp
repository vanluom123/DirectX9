#include "PlayerState.h"


PlayerState::PlayerState(PlayerData *pData)
{
    this->pData = pData;
}

PlayerState::PlayerState()
{}

PlayerState::~PlayerState()
{}

void PlayerState::Update(float dt)
{}

void PlayerState::HandleKeyboard(std::map<int, bool> keys)
{}

void PlayerState::OnCollision(Entity::SideCollisions side, Entity::CollisionReturn data)
{}