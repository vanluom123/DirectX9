#include "JumpState.h"
#include "../FallState/FallState.h"
#include "../../GamePlayer.h"

JumpState::JumpState(GamePlayer* gp) : GameState(gp)
{
	state = Jumping;
	this->gp->setVy(Define::PLAYER_MIN_JUMP_VELOCITY);
	acceleratorY = 15.0f;
	acceleratorX = 14.0f;

	noPressed = false;
}

void JumpState::Update(float dt)
{
	gp->addVy(acceleratorY);

	if (gp->getVy() >= 0)
	{
		gp->setState(new FallState(gp));
		return;
	}

	if (noPressed)
	{
		if (gp->getMoveDirection() == GamePlayer::MoveToLeft)
		{
			//Player is moving to left   
			if (gp->getVx() < 0)
			{
				gp->addVx(acceleratorX);

				if (gp->getVx() > 0)
					gp->setVx(0);
			}
		}
		else if (gp->getMoveDirection() == GamePlayer::MoveToRight)
		{
			//Player is moving to right   
			if (gp->getVx() > 0)
			{
				gp->addVx(-acceleratorX);

				if (gp->getVx() < 0)
					gp->setVx(0);
			}
		}
	}
}

void JumpState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_RIGHT])
	{
		if (keys[VK_Z])
			state = JumpingShoot;
		else
		{
			state = Jumping;
			gp->SetReverse(false);

			//Move to right
			if (gp->getVx() < Define::PLAYER_MAX_RUNNING_SPEED)
			{
				gp->addVx(acceleratorX);

				if (gp->getVx() >= Define::PLAYER_MAX_RUNNING_SPEED)
					gp->setVx(Define::PLAYER_MAX_RUNNING_SPEED);
			}
		}

		noPressed = false;
	}
	else if (keys[VK_LEFT])
	{
		if (keys[VK_Z])
			state = JumpingShoot;
		else
		{
			state = Jumping;
			gp->SetReverse(true);

			//Move to left
			if (gp->getVx() > -Define::PLAYER_MAX_RUNNING_SPEED)
			{
				gp->addVx(-acceleratorX);

				if (gp->getVx() < -Define::PLAYER_MAX_RUNNING_SPEED)
					gp->setVx(-Define::PLAYER_MAX_RUNNING_SPEED);
			}
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
			gp->addPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
			gp->setVx(0);
			break;
		}

		case Entity::Right:
		{
			gp->addPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
			gp->setVx(0);
			break;
		}

		case Entity::TopRight: case Entity::TopLeft: case Entity::Top:
		{
			gp->addPosition(0, data.RegionCollision.bottom - data.RegionCollision.top);
			gp->setVy(0);
			break;
		}

		case Entity::BottomRight: case Entity::BottomLeft: case Entity::Bottom:
		{
			gp->addPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
		}

		default: break;
	}
}

StateName JumpState::getState()
{
	return state;
}
