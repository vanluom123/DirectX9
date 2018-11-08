#include "StandState.h"
#include "../RunState/RunState.h"
#include "../../GamePlayer.h"
#include "../JumpState/JumpState.h"

StandState::StandState(GamePlayer* gp) : GameState(gp)
{
	state = Standing;
	this->gp->setVx(0);
	this->gp->setVy(0);
}

void StandState::Update(float dt) {}

void StandState::HandleKeyboard(std::map<int, bool> keys)
{
	gp->isJumping = true;
	gp->isShooting = false;

	if (keys[VK_LEFT] || keys[VK_RIGHT])
		gp->setState(new RunState(gp));
	else if (keys[VK_X])
		gp->setState(new JumpState(gp));
	else if (keys[VK_Z])
		state = StandingShoot;
	else state = Standing;
}

StateName StandState::getState()
{
	return state;
}

void StandState::OnCollision(Entity::CollisionReturn data, Entity::SideCollisions side) {}
