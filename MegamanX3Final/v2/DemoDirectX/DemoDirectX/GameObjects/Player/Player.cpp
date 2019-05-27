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
	_objectType = ROCK_MAN;
	this->SetId(0);
	_pAnimation = new Animation(Define::ANIMATION_ROCKMAN, 21, 10, 49, 49, 0.15, D3DCOLOR_XRGB(100, 100, 100));
	_pAniEfectCharge = new Animation(Define::ANIMATION_CHARGE, 2, 12, 55, 65, 0.02);
	_pAniEfectDash = new Animation(Define::ANIMATION_DASH, 1, 11, 75, 35, 0.15);
	_pAniEfectSlide = new Animation(Define::ANIMATION_SLIDE, 1, 2, 30, 30, 0.15);
	_hpbar = new HPBar(_objectType);

	_pAniEfectCharge->SetPause(true);
	_pAniEfectDash->SetPause(true);
	_pAniEfectSlide->SetAnimation(0, 2, 0.1);
	_pAniEfectSlide->SetPause(true);

	_allowJump = true;
	_allowShoot = true;
	_allowDash = true;
	_isReverse = false;

	_isShoot = false;
	_alive = false;
	_islock = false;

	_timeShoot = 0.3f;
	_timeCurrentShoot = 0.0f;
	_timeChangeShoot = 0.0f;
	_timeAlive = 0.0f;

	_vx = 0;
	_vy = 0;
	_MaxHP = 15;
	_HP = _MaxHP;
	_Damage = 0;

	_currentState = FALL;

	_playerData = new PLAYERDATA;
	_playerData->player = this;
	_playerData->state = NULL;

	this->SetState(new AppearState(_playerData));
}

Player::~Player()
{
	delete _hpbar;
	delete _pAnimation;
	delete _playerData;

	for (auto& bullet : _listBullet)
		delete bullet;
	_listBullet.clear();
}

void Player::ChangeAnimation(ePlayerState state)
{
	switch (state)
	{
	case APPEAR:
		_pAnimation->SetAnimation(0, 5, 0.15, false);
		break;

	case STAND:
		_pAnimation->SetAnimation(1, 4, 0.1, false);
		break;

	case RUN:
		_pAnimation->SetAnimation(3, 10, 0.05);
		break;

	case JUMP:
		_pAnimation->SetAnimation(5, 3, 0.05, false);
		break;

	case FALL:
		_pAnimation->SetAnimation(7, 3, 0.05, false);
		break;

	case CLING:
		_pAnimation->SetAnimation(9, 4, 0.03, false);
		break;

	case SLIP_DOWN:
		_pAnimation->SetAnimation(11, 3, 0.05, false);
		break;

	case DASH:
		_pAnimation->SetAnimation(16, 2, 0.05, false);
		break;

	case CLIMB:
		break;

	case BLEED:
		_pAnimation->SetAnimation(18, 9, 0.05);
		break;

	case DIE:
		_pAnimation->SetAnimation(20, 3, 0.3f);
		break;

	case WIN: break;

	default: break;
	}

	this->SetWidth(_pAnimation->GetWidth());
	this->SetHeight(_pAnimation->GetHeight());
}

void Player::SetState(PlayerState* newState)
{
	if (_currentState == newState->GetState())
		return;

	SAFE_DELETE(_playerData->state);
	_playerData->state = newState;

	ChangeAnimation(newState->GetState());
	_currentState = newState->GetState();

	if (_currentState != DASH && _currentState != CLING)
		_pAniEfectDash->SetPause(true);

	if (_currentState == SLIP_DOWN)
		_posSlideDown = _posY;

	else
		_posSlideDown = std::numeric_limits<float>::infinity();
}



#pragma region GETTER, SETTER

Animation* Player::GetAnimation() const
{
	return _pAnimation;
}

float Player::GetHP() const
{
	return this->_HP;
}

void Player::SetHP(float hp)
{
	this->_HP = hp;
}

