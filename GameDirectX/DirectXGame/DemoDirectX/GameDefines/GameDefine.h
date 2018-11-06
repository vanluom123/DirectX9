#ifndef __GAME_DEFINE__
#define __GAME_DEFINE__

template<class T>
void SafeDelete(T& pValue)
{
	if(pValue)
	{
		delete pValue;
		pValue = nullptr;
	}
}

template<class T>
void SafeRelease(T& pValue)
{
	if (pValue)
	{
		pValue->Release();
		pValue = nullptr;
	}
}

#define SAFE_DELETE(p) SafeDelete(p)
#define SAFE_RELEASE(p) SafeRelease(p)

namespace MegaManState
{
	enum StateName
	{
		Appear,
		Standing,
		StandingShoot,
		Running,
		RunningShoot,
		Falling,
		FallingShoot,
		Jumping,
		JumpingShoot,
		Cling,
		ClingShoot,
		Climb,
		ClimbShoot,
		SlideVertical,
		SlideHorizontal,
		Win,
		Die
	};
}

namespace Define
{
	const char ANIMATION_STANDING[] = "Resources/mario/standingright.png";
	const char ANIMATION_JUMPING[] = "Resources/mario/jumpingright.png";
	const char ANIMATION_RUNNING[] = "Resources/mario/runningright.png";
	
	//const char MEGAMAN_APPEAR[] = "Resources/Rockman/appear.png";
	const char MEGAMAN_STAND[] = "Resources/rockman/standing.png";
	const char MEGAMAN_STAND_SHOOT[] = "Resources/rockman/standing_shoot.png";

	const char MEGAMAN_RUN[] = "Resources/rockman/running.png";
	const char MEGAMAN_RUN_SHOOT[] = "Resources/rockman/running_shoot.png";

	const char MEGAMAN_JUMP[] = "Resources/rockman/jumping.png";
	const char MEGAMAN_JUMP_SHOOT[] = "Resources/rockman/jumping_shoot.png";

	const char MEGAMAN_FALL[] = "Resources/rockman/falling.png";
	const char MEGAMAN_FALL_SHOOT[] = "Resources/rockman/falling_shoot.png";

	const char MEGAMAN_WIN[] = "Resources/rockman/finish.png";
	const char MEGAMAN_DIE[] = "Resources/rockman/die.png";
	const char MEGAMAN_CLING[] = "Resources/rockman/cling.png";
	const char MEGAMAN_CLING_SHOOT[] = "Resources/rockman/cling_shoot.png";

	const char MEGAMAN_CLIMB[] = "Resources/rockman/climb.png";
	const char MEGAMAN_CLIMB_SHOOT[] = "Resources/rockman/climb_shoot.png";
	const char MEGAMAN_CLIMB_PERFECT[] = "Resources/rockman/climb_perfect.png";

	const char MEGAMAN_SLIDE_VERTICAL[] = "Resources/rockman/slide_vertical.png";
	const char MEGAMAN_SLIDE_VERTICAL_SHOOT[] = "Resources/rockman/slide_vertical_shoot.png";

	const char MEGAMAN_DASH[] = "Resources/rockman/dash.png";
	const char MEGAMAN_DASH_SHOOT[] = "Resources/rockman/dash_shoot.png";
	const char MEGAMAN_BLEED[] = "Resources/rockman/bleed.png";

	const char WORLD_MAP[] = "Resources/marioworld1-1.tmx";

	const float PLAYER_MAX_JUMP_VELOCITY = 480.0f; //Max jump velocity
	const float PLAYER_MIN_JUMP_VELOCITY = -480.0f; //Min jump velocity
	const float PLAYER_MAX_RUNNING_SPEED = 350.0f; //Max speed of layer
	const float PLAYER_BOTTOM_RANGE_FALLING = 6.0f; // The collision side with the bottom of the bottom collision is smaller that layer will fall down
}

#endif
