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

Player::Player()
{
	this->setId(0);
	_objectType = eOject_RockMan;
	_pAnimation = new Animation(Define::ANIMATION_ROCKMAN, 21, 10, 49, 49, 0.15f, D3DCOLOR_XRGB(100, 100, 100));
	_pAniEffectCharge = new Animation(Define::ANIMATION_CHARGE, 2, 12, 55, 65, 0.02f);
	_pAniEffectDash = new Animation(Define::ANIMATION_DASH, 1, 11, 75, 35, 0.15f);
	_pAniEffectSlide = new Animation(Define::ANIMATION_SLIDE, 1, 2, 30, 30, 0.15f);
	_pHPBar = new HPBar(_objectType);

	_pAniEffectCharge->setPause(true);
	_pAniEffectDash->setPause(true);
	_pAniEffectSlide->setAnimation(0, 2, 0.1f);
	_pAniEffectSlide->setPause(true);

	_allowJump = true;
	_allowShoot = true;
	_allowDash = true;
	_isReverse = false;

	_isShoot = false;
	_alive = false;
	_isLock = false;

	_timeShoot = 0.3f;
	_timeCurrentShoot = 0.0f;
	_timeChangeShoot = 0.0f;
	_timeAlive = 0.0f;

	_vx = 0.0f;
	_vy = 0.0f;
	_MaxHP = 15;
	_HP = _MaxHP;
	_Damage = 0;

	setState(new AppearState(this));
}

Player::~Player()
{
	delete _pHPBar;
	delete _pAnimation;
	delete m_pState;
	for (auto& bullet : _listPlayerBullet)
		delete bullet;
	if (!_listPlayerBullet.empty())
		_listPlayerBullet.clear();
}

void Player::changeAnimation(Player_State state)
{
	switch (state)
	{
		case ePlayer_Appear:
			_pAnimation->setAnimation(0, 5, 0.15f, false);
			break;

		case ePlayer_Stand:
			_pAnimation->setAnimation(1, 4, 0.1f, false);
			break;

		case ePlayer_Run:
			_pAnimation->setAnimation(3, 10, 0.05f);
			break;

		case ePlayer_Jump:
			_pAnimation->setAnimation(5, 3, 0.05f, false);
			break;

		case ePlayer_Fall:
			_pAnimation->setAnimation(7, 3, 0.05f, false);
			break;

		case ePlayer_Cling:
			_pAnimation->setAnimation(9, 4, 0.03f, false);
			break;

		case ePlayer_SlipDown:
			_pAnimation->setAnimation(11, 3, 0.05f, false);
			break;

		case ePlayer_Dash:
			_pAnimation->setAnimation(16, 2, 0.05f, false);
			break;

		case ePlayer_Climb:
			break;

		case ePlayer_Bleed:
			_pAnimation->setAnimation(18, 9, 0.05f);
			break;

		case ePlayer_Death:
			_pAnimation->setAnimation(20, 3, 0.3f);
			break;

		case ePlayer_Win: break;

		default: break;
	}

	setWidth(_pAnimation->getWidth());
	setHeight(_pAnimation->getHeight());
}

void Player::setState(PlayerState* new_state)
{
	if (_currentState == new_state->getState())
		return;

	delete m_pState;
	m_pState = new_state;
	_currentState = new_state->getState();
	changeAnimation(new_state->getState());

	if (_currentState != ePlayer_Dash && _currentState != ePlayer_Cling)
		_pAniEffectDash->setPause(true);

	if (_currentState == ePlayer_SlipDown)
		_posSlideDown = _posY;
	else
		_posSlideDown = std::numeric_limits<float>::infinity();
}



#pragma region GETTER, SETTER

Animation* Player::getAnimation()
{
	return _pAnimation;
}

int Player::getHP() const
{
	return this->_HP;
}

void Player::setHP(int hp)
{
	this->_HP = hp;
}

void Player::addHP(int hp)
{
	this->_HP += hp;
}

std::vector<PlayerBullet*>* Player::getPlayerBullet()
{
	return &_listPlayerBullet;
}

