#ifndef __GAME_DEFINE_H__
#define __GAME_DEFINE_H__

#include <d3dx9.h>
#pragma warning(disable : 4244)
#pragma warning(disable : 4007)
#pragma warning(disable : 4305)
#pragma warning(disable : 4018)

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
	enum Side_Collision
	{
		eSide_None,
		eSide_Left,
		eSide_Right,
		eSide_Top,
		eSide_Bottom,
		eSide_TopLeft,
		eSide_TopRight,
		eSide_BottomLeft,
		eSide_BottomRight
	};

	// Object Type
	enum Object_Type
	{
		eOject_None,
		eOject_RockMan,
		eObject_Enemy,
		eObject_RockMan_Bullet,
		eObject_Enemy_Bullet,
		eObject_Boss,
		eObject_Elevator,
		eObject_Conveyor,
		eObject_Static,
		eObject_Port,
		eObject_Thorn,
		eObject_Box,
		eObject_Item
	};

	// Player state
	enum Player_State
	{
		ePlayer_None,
		ePlayer_Appear,
		ePlayer_Stand,
		ePlayer_Run,
		ePlayer_Fall,
		ePlayer_Jump,
		ePlayer_Cling,
		ePlayer_Climb,
		ePlayer_SlipDown,
		ePlayer_Dash,
		ePlayer_Bleed,
		ePlayer_Win,
		ePlayer_Death
	};

	// Blast Hornet
	enum Hornet_State
	{
		eHornet_None,
		eHornet_Idle,
		eHornet_Appear,
		eHornet_Move,
		eHornet_Shoot,
		eHornet_Attack,
		eHornet_Death
	};

	// Banger
	enum Banger_State
	{
		eBanger_None,
		eBanger_Stand,
		eBanger_Attack,
		eBanger_Death,
		eBanger_Fall,
		eBanger_Jump
	};

	// Gunner
	enum Gunner_State
	{
		eGunner_None,
		eGunner_Stand,
		eGunner_Fall,
		eGunner_Attack,
		eGunner_Attack_Rocket,
		eGunner_Attack_Bullet,
		eGunner_Death
	};

	// Helit
	enum Helit_State
	{
		eHelit_None,
		eHelit_Stand,
		eHelit_Attack,
		eHelit_Death
	};

	// Item
	enum Item_Type
	{
		eItem_None,
		eItem_Big_Blood,
		eItem_Small_Blood,
		eItem_Enegy,
		eItem_Subtank,
		eItem_Small_Subtank
	};

	// Genjibo state
	enum Genjibo_State
	{
		eGenjibo_None,
		eGenjibo_Move,
		eGenjibo_Jump
	};

	// Shurikein State
	enum Shurikein_State
	{
		eShurikein_None,
		eShurikein_Stand,
		eShurikein_Appear,
		eShurikein_Attack_1,
		eShurikein_Attack_2,
		eShurikein_Attack_3,
		eShurikein_Death
	};

	// Carry State
	enum Carry_State
	{
		eCarry_None,
		eCarry_Stand,
		eCarry_MoveDown,
		eCarry_MoveUp,
		eCarry_Event_MoveUp,
		eCarry_Event_MoveUp_2
	};

	enum EnemyBullet_State
	{
		eEnemyBullet_Fire,
		eEnemyBullet_Explosion
	};

	// Player Bullet Type
	enum PlayerBullet_Type
	{
		ePlayerBullet_Type_Normal,
		ePlayerBullet_Type_Explosion_Normal,
		ePlayerBullet_Type_First_Level,
		ePlayerBullet_Type_Explosion_First_Level,
		ePlayerBullet_Type_Second_Level,
		ePlayerBullet_Type_Explosion_Second_Level
	};

	// Player Bullet
	enum PlayerBullet_State
	{
		ePlayerBullet_Fire,
		ePlayerBullet_Explosion
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