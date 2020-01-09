#ifndef __GAME_DEFINE_H__
#define __GAME_DEFINE_H__

#include <d3dx9.h>
#include <d3d9.h>
#include <vector>
#include <map>
#include <iostream>
using namespace std;

// Safely delete pointer referenced item
#define SAFE_DELETE(ptr)       { if (ptr) { delete (ptr); (ptr)=NULL; } }
// Safely release pointer referenced item
#define SAFE_RELEASE(ptr)      { if(ptr) { (ptr)->Release(); (ptr)=NULL; } }
// Safely delete pointer referenced array
#define SAFE_DELETE_ARRAY(ptr) { if(ptr) { delete [](ptr); (ptr)=NULL; } }

constexpr auto VK_SLIDE = 0x43;
constexpr auto VK_JUMP = 0x58;
constexpr auto VK_SHOOT = 0x5A;

typedef D3DXVECTOR3 GVec3;
typedef D3DXVECTOR2 GVec2;
#define Gvec2Zero GVec2(0.0f, 0.0f)
#define Gvec3Zero GVec3(0.0f, 0.0f, 0.0f)

namespace Enumerator
{
	enum class Side_Collision
	{
		NONE,
		LEFT,
		RIGHT,
		TOP,
		BOTTOM,
		TOP_LEFT,
		TOP_RIGHT,
		BOTTOM_LEFT,
		BOTTOM_RIGHT
	};

	// Object Type
	enum class Object_Type
	{
		NONE,
		ROCKMAN,
		ENEMY,
		ROCKMAN_BULLET,
		ENEMY_BULLET,
		BOSS,
		ELEVATOR,
		CONVEYOR,
		STATIC,
		PORT,
		THORN,
		BOX,
		ITEM
	};

	// Player state
	enum class Player_State
	{
		NONE,
		APPEAR,
		STAND,
		RUN,
		FALL,
		JUMP,
		CLING,
		CLIMB,
		SLIP_DOWN,
		DASH,
		BLEED,
		WIN,
		DEATH
	};

	// Blast Hornet
	enum class Hornet_State
	{
		NONE,
		STAND,
		APPEAR,
		MOVE,
		SHOOT,
		ATTACK,
		DEATH
	};

	// Banger
	enum class Banger_State
	{
		NONE,
		STAND,
		ATTACK,
		DEATH,
		FALL,
		JUMP
	};

	// Gunner
	enum class Gunner_State
	{
		NONE,
		STAND,
		FALL,
		ATTACK,
		ATTACK_ROCKET,
		ATTACK_BULLET,
		DEATH
	};

	// Helit
	enum class Helit_State
	{
		NONE,
		STAND,
		ATTACK,
		DEATH
	};

	// Item
	enum class Item_Type
	{
		NONE,
		BIG_BLOOD,
		SMALL_BLOOD,
		ENEGY,
		SUBTANK,
		SMALL_SUBTANK
	};

	// Genjibo state
	enum class Genjibo_State
	{
		NONE,
		MOVE,
		JUMP
	};

	// Shurikein State
	enum class Shurikein_State
	{
		NONE,
		STAND,
		APPEAR,
		ATTACK_1,
		ATTACK_2,
		ATTACK_3,
		DEATH
	};

	// Carry State
	enum class Carry_State
	{
		NONE,
		STAND,
		MOVE_DOWN,
		MOVE_UP,
		EVENT_MOVE_UP,
		EVENT_MOVE_UP_2
	};

	enum class EnemyBullet_State
	{
		NONE,
		FIRE,
		EXPLOSION
	};

	// Player Bullet Type
	enum class PlayerBullet_Type
	{
		BULLET_NORMAL,
		EXPLOSION_NORMAL,
		BULLET_FIRST_LEVEL,
		EXPLOSION_FIRST_LEVEL,
		BULLET_SECOND_LEVEL,
		EXPLOSION_SECOND_LEVEL
	};

	// Player Bullet
	enum class PlayerBullet_State
	{
		NONE,
		FIRE,
		EXPLOSION
	};
}

namespace Define
{
	// ROCK MAN SPRITE ANIMATION
	const char ANIMATION_ROCKMAN[] = "Resources/RockMan/rock_man_sprite_sheet.png";
	const char ANIMATION_CHARGE[] = "Resources/RockMan/Charge.png";
	const char ANIMATION_DASH[] = "Resources/RockMan/EffectDash.png";
	const char ANIMATION_SLIDE[] = "Resources/RockMan/EffectSlide.png";

	// ROCK MAN BULLET
	const char ROCKMAN_BULLET[] = "Resources/RockMan/bullet.png";
	const char ROCKMAN_BULLET_LEVEL_1[] = "Resources/RockMan/bullet_level_1.png";
	const char ROCKMAN_BULLET_LEVEL_2[] = "Resources/RockMan/bullet_level_2.png";
	const char ROCKMAN_EXPLOSION[] = "Resources/RockMan/explosions_bullet.png";
	const char ROCKMAN_EXPLOSION_LEVEL_1[] = "Resources/RockMan/explosion_level_1.png";
	const char ROCKMAN_EXPLOSION_LEVEL_2[] = "Resources/RockMan/explosion_level_2.png";

