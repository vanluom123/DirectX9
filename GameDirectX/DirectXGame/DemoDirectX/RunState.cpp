#include "RunState.h"
#include "GamePlayer.h"

RunState::RunState(GamePlayer* gp) : GameState(gp)
{
	accelerationX = 25.0f;
	this->gp->setAllowLeft(true);
	this->gp->setAllowRight(true);
}

void RunState::Update(float dt)
{
}

void RunState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_RIGHT])
	{
		if (gp->getAllowRight())
		{
			gp->SetReverse(false);

			//Move to right
			if (gp->GetVx() < Define::PLAYER_MAX_RUNNING_SPEED)
			{
				gp->AddVx(accelerationX);

				if (gp->GetVx() >= Define::PLAYER_MAX_RUNNING_SPEED)
					gp->SetVx(Define::PLAYER_MAX_RUNNING_SPEED);
			}
		}
	}
	else if (keys[VK_LEFT])
	{
		if (gp->getAllowLeft())
		{
			gp->SetReverse(true);

			//Move to left
			if (gp->GetVx() > -Define::PLAYER_MAX_RUNNING_SPEED)
			{
				gp->AddVx(-accelerationX);

				if (gp->GetVx() < -Define::PLAYER_MAX_RUNNING_SPEED)
					gp->SetVx(-Define::PLAYER_MAX_RUNNING_SPEED);
			}
		}
	}
	else
		gp->setState(new StandState(gp));
}

MegaManState::StateName RunState::getState()
{
	return MegaManState::Running;
}

void RunState::OnCollision(Entity::CollisionReturn data, Entity::SideCollisions side)
{
	switch (side)
	{
	case Entity::Left:
	{
		//Collision left of player side
		if (gp->getMoveDirection() == GamePlayer::MoveToLeft)
		{
			gp->setAllowLeft(false);
			//Player is pushed right that player not through object
			gp->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);

			gp->setState(new StandState(gp));
		}

		return;
	}

	case Entity::Right:
	{
		//Collision right of player side
		if (gp->getMoveDirection() == GamePlayer::MoveToRight)
		{
			gp->setAllowRight(false);
			gp->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
			gp->setState(new StandState(gp));
		}
		break;
	}

	case Entity::Bottom: case Entity::BottomLeft: case Entity::BottomRight:
	{
		gp->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));

		gp->SetVy(0);

		break;
	}

	default: break;
	}

}