void Player::addHP(float hp)
{
	this->_HP += hp;
}

std::vector<PlayerBullet*>* Player::GetPlayerBullet()
{
	return &_listBullet;
}

void Player::SetLock(bool lock)
{
	_islock = lock;
}

PLAYERDATA* Player::GetPlayerData() const
{
	return _playerData;
}

Player::ePlayerState Player::GetCurrentState() const
{
	return _currentState;
}

#pragma endregion


void Player::KeyBoardEventHandler(const std::map<int, bool>& keys, float dt)
{
	if (!_islock)
	{
		if (_playerData->state)
			_playerData->state->KeyBoardEventHandler(keys, dt);
	}
	_islock = false;
}

void Player::OnKeyDown(std::map<int, bool> keys, int Key)
{
	if (_islock)
		return;

	if (_currentState == DIE
		|| _currentState == APPEAR
		|| _currentState == WIN
		|| _currentState == BLEED)
		return;

	if (Key == VK_JUMP && _allowJump)
	{
		_allowJump = false;
		switch (_currentState)
		{
		case STAND: case RUN: case DASH:
		{
			SetState(new JumpState(_playerData));
			break;
		}
		case SLIP_DOWN:
		{

			_pAniEfectDash->SetReverse(!_isReverse);
			if (_isReverse)
				_pAniEfectDash->SetPosition(_posX, _posY + 12);
			else
				_pAniEfectDash->SetPosition(_posX, _posY + 12);

			_pAniEfectDash->SetAnimation(1, 1, 0.005, false);
			if (keys[VK_SLIDE])
				SetState(new ClingState(_playerData, true));
			else
				SetState(new ClingState(_playerData));
			break;
		}
		default: break;
		}
	}

	if (Key == VK_SHOOT && _allowShoot)
	{
		if (_currentState == BLEED)
			return;

		if (!_isShoot)
		{
			_isShoot = true;
			_pAnimation->SetShoot(_isShoot);

		}
		PlayerShoot(PlayerBullet::BULLET_TYPE_NORMAL);
		Sound::GetInstance()->Play("ShootingBullet", false, 1);

		_allowShoot = false;
		_timeCurrentShoot = 0.0f;
	}

	if (Key == VK_SLIDE && _allowDash)
	{
		_allowDash = false;

		switch (_currentState)
		{
		case STAND: case RUN:
			_pAniEfectDash->SetReverse(_isReverse);
			_pAniEfectDash->SetPosition(_posX, _posY + 12);
			_pAniEfectDash->SetAnimation(0, 11, 0.05, false);
			SetState(new DashState(_playerData));
			break;
		default: break;
		}
	}
}

void Player::OnKeyUp(int Key)
{
	if (_islock)
		return;

	switch (Key)
	{
	case VK_JUMP:
	{
		if (_currentState == JUMP || _currentState == CLING)
			_vy = 0;
		_allowJump = true;
		break;
	}
	case VK_SHOOT:
	{
		_allowShoot = true;
		_pAniEfectCharge->SetPause(true);

		if (_currentState == BLEED)
			return;

		if (_timeChangeShoot > _timeShoot * 4)
		{
			_isShoot = true;
			_pAnimation->SetShoot(_isShoot);
			//The second level
			PlayerShoot(PlayerBullet::BULLET_TYPE_SECOND_LEVEL);
			Sound::GetInstance()->Stop("AbsorbLongEnergy");
			Sound::GetInstance()->Play("GiveUpLongEnergy", false, 1);
		}
		else
		{
			if (_timeChangeShoot > _timeShoot * 2)
			{
				_isShoot = true;
				_pAnimation->SetShoot(_isShoot);
				//The first level
				PlayerShoot(PlayerBullet::BULLET_TYPE_FIRST_LEVEL);
				Sound::GetInstance()->Stop("AbsorbShortEnergy");
				Sound::GetInstance()->Play("GiveUpShortEnergy", false, 1);
			}
		}

		_timeChangeShoot = 0.0f;

		break;
	}
	case VK_SLIDE:
	{
		if (_currentState == DASH)
			SetState(new StandState(_playerData));
		_allowDash = true;
		break;
	}
	default:break;
	}
}

