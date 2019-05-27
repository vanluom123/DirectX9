#include "Player.h"
#include "GameState/FallState/FallState.h"
#include "GameState/JumpState/JumpState.h"
#include "GameState/JumpState/ClingState.h"
#include "../../GameComponents/GameGlobal.h"
#include "GameState/AppearState/AppearState.h"
#include "GameState/DashState/DashState.h"
#include "GameState/DieState/DieState.h"
#include "GameState/StandState/StandState.h"
#include "GameState/BleedState/BleedState.hpp"
#include "../../GameDefines/GameDefine.h"

Player::Player()
{
	m_objectType = OBJECT_ROCK_MAN;
	this->SetId(0);
	m_animation = new Animation(Define::ANIMATION_ROCKMAN, 21, 10, 49, 49, 0.15, D3DCOLOR_XRGB(100, 100, 100));
	m_animationEfectCharge = new Animation(Define::ANIMATION_CHARGE, 2, 12, 55, 65, 0.02);
	m_animationEfectDash = new Animation(Define::ANIMATION_DASH, 1, 11, 75, 35, 0.15);
	m_animationEfectSlide = new Animation(Define::ANIMATION_SLIDE, 1, 2, 30, 30, 0.15);
	m_HPBar = new HPBar(m_objectType);

	m_animationEfectCharge->SetPause(true);
	m_animationEfectDash->SetPause(true);
	m_animationEfectSlide->SetAnimation(0, 2, 0.1);
	m_animationEfectSlide->SetPause(true);

	m_allowJump = true;
	m_allowShoot = true;
	m_allowDash = true;
	m_isReverse = false;

	m_isShoot = false;
	m_alive = false;
	m_islock = false;

	m_timeShoot = 0.3f;
	m_timeCurrentShoot = 0.0f;
	m_timeChangeShoot = 0.0f;
	m_timeAlive = 0.0f;

	m_vx = 0;
	m_vy = 0;
	m_MaxHP = 15;
	m_HP = m_MaxHP;
	m_Damage = 0;

	m_currentState = FALL;

	m_playerData = new PlayerData;
	m_playerData->player = this;
	m_playerData->state = NULL;

	this->SetState(new AppearState(m_playerData));
}

Player::~Player()
{
	delete m_HPBar;
	delete m_animation;
	delete m_playerData;

	for (auto& bullet : m_listPlayerBullet)
		delete bullet;
	m_listPlayerBullet.clear();
}

void Player::ChangeAnimation(ePlayerState state)
{
	switch (state)
	{
	case APPEAR:
		m_animation->SetAnimation(0, 5, 0.15f, false);
		break;

	case STAND:
		m_animation->SetAnimation(1, 4, 0.1f, false);
		break;

	case RUN:
		m_animation->SetAnimation(3, 10, 0.05f);
		break;

	case JUMP:
		m_animation->SetAnimation(5, 3, 0.05f, false);
		break;

	case FALL:
		m_animation->SetAnimation(7, 3, 0.05f, false);
		break;

	case CLING:
		m_animation->SetAnimation(9, 4, 0.03f, false);
		break;

	case SLIP_DOWN:
		m_animation->SetAnimation(11, 3, 0.05f, false);
		break;

	case DASH:
		m_animation->SetAnimation(16, 2, 0.05f, false);
		break;

	case CLIMB:
		break;

	case BLEED:
		m_animation->SetAnimation(18, 9, 0.05f);
		break;

	case DIE:
		m_animation->SetAnimation(20, 3, 0.3f);
		break;

	case WIN: break;

	default: break;
	}

	this->SetWidth(m_animation->GetWidth());
	this->SetHeight(m_animation->GetHeight());
}

void Player::SetState(PlayerState* newState)
{
	if (m_currentState == newState->GetState())
		return;

	SAFE_DELETE(m_playerData->state);
	m_playerData->state = newState;

	ChangeAnimation(newState->GetState());
	m_currentState = newState->GetState();

	if (m_currentState != DASH && m_currentState != CLING)
		m_animationEfectDash->SetPause(true);

	if (m_currentState == SLIP_DOWN)
		m_posSlideDown = m_posY;

	else
		m_posSlideDown = std::numeric_limits<float>::infinity();
}



