#pragma once
#include "../Entity/Entity.h"

class RockManState
{
	Entity *pRockman;
	bool	isAppear,
			isJump, 
			allowJump,
			isFall, 
			isShoot, 
			isBleed, 
			isPush;

	float	mStartJump, 
			mTimeShoot, 
			mTimeBleed, 
			mTimeAppear;

	D3DXVECTOR3 mVelocityBleed;
	int mSide;
public:
	explicit RockManState(Entity *rockman);
	RockManState() = default;
	~RockManState() = default;

	enum StateName
	{
		Appear,
		Standing,
		StandingShoot,
		Running,
		RunningShoot,
		RunJump,
		Falling,
		FallingShoot,
		Jumping,
		JumpingShoot,
		Cling,
		ClingShoot,
		Climb,
		ClimbShoot,
		SlideVertical,
		SlideVerticalShoot,
		SlideHorizontal,
		SlideHorizontalShoot,
		Win,
		Die
	};

	void Fall(bool &fall) const;//Rơi
	void FallRoll(bool &fall) const;
	void AppearState();
	void StandState(int key);
	void RunState(int key);
	void JumpState(int key);
	void RunJumpState(int key);
	void ShootState(int key);
	void BleedState(int side, int dame, bool Bleed);
	void DeadState();

	StateName mStateName;

	void Update(float dt);
};
