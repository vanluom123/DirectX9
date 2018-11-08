#include "RockManState.h"
#include "../../GameDefines/GameDefine.h"

RockManState::RockManState(Entity* rockman)
{
	pRockman = rockman;
	mStateName = Appear;
	isJump = true;
	isFall = false;
	mTimeShoot = 0.0f;
	mTimeBleed = 2.1f;
	mTimeAppear = 0;
	mStartJump = 0.0f;
}

void RockManState::Fall(bool& fall) const
{
	if (fall)
	{
		if (isJump || (pRockman->getVy() - mStartJump) >= 32)
		{
			if (pRockman->getVy() > -1 && pRockman->getVy() <= 0.0f)
				pRockman->setVy(pRockman->getVy() - 0.05);
			else if (pRockman->getVy() <= -1 || (pRockman->getPosition().y - mStartJump) <= 2 * 32)
				pRockman->setVy(-1);
			else
				pRockman->setVy(-0.05 * 2);
		}
	}
	else
	{
		if ((isJump && pRockman->getVy() > 0.0f) || ((pRockman->getPosition().y - mStartJump) >= 2 * 32 && pRockman->getVy() > 0.0f))
			pRockman->setVy(pRockman->getVy() - 0.05);
		else if (pRockman->getVy() <= 0.0f)
			fall = true;
	}
}

void RockManState::FallRoll(bool& fall) const
{
}

void RockManState::AppearState()
{
	isJump = true;
	isFall = false;
	isShoot = false;
	mStateName = Appear;

	pRockman->setVx(0.0f);
	pRockman->setVy(0.0f);
}

void RockManState::StandState(int key)
{
	isJump = true;		// Cho nhảy khi đứng hoặc chạy
	isFall = false;		// Cho nhảy thì không rơi
	isShoot = false;	// Chỉ bắn trong Shooting

	if (key == VK_X)
		mStateName = Jumping;
	else if (key == VK_LEFT || key == VK_RIGHT)
		mStateName = Running;
	else if (key == VK_Z)
		mStateName = StandingShoot;
	else
		mStateName = Standing;
}

void RockManState::RunState(int key)
{
	isJump = true;
	isFall = false;
	isShoot = false;

	if (key == VK_LEFT || key == VK_RIGHT)
	{
		if (key == VK_Z)
			mStateName = RunningShoot;
		else if (key == VK_X)
			mStateName = RunJump;
		else
		{
			isFall = true;
			Fall(isFall);
			mStateName = Running;

			if (pRockman->getVy() < -0.05)
			{
				isJump = false;
				pRockman->setVy(-1);
				mStateName = Jumping;
			}
		}
	}
	else
		mStateName = Standing;
}

void RockManState::JumpState(int key)
{
	isShoot = false;
	if (isJump)
	{
		mStartJump = pRockman->getPosition().y;
		pRockman->setVy(1);
		if (!isBleed)
		{
			isPush = false;
			// pRockman.setAllowDraw(true)
			mTimeBleed = 2.1f;
		}
	}
	isJump = false;
	if (!(key == VK_X) || (pRockman->getPosition().y - mStartJump) >= 88)
		isFall = true;
	if (isFall && pRockman->getVy() == 0.0f)
	{
		mStateName = Standing;
	}
	else
	{
		if (key == VK_Z)
			mStateName = JumpingShoot;
		else
		{
			Fall(isFall);
			mStateName = Jumping;
		}
	}
}

// Trạng thái chạy nhảy
void RockManState::RunJumpState(int key)
{
	isShoot = false;

	if (isJump)
	{
		mStartJump = pRockman->getVy();
		pRockman->setVy(1);
	}
	isJump = false;

	if (!(key == VK_X) || (pRockman->getPosition().y - mStartJump) >= 88)
		isFall = true;

	if (isFall && pRockman->getVy() == 0.0f)
	{
		isFall = false;

		if (pRockman->getVx() != 0)
			mStateName = Running;
		else
			mStateName = Standing;
	}
	else
	{
		if (key == VK_Z)
			mStateName = JumpingShoot;
		else
		{
			Fall(isFall);
			mStateName = RunJump;
		}
	}
}

void RockManState::ShootState(int key)
{
	//Rơi
	if (mStateName == Falling)
		Fall(isFall);

	if (mTimeShoot >= 0.1)
	{
		//Cho bắn
		isShoot = true;
		mTimeShoot = 0;

		switch (mStateName)
		{
		case StandingShoot:
			mStateName = Standing;
			break;

		case RunningShoot:
		{
			isJump = true;
			isFall = false;
			//Lấy trạng thái vẽ
			mStateName = RunningShoot;

			//Điều kiện thoát
			if (!(key == VK_Z) || pRockman->getVx() == 0.0f)
				mStateName = Running;
			else if (key == VK_X)
				mStateName = Jumping;
			//Điều kiện rơi
			if (pRockman->getVy() < -0.05 * 2)
			{
				isJump = false;
				isFall = true;
				pRockman->setVy(-1);
				mStateName = Jumping;
			}
			break;
		}

		case JumpingShoot:
		{
			if (!(key == VK_X))
				isFall = true;

			if (!(key == VK_Z) || (pRockman->getVy() <= 0.0f && pRockman->getVy() >= -0.05 * 2))
				mStateName = Jumping;
		}
		break;

		default: break;
		}
	}
	else 
		isShoot = false;
}

void RockManState::BleedState(int side, int dame, bool Bleed)
{
}

void RockManState::DeadState()
{
}

void RockManState::Update(float gameTime)
{
	//trạng thái mất máu
	if (isPush)
	{
		mTimeBleed += gameTime;
		if (isBleed)
		{
			//Mất máu thì nháy
			if (isAppear)
			{
				//Samus->SetAllowDraw(true);
				isAppear = false;
			}
			else
			{
				//Samus->SetAllowDraw(false);
				isAppear = true;
			}
		}

		//chỉnh Vận tốc
		mVelocityBleed.y = mVelocityBleed.y - 0.075f;

		//Đang bị đẩy
		if (mVelocityBleed.y > -1 && pRockman->getVy() != 0.0f)
		{
			pRockman->setVy(mVelocityBleed.y);

			if (mSide > 0)
				pRockman->setVx(-0.75);

			else if (mSide < 0)
				pRockman->setVx(0.75);
		}

		if (mTimeBleed > 2.0f)
		{
			isBleed = false;
			isPush = false;
			//Samus->SetAllowDraw(true);
		}
	}

	switch (mStateName)
	{
	case StandingShoot:
	case RunningShoot:
	case JumpingShoot:
	{
		mTimeShoot += gameTime;
		break;
	}
	case Appear:
		mTimeAppear += gameTime;
		break;
	default:
		break;
	}
}