#pragma region GETTER, SETTER

Animation* Player::GetAnimation() const
{
	return m_animation;
}

float Player::GetHP() const
{
	return this->m_HP;
}

void Player::SetHP(float hp)
{
	this->m_HP = hp;
}

void Player::addHP(float hp)
{
	this->m_HP += hp;
}

std::vector<PlayerBullet*>* Player::GetPlayerBullet()
{
	return &m_listPlayerBullet;
}

void Player::SetLock(bool lock)
{
	m_islock = lock;
}

PlayerData* Player::GetPlayerData() const
{
	return m_playerData;
}

Player::ePlayerState Player::GetCurrentState() const
{
	return m_currentState;
}

#pragma endregion


void Player::KeyBoardEventHandler(const std::map<int, bool>& keys, float dt)
{
	if (!m_islock)
	{
		if (m_playerData->state)
			m_playerData->state->KeyBoardEventHandler(keys, dt);
	}
	m_islock = false;
}

void Player::OnKeyDown(std::map<int, bool> keys, int Key)
{
	if (m_islock)
		return;

	if (m_currentState == DIE
		|| m_currentState == APPEAR
		|| m_currentState == WIN
		|| m_currentState == BLEED)
		return;

	if (Key == VK_JUMP && m_allowJump)
	{
		m_allowJump = false;
		switch (m_currentState)
		{
		case STAND: case RUN: case DASH:
		{
			SetState(new JumpState(m_playerData));
			break;
		}
		case SLIP_DOWN:
		{

			m_animationEfectDash->SetReverse(!m_isReverse);
			if (m_isReverse)
				m_animationEfectDash->SetPosition(m_posX, m_posY + 12);
			else
				m_animationEfectDash->SetPosition(m_posX, m_posY + 12);

			m_animationEfectDash->SetAnimation(1, 1, 0.005, false);
			if (keys[VK_SLIDE])
				SetState(new ClingState(m_playerData, true));
			else
				SetState(new ClingState(m_playerData));
			break;
		}
		default: break;
		}
	}

	if (Key == VK_SHOOT && m_allowShoot)
	{
		if (m_currentState == BLEED)
			return;

		if (!m_isShoot)
		{
			m_isShoot = true;
			m_animation->SetShoot(m_isShoot);

		}
		PlayerShoot(PlayerBullet::BULLET_TYPE_NORMAL);
		Sound::GetInstance()->Play("ShootingBullet", false, 1);

		m_allowShoot = false;
		m_timeCurrentShoot = 0.0f;
	}

	if (Key == VK_SLIDE && m_allowDash)
	{
		m_allowDash = false;

		switch (m_currentState)
		{
		case STAND: case RUN:
			m_animationEfectDash->SetReverse(m_isReverse);
			m_animationEfectDash->SetPosition(m_posX, m_posY + 12);
			m_animationEfectDash->SetAnimation(0, 11, 0.05, false);
			SetState(new DashState(m_playerData));
			break;
		default: break;
		}
	}
}

void Player::OnKeyUp(int Key)
{
	if (m_islock)
		return;

	switch (Key)
	{
	case VK_JUMP:
	{
		if (m_currentState == JUMP || m_currentState == CLING)
			m_vy = 0;
		m_allowJump = true;
		break;
	}
	case VK_SHOOT:
	{
		m_allowShoot = true;
		m_animationEfectCharge->SetPause(true);

		if (m_currentState == BLEED)
			return;

		if (m_timeChangeShoot > m_timeShoot * 4)
		{
			m_isShoot = true;
			m_animation->SetShoot(m_isShoot);
			//The second level
			PlayerShoot(PlayerBullet::BULLET_TYPE_SECOND_LEVEL);
			Sound::GetInstance()->Stop("AbsorbLongEnergy");
			Sound::GetInstance()->Play("GiveUpLongEnergy", false, 1);
		}
		else
		{
			if (m_timeChangeShoot > m_timeShoot * 2)
			{
				m_isShoot = true;
				m_animation->SetShoot(m_isShoot);
				//The first level
				PlayerShoot(PlayerBullet::BULLET_TYPE_FIRST_LEVEL);
				Sound::GetInstance()->Stop("AbsorbShortEnergy");
				Sound::GetInstance()->Play("GiveUpShortEnergy", false, 1);
			}
		}

		m_timeChangeShoot = 0.0f;

		break;
	}
	case VK_SLIDE:
	{
		if (m_currentState == DASH)
			SetState(new StandState(m_playerData));
		m_allowDash = true;
		break;
	}
	default:break;
	}
}

