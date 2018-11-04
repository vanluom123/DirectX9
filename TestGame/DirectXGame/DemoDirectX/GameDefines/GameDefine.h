#ifndef __GAME_DEFINE__
#define __GAME_DEFINE__

#define SAFE_RELEASE(p) { if ( (p) ) { (p)->Release(); (p) = NULL; } }
#define SAFE_DELETE(a) { if( (a) ) { delete (a); (a) = NULL; } }

namespace Define
{
	const char ANIMATION_STANDING[] = "Resources/mario/standingright.png";
	const char ANIMATION_JUMPING[] = "Resources/mario/jumpingright.png";
	const char ANIMATION_RUNNING[] = "Resources/mario/runningright.png";

	const char MEGAMAN_APPEAR[] = "Resources/Rockman/appear.png";
	const char MEGAMAN_STAND[] = "Resources/Rockman/standing.png";
	const char MEGAMAN_RUN[] = "Resources/Rockman/running.png";
	const char MEGAMAN_JUMP[] = "Resources/Rockman/jumping.png";
	const char MEGAMAN_FALL[] = "Resources/Rockman/falling.png";
	const char MEGAMAN_WIN[] = "Resources/Rockman/win.png";
	const char MEGAMAN_DIE[] = "Resources/Rockman/die.png";
	const char MEGAMAN_CLING[] = "Resources/Rockman/cling.png";
	const char MEGAMAN_CLIMB[] = "Resources/Rockman/climbing.png";
	const char MEGAMAN_SLIDE_HORIZONTAL[] = "Resources/Rockman/slide.png";
	const char MEGAMAN_SLIDE_HORIZONTAL_SHOOT[] = "Resources/Rockman/slideshoot.png";
	const char MEGAMAN_SLIDE_VERTICAL[] = "Resources/Rockman/slidevertical.png";
	const char MEGAMAN_SLIDE_VERTICAL_SHOOT[] = "Resources/Rockman/slideverticalshoot.png";

	const char WORLD_MAP[] = "Resources/marioworld1-1.tmx";

	const float PLAYER_MAX_JUMP_VELOCITY = 480.0f; //Max jump velocity
	const float PLAYER_MIN_JUMP_VELOCITY = -480.0f; //Min jump velocity
	const float PLAYER_MAX_RUNNING_SPEED = 350.0f; //Max speed of layer
	const float PLAYER_BOTTOM_RANGE_FALLING = 6.0f; // The collision side with the bottom of the bottom collision is smaller that layer will fall down
}

#endif
