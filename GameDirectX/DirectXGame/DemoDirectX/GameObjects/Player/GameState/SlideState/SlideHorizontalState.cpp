#include "SlideHorizontalState.h"

SlideHorizontalState::SlideHorizontalState(GamePlayer* gp) : GameState(gp)
{
	state = MegaManState::SlideHorizontal;
}

void SlideHorizontalState::Update(float dt) {}
void SlideHorizontalState::HandleKeyboard(std::map<int, bool> keys) {}
void SlideHorizontalState::OnCollision(Entity::CollisionReturn data, Entity::SideCollisions side) {}

MegaManState::StateName SlideHorizontalState::getState()
{
	return state;
}