RECT Player::GetBound()
{
	RECT bound;
	bound.left = _posX - 13;
	bound.right = _posX + 13;
	bound.top = _posY - 15;
	bound.bottom = _posY + 49 / 2.0f;

	return bound;
}

void Player::Update(float dt)
{
	OnNoCollisionWithBottom();

	for (auto& bullet : _listBullet)
		bullet->Update(dt);

	if (_isShoot)
	{
		_timeCurrentShoot += dt;
		if (_timeCurrentShoot > _timeShoot)
		{
			_isShoot = false;
			_pAnimation->SetShoot(_isShoot);
			_timeCurrentShoot = 0;
		}
	}

	//Animation Charge Bullet
	if (!_allowShoot)
	{
		_timeChangeShoot += dt;

		if (_timeChangeShoot > _timeShoot * 4)
		{
			Sound::GetInstance()->Stop("AbsorbShortEnergy");
			Sound::GetInstance()->Play("AbsorbLongEnergy", true, 0);
			_pAniEfectCharge->SetPause(false);
			if (_pAniEfectCharge->GetCurrentRow() != 1)
				_pAniEfectCharge->SetAnimation(1, 12, 0.017);
		}
		else if (_timeChangeShoot > _timeShoot * 2)
		{
			Sound::GetInstance()->Play("AbsorbShortEnergy", true, 0);
			_pAniEfectCharge->SetPause(false);
			if (_pAniEfectCharge->GetCurrentRow() != 0)
				_pAniEfectCharge->SetAnimation(0, 12, 0.02);
		}
	}


	// Time is alive
	if (_alive)
	{
		_timeAlive += dt;
		if (_timeAlive > 1.5f)
		{
			_alive = false;
			_isAllowDraw = true;
			_timeAlive = 0.0f;
		}
		else
		{
			// 0.1 time twinkle
			int TimePause = _timeAlive / 0.05f;
			if (TimePause % 2 == 0)
				_isAllowDraw = true;
			else if (TimePause % 2 == 1)
				_isAllowDraw = false;
		}
	}

	if (_posY - _posSlideDown > 8)
		_pAniEfectSlide->SetPause(false);
	else
		_pAniEfectSlide->SetPause(true);

	BaseObject::Update(dt);
	_pAnimation->Update(dt);
	_pAniEfectCharge->Update(dt);
	_pAniEfectDash->Update(dt);
	_pAniEfectSlide->Update(dt);

	if (_playerData->state)
		_playerData->state->Update(dt);
}

void Player::DrawHP()
{
	_hpbar->draw(_HP, _MaxHP);
}

void Player::Draw(Camera* camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter,
	D3DCOLOR color)
{
	for (auto& bullet : _listBullet)
		bullet->Draw(camera);

	if (!_isAllowDraw)
		return;

	_pAnimation->SetReverse(_isReverse);
	_pAnimation->SetPosition(GetPosition());

	if (camera)
	{
		_pAnimation->Draw(_pAnimation->GetPosition(), rect, scale, camera->GetTrans(), angle, rotationCenter, color);
		if (!_pAniEfectCharge->GetPause())
		{
			_pAniEfectCharge->SetReverse(_isReverse);
			_pAniEfectCharge->SetPosition(_posX, _posY + 6);
			_pAniEfectCharge->Draw(_pAniEfectCharge->GetPosition(), rect, scale, camera->GetTrans(), angle, rotationCenter, color);
		}

		if (!_pAniEfectDash->GetPause())
			_pAniEfectDash->Draw(_pAniEfectDash->GetPosition(), rect, scale, camera->GetTrans(), angle, rotationCenter, color);

		if (!_pAniEfectSlide->GetPause())
		{
			_pAniEfectSlide->SetReverse(_isReverse);
			if (_isReverse)
				_pAniEfectSlide->SetPosition(_posX - 15, _posY);
			else
				_pAniEfectSlide->SetPosition(_posX + 15, _posY);

			_pAniEfectSlide->Draw(_pAniEfectSlide->GetPosition(), rect, scale, camera->GetTrans(), angle, rotationCenter, color);
		}
	}
	else
		_pAnimation->Draw(_pAnimation->GetPosition());
}

