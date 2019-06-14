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
	setId(0);
	_pAnimation = new Animation(Define::ANIMATION_ROCKMAN, 21, 10, 49, 49, 0.15f, D3DCOLOR_XRGB(100, 100, 100));
	_pAniEfectCharge = new Animation(Define::ANIMATION_CHARGE, 2, 12, 55, 65, 0.02f);
	_pAniEfectDash = new Animation(Define::ANIMATION_DASH, 1, 11, 75, 35, 0.15f);
	_pAniEfectSlide = new Animation(Define::ANIMATION_SLIDE, 1, 2, 30, 30, 0.15f);
	_hpbar = new HPBar(_objectType);

	_pAniEfectCharge->setPause(true);
	_pAniEfectDash->setPause(true);
	_pAniEfectSlide->setAnimation(0, 2, 0.1f);
	_pAniEfectSlide->setPause(true);

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

	_vx = 0.0f;
	_vy = 0.0f;
	_MaxHP = 15;
	_HP = _MaxHP;
	_Damage = 0;

	_currentState = FALL;

	_playerData = new PlayerData;
	_playerData->player = this;
	_playerData->state = nullptr;

	setState(new AppearState(_playerData));
}

Player::~Player()
{
	delete _hpbar;
	delete _pAnimation;
	delete _playerData;

	for (auto& bullet : _listBullet)
		delete bullet;

	if (!_listBullet.empty())
		_listBullet.clear();
}

void Player::changeAnimation(ePlayerState state)
{
	switch (state)
	{
	case APPEAR:
		_pAnimation->setAnimation(0, 5, 0.15f, false);
		break;

	case STAND:
		_pAnimation->setAnimation(1, 4, 0.1f, false);
		break;

	case RUN:
		_pAnimation->setAnimation(3, 10, 0.05f);
		break;

	case JUMP:
		_pAnimation->setAnimation(5, 3, 0.05f, false);
		break;

	case FALL:
		_pAnimation->setAnimation(7, 3, 0.05f, false);
		break;

	case CLING:
		_pAnimation->setAnimation(9, 4, 0.03f, false);
		break;

	case SLIP_DOWN:
		_pAnimation->setAnimation(11, 3, 0.05f, false);
		break;

	case DASH:
		_pAnimation->setAnimation(16, 2, 0.05f, false);
		break;

	case CLIMB:
		break;

	case BLEED:
		_pAnimation->setAnimation(18, 9, 0.05f);
		break;

	case DIE:
		_pAnimation->setAnimation(20, 3, 0.3f);
		break;

	case WIN: break;

	default: break;
	}

	setWidth(_pAnimation->getWidth());
	setHeight(_pAnimation->getHeight());
}

void Player::setState(PlayerState* newState)
{
	if (_currentState != newState->getState())
	{
		SAFE_DELETE(_playerData->state);
		_playerData->state = newState;

		changeAnimation(newState->getState());
		_currentState = newState->getState();

		if (_currentState != DASH && _currentState != CLING)
			_pAniEfectDash->setPause(true);

		if (_currentState == SLIP_DOWN)
			_posSlideDown = _posY;

		else
			_posSlideDown = std::numeric_limits<float>::infinity();
	}
}



#pragma region GETTER, SETTER

Animation* Player::getAnimation() const
{
	return _pAnimation;
}

float Player::getHP() const
{
	return this->_HP;
}

void Player::setHP(float hp)
{
	this->_HP = hp;
}

void Player::addHP(float hp)
{
	this->_HP += hp;
}

std::vector<PlayerBullet*>* Player::getPlayerBullet()
{
	return &_listBullet;
}

void Player::setLock(bool lock)
{
	_islock = lock;
}

PlayerData* Player::getPlayerData() const
{
	return _playerData;
}