PlayerState* Player::getPlayerState()
{
	return m_pState;
}

void Player::setLock(bool lock)
{
	_isLock = lock;
}

Player_State Player::getCurrentState() const
{
	return _currentState;
}

#pragma endregion


void Player::KeyBoardEventHandler(const std::map<int, bool>& keys, float dt)
{
	if (!_isLock)
	{
		if (m_pState)
			m_pState->KeyBoardEventHandler(keys, dt);
	}
	_isLock = false;
}

void Player::OnKeyDown(std::map<int, bool> keys, int Key)
{
	if (_isLock)
		return;

	if (_currentState == ePlayer_Death
		|| _currentState == ePlayer_Appear
		|| _currentState == ePlayer_Win
		|| _currentState == ePlayer_Bleed)
		return;

	if (Key == VK_JUMP && _allowJump)
	{
		_allowJump = false;
		switch (_currentState)
		{
			case ePlayer_Stand: case ePlayer_Run: case ePlayer_Dash:
			{
				setState(new JumpState(this));
				break;
			}
			case ePlayer_SlipDown:
			{
				_pAniEffectDash->setReverse(!_isReverse);
				if (_isReverse)
					_pAniEffectDash->setPosition(_posX, _posY + 12);
				else
					_pAniEffectDash->setPosition(_posX, _posY + 12);

				_pAniEffectDash->setAnimation(1, 1, 0.005f, false);
				if (keys[VK_SLIDE])
					setState(new ClingState(this, true));
				else
					setState(new ClingState(this));
				break;
			}
			default:
				break;
		}
	}

	if (Key == VK_SHOOT && _allowShoot)
	{
		if (_currentState == ePlayer_Bleed)
			return;

		if (!_isShoot)
		{
			_isShoot = true;
			_pAnimation->setShoot(_isShoot);

		}

		playerShoot(ePlayerBullet_Type_Normal);
		Sound::getInstance()->play("ShootingBullet", false, 1);

		_allowShoot = false;
		_timeCurrentShoot = 0.0f;
	}

	if (Key == VK_SLIDE && _allowDash)
	{
		_allowDash = false;

		switch (_currentState)
		{
			case ePlayer_Stand: case ePlayer_Run:
			{
				_pAniEffectDash->setReverse(_isReverse);
				_pAniEffectDash->setPosition(_posX, _posY + 12);
				_pAniEffectDash->setAnimation(0, 11, 0.05f, false);
				setState(new DashState(this));
				break;
			}
			default:
				break;
		}
	}
}

