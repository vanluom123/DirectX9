#ifndef __GAME_DEFINE__
#define __GAME_DEFINE__

#define SAFE_RELEASE(p) { if ( (p) ) { (p)->Release(); (p) = NULL; } }
#define SAFE_DELETE(a) { if( (a) ) { delete (a); (a) = NULL; } }

namespace Define
{
	CONST CHAR ANIMATION_STANDING[] = "Resources/mario/standingright.png";
	CONST CHAR ANIMATION_JUMPING[] = "Resources/mario/jumpingright.png";
	CONST CHAR ANIMATION_RUNNING[] = "Resources/mario/runningright.png";

	CONST CHAR WORLD_MAP[] = "";

	CONST FLOAT PLAYER_MAX_JUMP_VELOCITY = 480.0f; //Max jump velocity
	CONST FLOAT PLAYER_MIN_JUMP_VELOCITY = -480.0f; //Min jump velocity
	CONST FLOAT PLAYER_MAX_RUNNING_SPEED = 350.0f; //Max speed of layer
	CONST FLOAT PLAYER_BOTTOM_RANGE_FALLING = 6.0f; // The collision side with the bottom of the bottom collision is smaller that layer will fall down
}

#endif