Player::ePlayerState Player::getCurrentState() const
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
			setState(new JumpState(_playerData));
			break;
		}
		case SLIP_DOWN:
		{
			_pAniEfectDash->setReverse(!_isReverse);
			if (_isReverse)
				_pAniEfectDash->setPosition(_posX, _posY + 12);
			else
				_pAniEfectDash->setPosition(_posX, _posY + 12);

			_pAniEfectDash->setAnimation(1, 1, 0.005f, false);
			if (keys[VK_SLIDE])
				setState(new ClingState(_playerData, true));
			else
				setState(new ClingState(_playerData));
			break;
		}
		default:
			break;
		}
	}

	if (Key == VK_SHOOT && _allowShoot)
	{
		if (_currentState == BLEED)
			return;

		if (!_isShoot)
		{
			_isShoot = true;
			_pAnimation->setShoot(_isShoot);

		}

		playerShoot(PlayerBullet::BULLET_TYPE_NORMAL);
		Sound::getInstance()->play("ShootingBullet", false, 1);

		_allowShoot = false;
		_timeCurrentShoot = 0.0f;
	}

	if (Key == VK_SLIDE && _allowDash)
	{
		_allowDash = false;

		switch (_currentState)
		{
		case STAND: case RUN:
		{
			_pAniEfectDash->setReverse(_isReverse);
			_pAniEfectDash->setPosition(_posX, _posY + 12);
			_pAniEfectDash->setAnimation(0, 11, 0.05f, false);
			setState(new DashState(_playerData));
			break;
		}
		default:
			break;
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
		_pAniEfectCharge->setPause(true);

		if (_currentState == BLEED)
			return;

		if (_timeChangeShoot > _timeShoot * 4)
		{
			_isShoot = true;
			_pAnimation->setShoot(_isShoot);

			// The second level
			playerShoot(PlayerBullet::BULLET_TYPE_SECOND_LEVEL);

			Sound::getInstance()->stop("AbsorbLongEnergy");
			Sound::getInstance()->play("GiveUpLongEnergy", false, 1);
		}
		else
		{
			if (_timeChangeShoot > _timeShoot * 2)
			{
				_isShoot = true;
				_pAnimation->setShoot(_isShoot);

				//The first level
				playerShoot(PlayerBullet::BULLET_TYPE_FIRST_LEVEL);

				Sound::getInstance()->stop("AbsorbShortEnergy");
				Sound::getInstance()->play("GiveUpShortEnergy", false, 1);
			}
		}

		_timeChangeShoot = 0.0f;

		break;
	}
	case VK_SLIDE:
	{
		if (_currentState == DASH)
			setState(new StandState(_playerData));

		_allowDash = true;
		break;
	}
	default:break;
	}
}

RECT Player::getBound()
{
	RECT bound;
	bound.left = _posX - 13;
	bound.right = _posX + 13;
	bound.top = _posY - 15;
	bound.bottom = _posY + 49 / 2.0f;

	return bound;
}

