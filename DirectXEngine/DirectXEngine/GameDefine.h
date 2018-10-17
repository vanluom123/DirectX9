#ifndef _DEFINE_H
#define _DEFINE_H

namespace Define
{
	const char AnimationStanding[] = "./Resources/mario/standingright.png";
	const char AnimationRunning[] = "./Resources/mario/runningright.png";
	const char AnimationJumping[] = "./Resources/mario/jumpingright.png";

	const float PLAYER_MAX_JUMP_VELOCITY = 280.0f; 
	const float PLAYER_MIN_JUMP_VELOCITY = -280.0f;
	const float PLAYER_MAX_RUNNING_SPEED = 180.0f;
	const float PLAYER_BOTTOM_RANGE_FALLING = 8.0f;

	// Speed
	const float RunSpeed = 0.75f;
	const float Gravity = 1.0f;
	const float JumpSpeed = 1.0f;

	// Limited
	const float JumpMin = 32.0f;
	const float FallAc = 0.05f;
	const float JumMax = 88.0f;
}

#endif
