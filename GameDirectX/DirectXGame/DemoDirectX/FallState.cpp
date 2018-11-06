#include "FallState.h"
#include "GamePlayer.h"
#include "RunState.h"

FallState::FallState(GamePlayer* gp) : GameState(gp)
{
	acceleratorY = 15.0f;
	acceleratorX = 8.0f;

	if (this->gp->GetVx() == 0)
		allowMoveX = false;
	else
		allowMoveX = true;
}

void FallState::Update(float dt)
{
	gp->AddVy(acceleratorY);

	if (gp->GetVy() > Define::PLAYER_MAX_JUMP_VELOCITY)
		gp->SetVy(Define::PLAYER_MAX_JUMP_VELOCITY);
}

void FallState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_RIGHT])
	{
		gp->SetReverse(false);

		isLeftOrRightKeyPressed = true;
		//Move to left
		if (gp->GetVx() < Define::PLAYER_MAX_RUNNING_SPEED)
		{
			gp->AddVx(acceleratorX);

			if (gp->GetVx() >= Define::PLAYER_MAX_RUNNING_SPEED)
				gp->SetVx(Define::PLAYER_MAX_RUNNING_SPEED);
		}
	}
	else if (keys[VK_LEFT])
	{
		gp->SetReverse(true);

		isLeftOrRightKeyPressed = true;
		//Move to  right
		if (gp->GetVx() > -Define::PLAYER_MAX_RUNNING_SPEED)
		{
			gp->AddVx(-acceleratorX);

			if (gp->GetVx() <= -Define::PLAYER_MAX_RUNNING_SPEED)
				gp->SetVx(-Define::PLAYER_MAX_RUNNING_SPEED);
		}
	}
	else
		isLeftOrRightKeyPressed = false;
}

void FallState::OnCollision(Entity::CollisionReturn data, Entity::SideCollisions side)
{
	switch (side)
	{
	case Entity::Left:
	{
		if (gp->getMoveDirection() == GamePlayer::MoveToLeft)
		{
			gp->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
			gp->SetVx(0);
		}
		break;
	}
	case Entity::Right:
	{
		if (gp->getMoveDirection() == GamePlayer::MoveToRight)
		{
			gp->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
			gp->SetVx(0);
		}
		break;
	}

	case Entity::Bottom:
	case Entity::BottomRight:
	case Entity::BottomLeft:
	{
		if (data.RegionCollision.right - data.RegionCollision.left >= 8.0f)
		{
			gp->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));

			if (isLeftOrRightKeyPressed)
				gp->setState(new RunState(gp));
			else
				gp->setState(new StandState(gp));
		}
		break;
	}

	case Entity::Top: break;
	case Entity::TopLeft: break;
	case Entity::TopRight: break;
	case Entity::Unknown: break;
	default: break;
	}

}

MegaManState::StateName FallState::getState()
{
	return MegaManState::Falling;
}