void Player::OnKeyUp(int Key)
{
	if (_isLock)
		return;

	switch (Key)
	{
		case VK_JUMP:
		{
			if (_currentState == ePlayer_Jump || _currentState == ePlayer_Cling)
				_vy = 0;
			_allowJump = true;
			break;
		}
		case VK_SHOOT:
		{
			_allowShoot = true;
			_pAniEffectCharge->setPause(true);

			if (_currentState == ePlayer_Bleed)
				return;

			if (_timeChangeShoot > _timeShoot * 4)
			{
				_isShoot = true;
				_pAnimation->setShoot(_isShoot);

				// The second level
				playerShoot(ePlayerBullet_Type_Second_Level);

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
					playerShoot(ePlayerBullet_Type_First_Level);

					Sound::getInstance()->stop("AbsorbShortEnergy");
					Sound::getInstance()->play("GiveUpShortEnergy", false, 1);
				}
			}

			_timeChangeShoot = 0.0f;

			break;
		}
		case VK_SLIDE:
		{
			if (_currentState == ePlayer_Dash)
				setState(new StandState(this));

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

	for (auto& bullet : _listPlayerBullet)
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
			_pAniEffectCharge->setPause(false);
			if (_pAniEffectCharge->getCurrentRow() != 1)
				_pAniEffectCharge->setAnimation(1, 12, 0.017f);
		}
		else if (_timeChangeShoot > _timeShoot * 2)
		{
			Sound::getInstance()->play("AbsorbShortEnergy", true, 0);
			_pAniEffectCharge->setPause(false);
			if (_pAniEffectCharge->getCurrentRow() != 0)
				_pAniEffectCharge->setAnimation(0, 12, 0.02f);
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
		_pAniEffectSlide->setPause(false);
	else
		_pAniEffectSlide->setPause(true);

	BaseObject::update(dt);
	_pAnimation->update(dt);
	_pAniEffectCharge->update(dt);
	_pAniEffectDash->update(dt);
	_pAniEffectSlide->update(dt);

	if (m_pState)
		m_pState->update(dt);
}

void Player::drawHP()
{
	_pHPBar->draw(_HP, _MaxHP);
}

void Player::draw(Camera* camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter,
	D3DCOLOR color)
{
	for (auto& bullet : _listPlayerBullet)
		bullet->draw(camera);

	if (_isAllowDraw)
	{
		_pAnimation->setReverse(_isReverse);
		_pAnimation->setPosition(getPosition());

		if (camera)
		{
			_pAnimation->draw(_pAnimation->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
			if (!_pAniEffectCharge->getPause())
			{
				_pAniEffectCharge->setReverse(_isReverse);
				_pAniEffectCharge->setPosition(_posX, _posY + 6);
				_pAniEffectCharge->draw(_pAniEffectCharge->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
			}

			if (!_pAniEffectDash->getPause())
				_pAniEffectDash->draw(_pAniEffectDash->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);

			if (!_pAniEffectSlide->getPause())
			{
				_pAniEffectSlide->setReverse(_isReverse);
				if (_isReverse)
					_pAniEffectSlide->setPosition(_posX - 15, _posY);
				else
					_pAniEffectSlide->setPosition(_posX + 15, _posY);

				_pAniEffectSlide->draw(_pAniEffectSlide->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
			}
		}
		else
			_pAnimation->draw(_pAnimation->getPosition());
	}
}

void Player::onCollision(Side_Collision side)
{
	if (_side_x != eSide_None)
	{
		if (_entity_x->getObjectType() == eObject_Port)
		{
			if (_entity_x->getHP() <= 0)
			{
				_side_x = eSide_None;
				_collision_time_min_x = 1.0f;
				return;
			}
		}
	}

	if (m_pState)
		m_pState->onCollision(side);
}

void Player::onNoCollisionWithBottom()
{
	if (_side_y != eSide_Bottom)
	{
		switch (_currentState)
		{
			case ePlayer_Stand: case ePlayer_Run: case ePlayer_Dash:
			{
				setState(new FallState(this));
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
		case eObject_Enemy:
		case eObject_Enemy_Bullet:
		case eObject_Boss:
		{
			if (_alive)
				return;

			//HP -= object->getDamage();
			_alive = true;
			if (_HP <= 0)
			{
				setState(new DieState(this));
				_alive = false;
				_isDie = true;
				return;
			}

			_pAnimation->setShoot(false);

			if (_posX < object->getPosition().x)
				setState(new BleedState(this, 1));
			else
				setState(new BleedState(this, -1));
			break;
		}

		case eObject_Elevator:
		{
			if (_currentState == ePlayer_Jump || _currentState == ePlayer_Cling)
				break;
			_posY = object->getBound().top - 24.51f;
			_side_y = eSide_Bottom;
			break;
		}

		case eObject_Port:
		{
			if (object->getHP() <= 0 && getBound().top > object->getBound().top)
			{
				_isLock = true;
				if (object->getDamage() > 0)
					_pAnimation->setPause(false);
				else
					_pAnimation->setPause(true);
			}

			break;
		}

		case eObject_Thorn:
		{
			_HP = 0;
			_isDie = true;
			setState(new DieState(this));
			_alive = false;
			break;
		}

		default:
			break;
	}
}

void Player::playerShoot(PlayerBullet_Type bulletType)
{
	PlayerBullet* playerBullet = nullptr;

	if (_listPlayerBullet.size() < 3)
	{
		playerBullet = new PlayerBullet();
		_listPlayerBullet.push_back(playerBullet);
	}
	else
	{
		for (auto& bullet : _listPlayerBullet)
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

	if (_currentState == ePlayer_SlipDown)
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