void Player::OnCollision(eSideCollision side)
{
	if (_sideX != NONE)
	{
		if (_entityX->GetObjectType() == PORT)
		{
			if (_entityX->GetHP() <= 0)
			{
				_sideX = BaseObject::NONE;
				_collisionTimeMinX = 1.0f;
				return;
			}
		}
	}
	if (_playerData->state)
		_playerData->state->OnCollision(side);
}

void Player::OnNoCollisionWithBottom()
{
	if (_sideY != BOTTOM)
	{
		switch (_currentState)
		{
		case STAND:case RUN:case DASH:
			SetState(new FallState(_playerData));
			break;
		default:break;
		}
	}
}

void Player::OnCollision(BaseObject* object)
{
	switch (object->GetObjectType())
	{
	case BaseObject::ENEMY:
	case BaseObject::ENEMY_BULLET:
	case BaseObject::BOSS:
	{
		if (_alive)
			return;

		//HP -= object->getDamage();
		_alive = true;
		if (_HP <= 0)
		{
			SetState(new DieState(_playerData));
			_alive = false;
			_isDie = true;
			return;
		}

		_pAnimation->SetShoot(false);

		if (_posX < object->GetPosition().x)
			SetState(new BleedState(_playerData, 1));
		else
			SetState(new BleedState(_playerData, -1));
		break;
	}

	case BaseObject::ELEVATOR:
	{
		if (_currentState == JUMP || _currentState == CLING)
			break;
		_posY = object->GetBound().top - 24.51f;
		_sideY = BOTTOM;
		break;
	}

	case BaseObject::PORT:
	{
		if (object->GetHP() <= 0 && GetBound().top > object->GetBound().top)
		{
			_islock = true;
			if (object->GetDamage() > 0)
			{
				// Player standing
				_pAnimation->SetPause(false);
			}
			else
			{
				// Player moving
				_pAnimation->SetPause(true);
			}
		}

		break;
	}

	case BaseObject::THORN:
	{
		_HP = 0;
		_isDie = true;
		SetState(new DieState(_playerData));
		_alive = false;
		break;
	}

	case BaseObject::TAG_NONE:
		break;
	default:
		break;
	}
}

void Player::PlayerShoot(PlayerBullet::eBulletType bulletType)
{
	PlayerBullet* playerBullet = NULL;

	if (_listBullet.size() < 3)
	{
		playerBullet = new PlayerBullet();
		_listBullet.push_back(playerBullet);
	}
	else
	{
		for (auto& bullet : _listBullet)
			if (bullet->GetExplosion())
			{
				playerBullet = bullet;
				break;
			}
		if (playerBullet == NULL)
			return;
	}

	bool isReverseBullet = _isReverse;
	float posX = 0;
	float posY = this->GetBound().bottom - 18;

	if (_currentState == SLIP_DOWN)
	{
		isReverseBullet = !_isReverse;
		if (!_isReverse)
			posX = this->GetBound().left + playerBullet->GetWidth() / 4.0f;
		else
			posX = this->GetBound().right - playerBullet->GetWidth() / 4.0f;
	}
	else
	{
		if (!_isReverse)
			posX = this->GetBound().right - playerBullet->GetWidth() / 4.0f;
		else
			posX = this->GetBound().left + playerBullet->GetWidth() / 4.0f;
	}

	playerBullet->NewBullet(posX, posY, isReverseBullet, bulletType);
}