	// NOTOR BANGER
	const char NOTOR_BANGER_BULLET[] = "Resources/Enemies/NotorBanger/NotorBangerBullet.png";
	const char NOTOR_BANGER_SPRITE[] = "Resources/Enemies/NotorBanger/NotorBangerSprite.png";
	const char BANGER_DIE[] = "Resources/Enemies/NotorBanger/NotorBangerDie.png";

	// HEAD GUNNER
	const char HEAD_GUNNER_SPRITE[] = "Resources/Enemies/HeadGunnerCustomer/HeadGunnerSpriteSheet.png";
	const char HEAD_GUNNER_BULLET[] = "Resources/Enemies/HeadGunnerCustomer/HeadGunnerBullet.png";
	const char GUNNER_DIE[] = "Resources/Enemies/HeadGunnerCustomer/GunnerDie.png";

	// HELIT
	const char HELIT_SPRITE_SHEET[] = "Resources/Enemies/Helit/HelitSpriteSheet.png";
	const char HELIT_BULLET[] = "Resources/Enemies/Helit/HelitBullet.png";
	const char HELIT_DIE[] = "Resources/Enemies/Helit/HelitDie.png";

	// CARRY ARM
	const char CARRY_ARM[] = "Resources/Enemies/CarryArm/ArmSpriteSheet.png";
	const char SUB_BOSS_CARRY_ARM[] = "Resources/Enemies/CarryArm/x3_subboss_carryarm_01.png";
	const char CARRY_ARM_ATTACK[] = "Resources/Enemies/CarryArm/attack.png";
	const char CARRY_ARM_BULLET[] = "Resources/Enemies/CarryArm/bullet.png";

	// GENJIBO AND SHURIKEIN
	const char GENJIBO_SHURIKEIN[] = "Resources/Enemies/Genjibo/ShurikenSpriteSheet.png";
	const char SHURIKEN[] = "Resources/Enemies/Genjibo/GenjiboSprite.png";

	// BLAST HORNET
	const char BLAST_HORNET_IDLE[] = "Resources/Enemies/BlastHornet/State/Stand/animation_stand.png";
	const char BLAST_HORNET_APPEAR[] = "Resources/Enemies/BlastHornet/State/Appear/animation_appear.png";
	const char BLAST_HORNET_ATTACK[] = "Resources/Enemies/BlastHornet/State/Attack/animation_attack.png";
	const char BLAST_HORNET_SHOOT[] = "Resources/Enemies/BlastHornet/State/Shooter/animation_shoot.png";
	// BULLET OF BLAST HORNET
	const char BULLET_BLAST_HORNET[] = "Resources/Enemies/BlastHornet/Bullet/BulletAnim.png";
	// THE EXPLOSION OF BLAST HORNET
	const char EXPLOSION_BLAST_HORNET[] = "Resources/Enemies/BlastHornet/Burst/BurstAnimation.png";

	const char BURST[] = "Resources/Enemies/Burst.png";
	const char EXPLOSIONS[] = "Resources/Enemies/Explosions/RedExplosionsSpriteSheet.png";

	const char WORLD_MAP_PNG[] = "Resources/Map/MapStage1.png";
	const char WORLD_MAP[] = "Resources/Map/Map1.tmx";
	const char Elevator[] = "Resources/MapObject/Elevator.png";

	// ITEM
	const char SUB_TANK_ITEM[] = "Resources/Items/sub-tanks.bmp";
	const char SMALL_SUB_TANK_ITEM[] = "Resources/Items/sub-tanks_small.bmp";
	const char ENEGY_ITEM[] = "Resources/Items/energy-hearts.bmp";
	const char BLOOD_IS_SMALL_ITEM[] = "Resources/Items/small_blood.bmp";
	const char BLOOD_IS_BIG_ITEM[] = "Resources/Items/big_blood.bmp";

	// BOX
	const char BOXX[] = "Resources/Enemies/CarryArm/box.png";

	// PISTOL
	const char PISTOL[] = "Resources/Enemies/CarryArm/x3_subboss_carryarm_39.png";

	const float PLAYER_MAX_JUMP_VELOCITY = 300.0f;
	const float PLAYER_MIN_JUMP_VELOCITY = -300.0f;
	const float PLAYER_MAX_RUNNING_SPEED = 125.0f;
	const float PLAYER_MAX_CLING_SPEED = 25.0f;
	const float PLAYER_MAX_SLIDE_SPEED = 230.0f;

	const float ENEMY_MAX_JUMP_VELOCITY = 300.0f;
	const float ENEMY_MIN_JUMP_VELOCITY = -300.0f;
}

#endif