RECT Player::GetBound()
{
	RECT bound;
	bound.left = m_posX - 13;
	bound.right = m_posX + 13;
	bound.top = m_posY - 15;
	bound.bottom = m_posY + 49 / 2.0f;

	return bound;
}

void Player::Update(float dt)
{
	OnNoCollisionWithBottom();

	for (auto& bullet : m_listPlayerBullet)
		bullet->Update(dt);

	if (m_isShoot)
	{
		m_timeCurrentShoot += dt;
		if (m_timeCurrentShoot > m_timeShoot)
		{
			m_isShoot = false;
			m_animation->SetShoot(m_isShoot);
			m_timeCurrentShoot = 0;
		}
	}

	//Animation Charge Bullet
	if (!m_allowShoot)
	{
		m_timeChangeShoot += dt;

		if (m_timeChangeShoot > m_timeShoot * 4)
		{
			Sound::GetInstance()->Stop("AbsorbShortEnergy");
			Sound::GetInstance()->Play("AbsorbLongEnergy", true, 0);
			m_animationEfectCharge->SetPause(false);
			if (m_animationEfectCharge->GetCurrentRow() != 1)
				m_animationEfectCharge->SetAnimation(1, 12, 0.017);
		}
		else if (m_timeChangeShoot > m_timeShoot * 2)
		{
			Sound::GetInstance()->Play("AbsorbShortEnergy", true, 0);
			m_animationEfectCharge->SetPause(false);
			if (m_animationEfectCharge->GetCurrentRow() != 0)
				m_animationEfectCharge->SetAnimation(0, 12, 0.02);
		}
	}


	// Time is alive
	if (m_alive)
	{
		m_timeAlive += dt;
		if (m_timeAlive > 1.5f)
		{
			m_alive = false;
			m_isAllowDraw = true;
			m_timeAlive = 0.0f;
		}
		else
		{
			// 0.1 time twinkle
			int TimePause = m_timeAlive / 0.05f;
			if (TimePause % 2 == 0)
				m_isAllowDraw = true;
			else if (TimePause % 2 == 1)
				m_isAllowDraw = false;
		}
	}

	if (m_posY - m_posSlideDown > 8)
		m_animationEfectSlide->SetPause(false);
	else
		m_animationEfectSlide->SetPause(true);

	BaseObject::Update(dt);
	m_animation->Update(dt);
	m_animationEfectCharge->Update(dt);
	m_animationEfectDash->Update(dt);
	m_animationEfectSlide->Update(dt);

	if (m_playerData->state)
		m_playerData->state->Update(dt);
}

void Player::DrawHP()
{
	m_HPBar->draw(m_HP, m_MaxHP);
}

void Player::Draw(Camera* camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter,
	D3DCOLOR color)
{
	for (auto& bullet : m_listPlayerBullet)
		bullet->Draw(camera);

	if (!m_isAllowDraw)
		return;

	m_animation->SetReverse(m_isReverse);
	m_animation->SetPosition(GetPosition());

	if (camera)
	{
		m_animation->Draw(m_animation->GetPosition(), rect, scale, camera->GetTrans(), angle, rotationCenter, color);
		if (!m_animationEfectCharge->GetPause())
		{
			m_animationEfectCharge->SetReverse(m_isReverse);
			m_animationEfectCharge->SetPosition(m_posX, m_posY + 6);
			m_animationEfectCharge->Draw(m_animationEfectCharge->GetPosition(), rect, scale, camera->GetTrans(), angle, rotationCenter, color);
		}

		if (!m_animationEfectDash->GetPause())
			m_animationEfectDash->Draw(m_animationEfectDash->GetPosition(), rect, scale, camera->GetTrans(), angle, rotationCenter, color);

		if (!m_animationEfectSlide->GetPause())
		{
			m_animationEfectSlide->SetReverse(m_isReverse);
			if (m_isReverse)
				m_animationEfectSlide->SetPosition(m_posX - 15, m_posY);
			else
				m_animationEfectSlide->SetPosition(m_posX + 15, m_posY);

			m_animationEfectSlide->Draw(m_animationEfectSlide->GetPosition(), rect, scale, camera->GetTrans(), angle, rotationCenter, color);
		}
	}
	else
		m_animation->Draw(m_animation->GetPosition());
}

