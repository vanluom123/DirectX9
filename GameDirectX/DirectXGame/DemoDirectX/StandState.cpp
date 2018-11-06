#include "StandState.h"
#include "GamePlayer.h"
#include "RunState.h"

StandState::StandState(GamePlayer* gp) : GameState(gp)
{
	this->gp->SetVx(0);
	this->gp->SetVy(0);
}

void StandState::Update(float dt)
{
}

void StandState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_LEFT] || keys[VK_RIGHT])
		gp->setState(new RunState(gp));
}

MegaManState::StateName StandState::getState()
{
	return MegaManState::Standing;
}

void StandState::OnCollision(Entity::CollisionReturn data, Entity::SideCollisions side)
{
}
