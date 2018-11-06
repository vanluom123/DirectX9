#include "JumpState.h"
#include "GamePlayer.h"
#include "FallState.h"

JumpState::JumpState(GamePlayer* gp) : GameState(gp)
{
	this->gp->SetVy(Define::PLAYER_MIN_JUMP_VELOCITY);
	acceleratorY = 15.0f;
	acceleratorX = 14.0f;

	noPressed = false;
}

void JumpState::Update(float dt)
{
	gp->AddVy(acceleratorY);

	if (gp->GetVy() >= 0)
	{
		gp->setState(new FallState(gp));
		return;
	}

	if (noPressed)
	{
		if (gp->getMoveDirection() == GamePlayer::MoveToLeft)
		{
			//Player is moving to left   
			if (gp->GetVx() < 0)
			{
				gp->AddVx(acceleratorX);

				if (gp->GetVx() > 0)
					gp->SetVx(0);
			}
		}
		else if (gp->getMoveDirection() == GamePlayer::MoveToRight)
		{
			//Player is moving to right   
			if (gp->GetVx() > 0)
			{
				gp->AddVx(-acceleratorX);

				if (gp->GetVx() < 0)
					gp->SetVx(0);
			}
		}
	}
}

void JumpState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_RIGHT])
	{
		gp->SetReverse(false);

		//Move to right
		if (gp->GetVx() < Define::PLAYER_MAX_RUNNING_SPEED)
		{
			gp->AddVx(acceleratorX);

			if (gp->GetVx() >= Define::PLAYER_MAX_RUNNING_SPEED)
				gp->SetVx(Define::PLAYER_MAX_RUNNING_SPEED);
		}

		noPressed = false;
	}
	else if (keys[VK_LEFT])
	{
		gp->SetReverse(true);

		//Move to left
		if (gp->GetVx() > -Define::PLAYER_MAX_RUNNING_SPEED)
		{
			gp->AddVx(-acceleratorX);

			if (gp->GetVx() < -Define::PLAYER_MAX_RUNNING_SPEED)
				gp->SetVx(-Define::PLAYER_MAX_RUNNING_SPEED);
		}

		noPressed = false;
	}
	else
		noPressed = true;
}

void JumpState::OnCollision(Entity::CollisionReturn data, Entity::SideCollisions side)
{
	switch (side)
	{
	case Entity::Left:
	{
		gp->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
		gp->SetVx(0);
		break;
	}

	case Entity::Right:
	{
		gp->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
		gp->SetVx(0);
		break;
	}

	case Entity::TopRight: case Entity::TopLeft: case Entity::Top:
	{
		gp->AddPosition(0, data.RegionCollision.bottom - data.RegionCollision.top);
		gp->SetVy(0);
		break;
	}

	case Entity::BottomRight: case Entity::BottomLeft: case Entity::Bottom:
	{
		gp->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
	}

	default:
		break;
	}

}

MegaManState::StateName JumpState::getState()
{
	return MegaManState::Jumping;
}