void Player::OnCollision(eSideCollision side)
{
	if (m_sideX != SIDE_COLLISION_NONE)
	{
		if (m_entityX->GetObjectType() == OBJECT_PORT)
		{
			if (m_entityX->GetHP() <= 0)
			{
				m_sideX = BaseObject::SIDE_COLLISION_NONE;
				m_collisionTimeMinX = 1.0f;
				return;
			}
		}
	}
	if (m_playerData->state)
		m_playerData->state->OnCollision(side);
}

void Player::OnNoCollisionWithBottom()
{
	if (m_sideY != SIDE_COLLISION_BOTTOM)
	{
		switch (m_currentState)
		{
		case STAND:case RUN:case DASH:
			SetState(new FallState(m_playerData));
			break;
		default:break;
		}
	}
}

void Player::OnCollision(BaseObject* object)
{
	switch (object->GetObjectType())
	{
	case BaseObject::OBJECT_ENEMY:
	case BaseObject::OBJECT_ENEMY_BULLET:
	case BaseObject::OBJECT_BOSS:
	{
		if (m_alive)
			return;

		//HP -= object->GetDamage();
		m_alive = true;
		if (m_HP <= 0)
		{
			SetState(new DieState(m_playerData));
			m_alive = false;
			m_isDie = true;
			return;
		}

		m_animation->SetShoot(false);

		if (m_posX < object->GetPosition().x)
			SetState(new BleedState(m_playerData, 1));
		else
			SetState(new BleedState(m_playerData, -1));
		break;
	}

	case BaseObject::OBJECT_ELEVATOR:
	{
		if (m_currentState == JUMP || m_currentState == CLING)
			break;
		m_posY = object->GetBound().top - 24.51f;
		m_sideY = SIDE_COLLISION_BOTTOM;
		break;
	}

	case BaseObject::OBJECT_PORT:
	{
		if (object->GetHP() <= 0 && GetBound().top > object->GetBound().top)
		{
			m_islock = true;
			if (object->GetDamage() > 0)
			{
				// Player standing
				m_animation->SetPause(false);
			}
			else
			{
				// Player moving
				m_animation->SetPause(true);
			}
		}

		break;
	}

	case BaseObject::OBJECT_THORN:
	{
		m_HP = 0;
		m_isDie = true;
		SetState(new DieState(m_playerData));
		m_alive = false;
		break;
	}

	case BaseObject::OBJECT_UNKNOWN:
		break;
	default:
		break;
	}
}

void Player::PlayerShoot(PlayerBullet::eBulletType bulletType)
{
	PlayerBullet* playerBullet = NULL;

	if (m_listPlayerBullet.size() < 3)
	{
		playerBullet = new PlayerBullet();
		m_listPlayerBullet.push_back(playerBullet);
	}
	else
	{
		for (auto& bullet : m_listPlayerBullet)
			if (bullet->GetExplosion())
			{
				playerBullet = bullet;
				break;
			}
		if (playerBullet == NULL)
			return;
	}

	bool isReverseBullet = m_isReverse;
	float posX = 0;
	float posY = this->GetBound().bottom - 18;

	if (m_currentState == SLIP_DOWN)
	{
		isReverseBullet = !m_isReverse;
		if (!m_isReverse)
			posX = this->GetBound().left + playerBullet->GetWidth() / 4.0f;
		else
			posX = this->GetBound().right - playerBullet->GetWidth() / 4.0f;
	}
	else
	{
		if (!m_isReverse)
			posX = this->GetBound().right - playerBullet->GetWidth() / 4.0f;
		else
			posX = this->GetBound().left + playerBullet->GetWidth() / 4.0f;
	}

	playerBullet->NewBullet(posX, posY, isReverseBullet, bulletType);
}