#ifndef __GAME_DEFINE_H__
#define __GAME_DEFINE_H__

#include <d3d9.h>
#include <d3dx9.h>

// Safely delete pointer referenced item
#define SAFE_DELETE(ptr)       { if (ptr) { delete (ptr); (ptr)=NULL; } }
// Safely release pointer referenced item
#define SAFE_RELEASE(ptr)      { if(ptr) { (ptr)->Release(); (ptr)=NULL; } }
// Safely delete pointer referenced array
#define SAFE_DELETE_ARRAY(ptr) { if(ptr) { delete [](ptr); (ptr)=NULL; } }

#define VK_SLIDE	0x43
#define VK_JUMP		0x58
#define VK_SHOOT	0x5A

typedef D3DXVECTOR3 GVec3;
typedef D3DXVECTOR2 GVec2;
#define Gvec2Zero GVec2(0.0f, 0.0f)
#define Gvec3Zero GVec3(0.0f, 0.0f, 0.0f)

enum eSoundID
{

};

namespace Define
{
	const char ANIMATION_ROCKMAN[]       = "Resources/rockman/Rockman_49x49_background(100,100,100).png";
	const char ANIMATION_CHARGE[]        = "Resources/rockman/Charge.png";
	const char ANIMATION_DASH[]          = "Resources/rockman/EffectDash.png";
	const char ANIMATION_SLIDE[]         = "Resources/rockman/EffectSlide.png";

	const char PLAYER_BULLET[]           = "Resources/rockman/RockManBullet.png";

	const char NOTOR_BANGER_BULLET[]     = "Resources/Enemies/NotorBanger/NotorBangerBullet.png";
	const char NOTOR_BANGER_SPRITE[]     = "Resources/Enemies/NotorBanger/NotorBangerSprite.png";

	const char HEAD_GUNNER_SPRITE[]      = "Resources/Enemies/HeadGunnerCustomer/HeadGunnerSpriteSheet.png";
	const char HEAD_GUNNER_BULLET[]      = "Resources/Enemies/HeadGunnerCustomer/HeadGunnerBullet.png";

	const char GUNNER_DIE[]              = "Resources/Enemies/HeadGunnerCustomer/GunnerDie.png";
	const char BANGER_DIE[]              = "Resources/Enemies/NotorBanger/NotorBangerDie.png";

	const char HELIT_SPRITE_SHEET[]      = "Resources/Enemies/Helit/HelitSpriteSheet.png";
	const char HELIT_BULLET[]            = "Resources/Enemies/Helit/HelitBullet.png";
	const char HELIT_DIE[]               = "Resources/Enemies/Helit/HelitDie.png";

	const char CARRY_ARM[]               = "Resources/Enemies/CarryArm/ArmSpriteSheet.png";

	const char GENJIBO_SHURIKEIN[]       = "Resources/Enemies/Genjibo/ShurikenSpriteSheet.png";
	const char SHURIKEN[]                = "Resources/Enemies/Genjibo/GenjiboSprite.png";

	const char BURST[]                   = "Resources/Enemies/Burst.png";
	const char EXPLOSIONS[]				 = "Resources/Enemies/Explosions/RedExplosionsSpriteSheet.png";

	const char WORLD_MAP_PNG[]           = "Resources/Map/MapStage1.png";
	//const char WORLD_MAP[]             = "Resources/Map/MapDemoLoad.tmx";
	const char WORLD_MAP[]               = "Resources/Map/Map1.tmx";
	const char Elevator[]                = "Resources/MapObject/Elevator.png";

	const float PLAYER_MAX_JUMP_VELOCITY = 300.0f; //Max jump velocity
	const float PLAYER_MIN_JUMP_VELOCITY = -300.0f; //Min jump velocity
	const float PLAYER_MAX_RUNNING_SPEED = 125.0f; //Max speed of layer
	const float PLAYER_MAX_CLING_SPEED   = 25.0f; //Max speed of layer
	const float PLAYER_MAX_SLIDE_SPEED   = 230.0f;

	const float ENEMY_MAX_JUMP_VELOCITY  = 300.0f;
	const float ENEMY_MIN_JUMP_VELOCITY  = -300.0f;
}

#endif