void Player::update(float dt)
{
	onNoCollisionWithBottom();

	for (auto& bullet : _listBullet)
		bullet->update(dt);

	if (_isShoot)
	{
		_timeCurrentShoot += dt;
		if (_timeCurrentShoot > _timeShoot)
		{
			_isShoot = false;
			_pAnimation->setShoot(_isShoot);
			_timeCurrentShoot = 0;
		}
	}

	// Animation Charge Bullet
	if (!_allowShoot)
	{
		_timeChangeShoot += dt;

		if (_timeChangeShoot > _timeShoot * 4)
		{
			Sound::getInstance()->stop("AbsorbShortEnergy");
			Sound::getInstance()->play("AbsorbLongEnergy", true, 0);
			_pAniEfectCharge->setPause(false);
			if (_pAniEfectCharge->getCurrentRow() != 1)
				_pAniEfectCharge->setAnimation(1, 12, 0.017f);
		}
		else if (_timeChangeShoot > _timeShoot * 2)
		{
			Sound::getInstance()->play("AbsorbShortEnergy", true, 0);
			_pAniEfectCharge->setPause(false);
			if (_pAniEfectCharge->getCurrentRow() != 0)
				_pAniEfectCharge->setAnimation(0, 12, 0.02f);
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
		_pAniEfectSlide->setPause(false);
	else
		_pAniEfectSlide->setPause(true);

	BaseObject::update(dt);
	_pAnimation->update(dt);
	_pAniEfectCharge->update(dt);
	_pAniEfectDash->update(dt);
	_pAniEfectSlide->update(dt);

	if (_playerData->state)
		_playerData->state->Update(dt);
}

void Player::DrawHP()
{
	_hpbar->draw(_HP, _MaxHP);
}

void Player::draw(Camera* camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter,
	D3DCOLOR color)
{
	for (auto& bullet : _listBullet)
		bullet->draw(camera);

	if (!_isAllowDraw)
		return;

	_pAnimation->setReverse(_isReverse);
	_pAnimation->setPosition(getPosition());

	if (camera)
	{
		_pAnimation->draw(_pAnimation->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
		if (!_pAniEfectCharge->getPause())
		{
			_pAniEfectCharge->setReverse(_isReverse);
			_pAniEfectCharge->setPosition(_posX, _posY + 6);
			_pAniEfectCharge->draw(_pAniEfectCharge->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
		}

		if (!_pAniEfectDash->getPause())
			_pAniEfectDash->draw(_pAniEfectDash->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);

		if (!_pAniEfectSlide->getPause())
		{
			_pAniEfectSlide->setReverse(_isReverse);
			if (_isReverse)
				_pAniEfectSlide->setPosition(_posX - 15, _posY);
			else
				_pAniEfectSlide->setPosition(_posX + 15, _posY);

			_pAniEfectSlide->draw(_pAniEfectSlide->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
		}
	}
	else
		_pAnimation->draw(_pAnimation->getPosition());
}

void Player::onCollision(eSideCollision side)
{
	if (_side_x != NONE)
	{
		if (_entity_x->getObjectType() == PORT)
		{
			if (_entity_x->getHP() <= 0)
			{
				_side_x = BaseObject::NONE;
				_collision_time_min_x = 1.0f;
				return;
			}
		}
	}
	if (_playerData->state)
		_playerData->state->onCollision(side);
}

void Player::onNoCollisionWithBottom()
{
	if (_side_y != BOTTOM)
	{
		switch (_currentState)
		{
		case STAND:case RUN:case DASH:
		{
			setState(new FallState(_playerData));
			break;
		}
		default:
			break;
		}
	}
}

void Player::onCollision(BaseObject* object)
{
	switch (object->getObjectType())
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
			setState(new DieState(_playerData));
			_alive = false;
			_isDie = true;
			return;
		}

		_pAnimation->setShoot(false);

		if (_posX < object->getPosition().x)
			setState(new BleedState(_playerData, 1));
		else
			setState(new BleedState(_playerData, -1));
		break;
	}

	case BaseObject::ELEVATOR:
	{
		if (_currentState == JUMP || _currentState == CLING)
			break;
		_posY = object->getBound().top - 24.51f;
		_side_y = BOTTOM;
		break;
	}

	case BaseObject::PORT:
	{
		if (object->getHP() <= 0 && getBound().top > object->getBound().top)
		{
			_islock = true;
			if (object->getDamage() > 0)
				_pAnimation->setPause(false);
			else
				_pAnimation->setPause(true);
		}

		break;
	}

	case BaseObject::THORN:
	{
		_HP = 0;
		_isDie = true;
		setState(new DieState(_playerData));
		_alive = false;
		break;
	}

	default:
		break;
	}
}

void Player::playerShoot(PlayerBullet::eBulletType bulletType)
{
	PlayerBullet* playerBullet = nullptr;

	if (_listBullet.size() < 3)
	{
		playerBullet = new PlayerBullet();
		_listBullet.push_back(playerBullet);
	}
	else
	{
		for (auto& bullet : _listBullet)
		{
			if (bullet->getExplosion())
			{
				playerBullet = bullet;
				break;
			}
		}
		if (playerBullet == nullptr)
			return;
	}

	bool isReverseBullet = _isReverse;
	float posX = 0.0f;
	float posY = this->getBound().bottom - 18;

	if (_currentState == SLIP_DOWN)
	{
		isReverseBullet = !_isReverse;
		if (!_isReverse)
			posX = this->getBound().left + playerBullet->getWidth() / 4.0f;
		else
			posX = this->getBound().right - playerBullet->getWidth() / 4.0f;
	}
	else
	{
		if (!_isReverse)
			posX = this->getBound().right - playerBullet->getWidth() / 4.0f;
		else
			posX = this->getBound().left + playerBullet->getWidth() / 4.0f;
	}

	playerBullet->newBullet(posX, posY, isReverseBullet, bulletType);
}