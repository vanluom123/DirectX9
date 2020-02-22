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

Player * Player::s_instance = nullptr;

Player::Player()
{
	this->setId(0);
	_objectType = Enumerator::Object_Type::ROCKMAN;
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

	_velocity.x = 0.0f;
	_velocity.y = 0.0f;
	_MaxHP = 15;
	_HP = _MaxHP;
	_Damage = 0;

	this->setState(new AppearState());

}

Player::~Player()
{
	delete _pAniEffectCharge;
	delete _pAniEffectDash;
	delete _pAniEffectSlide;

	delete _pHPBar;
	delete _pAnimation;
	delete m_pState;

	for (auto bullet : _listPlayerBullet)
		delete bullet;

	if (!_listPlayerBullet.empty())
		_listPlayerBullet.clear();
}

Player * Player::getInstance()
{
	if (!s_instance) s_instance = new Player;
	return s_instance;
}

void Player::release()
{
	delete s_instance;
	s_instance = nullptr;
}

void Player::changeAnimation(Player_State state)
{
	switch (state)
	{
		case Enumerator::Player_State::APPEAR:
			_pAnimation->setAnimation(0, 5, 0.15f, false);
			break;

		case Enumerator::Player_State::STAND:
			_pAnimation->setAnimation(1, 4, 0.1f, false);
			break;

		case Enumerator::Player_State::RUN:
			_pAnimation->setAnimation(3, 10, 0.05f);
			break;

		case Enumerator::Player_State::JUMP:
			_pAnimation->setAnimation(5, 3, 0.05f, false);
			break;

		case Enumerator::Player_State::FALL:
			_pAnimation->setAnimation(7, 3, 0.05f, false);
			break;

		case Enumerator::Player_State::CLING:
			_pAnimation->setAnimation(9, 4, 0.03f, false);
			break;

		case Enumerator::Player_State::SLIP_DOWN:
			_pAnimation->setAnimation(11, 3, 0.05f, false);
			break;

		case Enumerator::Player_State::DASH:
			_pAnimation->setAnimation(16, 2, 0.05f, false);
			break;

		case Enumerator::Player_State::CLIMB:
			break;

		case Enumerator::Player_State::BLEED:
			_pAnimation->setAnimation(18, 9, 0.05f);
			break;

		case Enumerator::Player_State::DEATH:
			_pAnimation->setAnimation(20, 3, 0.3f);
			break;

		case Enumerator::Player_State::WIN:
		default: break;
	}

	setWidth(_pAnimation->getWidth());
	setHeight(_pAnimation->getHeight());
}

void Player::setState(PlayerState * new_state)
{
	if (_currentState == new_state->getState())
		return;

	delete m_pState;
	m_pState = new_state;
	_currentState = new_state->getState();
	this->changeAnimation(new_state->getState());

	if (_currentState != Enumerator::Player_State::DASH && _currentState != Enumerator::Player_State::CLING)
		_pAniEffectDash->setPause(true);

	if (_currentState == Enumerator::Player_State::SLIP_DOWN)
		_posSlideDown = _position.y;
	else
		_posSlideDown = std::numeric_limits<float>::infinity();
}



#pragma region GETTER, SETTER

Animation * Player::getAnimation()
{
	return _pAnimation;
}

int Player::getHP() const
{
	return _HP;
}

void Player::setHP(int hp)
{
	_HP = hp;
}

void Player::addHP(int hp)
{
	_HP += hp;
}

vector<PlayerBullet *> Player::getPlayerBullet() const
{
	return _listPlayerBullet;
}

PlayerState * Player::getPlayerState()
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


void Player::KeyBoardEventHandler(const std::map<int, bool> & keys, float dt)
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

	if (_currentState == Enumerator::Player_State::DEATH
		|| _currentState == Enumerator::Player_State::APPEAR
		|| _currentState == Enumerator::Player_State::WIN
		|| _currentState == Enumerator::Player_State::BLEED)
		return;

	if (Key == VK_JUMP && _allowJump)
	{
		_allowJump = false;
		switch (_currentState)
		{
			case Enumerator::Player_State::STAND:
			case Enumerator::Player_State::RUN:
			case Enumerator::Player_State::DASH:
			{
				setState(new JumpState());
				break;
			}
			case Enumerator::Player_State::SLIP_DOWN:
			{
				_pAniEffectDash->setReverse(!_isReverse);
				if (_isReverse)
					_pAniEffectDash->setPosition(_position.x, _position.y + 12);
				else
					_pAniEffectDash->setPosition(_position.x, _position.y + 12);

				_pAniEffectDash->setAnimation(1, 1, 0.005f, false);

				if (keys[VK_SLIDE])
					setState(new ClingState(true));
				else
					setState(new ClingState());
				break;
			}
			default:
				break;
		}
	}

	if (Key == VK_SHOOT && _allowShoot)
	{
		if (_currentState == Enumerator::Player_State::BLEED)
			return;

		if (!_isShoot)
		{
			_isShoot = true;
			_pAnimation->setShoot(_isShoot);
		}

		playerShoot(Enumerator::PlayerBullet_Type::BULLET_NORMAL);
		Sound::getInstance()->play("ShootingBullet", false, 1);

		_allowShoot = false;
		_timeCurrentShoot = 0.0f;
	}

	if (Key == VK_SLIDE && _allowDash)
	{
		_allowDash = false;

		switch (_currentState)
		{
			case Enumerator::Player_State::STAND:
			case Enumerator::Player_State::RUN:
			{
				_pAniEffectDash->setReverse(_isReverse);
				_pAniEffectDash->setPosition(_position.x, _position.y + 12);
				_pAniEffectDash->setAnimation(0, 11, 0.05f, false);
				setState(new DashState());
				break;
			}
			default: break;
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
			if (_currentState == Enumerator::Player_State::JUMP || _currentState == Enumerator::Player_State::CLING)
				_velocity.y = 0.0f;
			_allowJump = true;
			break;
		}
		case VK_SHOOT:
		{
			_allowShoot = true;
			_pAniEffectCharge->setPause(true);

			if (_currentState == Enumerator::Player_State::BLEED)
				return;

			if (_timeChangeShoot > _timeShoot * 4)
			{
				_isShoot = true;
				_pAnimation->setShoot(_isShoot);

				// The second level
				this->playerShoot(Enumerator::PlayerBullet_Type::BULLET_SECOND_LEVEL);

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
					this->playerShoot(Enumerator::PlayerBullet_Type::BULLET_FIRST_LEVEL);

					Sound::getInstance()->stop("AbsorbShortEnergy");
					Sound::getInstance()->play("GiveUpShortEnergy", false, 1);
				}
			}

			_timeChangeShoot = 0.0f;

			break;
		}
		case VK_SLIDE:
		{
			if (_currentState == Enumerator::Player_State::DASH)
				setState(new StandState());

			_allowDash = true;
			break;
		}
		default: break;
	}
}

RECT Player::getBound()
{
	RECT bound;
	bound.left = _position.x - 13;
	bound.right = _position.x + 13;
	bound.top = _position.y - 15;
	bound.bottom = _position.y + 49 / 2.0f;
	return bound;
}

void Player::update(float dt)
{
	this->onNoCollisionWithBottom();

	for (auto bullet : _listPlayerBullet)
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

	if (_position.y - _posSlideDown > 8)
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

void Player::draw(Camera * camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter, D3DCOLOR color)
{
	for (auto bullet : _listPlayerBullet)
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
				_pAniEffectCharge->setPosition(_position.x, _position.y + 6);
				_pAniEffectCharge->draw(_pAniEffectCharge->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
			}

			if (!_pAniEffectDash->getPause())
				_pAniEffectDash->draw(_pAniEffectDash->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);

			if (!_pAniEffectSlide->getPause())
			{
				_pAniEffectSlide->setReverse(_isReverse);
				if (_isReverse)
					_pAniEffectSlide->setPosition(_position.x - 15, _position.y);
				else
					_pAniEffectSlide->setPosition(_position.x + 15, _position.y);

				_pAniEffectSlide->draw(_pAniEffectSlide->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
			}
		}
		else
			_pAnimation->draw(_pAnimation->getPosition());
	}
}

void Player::onCollision(Side_Collision side)
{
	if (_side_x != Enumerator::Side_Collision::NONE)
	{
		if (_entity_x->getObjectType() == Enumerator::Object_Type::PORT)
		{
			if (_entity_x->getHP() <= 0)
			{
				_side_x = Enumerator::Side_Collision::NONE;
				_colTimeMinX = 1.0f;
				return;
			}
		}
	}

	if (m_pState)
		m_pState->onCollision(side);
}

void Player::onNoCollisionWithBottom()
{
	if (_side_y != Enumerator::Side_Collision::BOTTOM)
	{
		switch (_currentState)
		{
			case Enumerator::Player_State::STAND:
			case Enumerator::Player_State::RUN:
			case Enumerator::Player_State::DASH:
			{
				setState(new FallState());
				break;
			}
			default:
				break;
		}
	}
}

void Player::onCollision(BaseObject * object)
{
	switch (object->getObjectType())
	{
		case Enumerator::Object_Type::ENEMY:
		case Enumerator::Object_Type::ENEMY_BULLET:
		case Enumerator::Object_Type::BOSS:
		{
			if (_alive)
				return;

			//HP -= object->getDamage();
			_alive = true;
			if (_HP <= 0)
			{
				setState(new DieState());
				_alive = false;
				_isDestroy = true;
				return;
			}

			_pAnimation->setShoot(false);

			if (_position.x < object->getPosition().x)
				setState(new BleedState(1));
			else
				setState(new BleedState(-1));
			break;
		}

		case Enumerator::Object_Type::ELEVATOR:
		{
			if (_currentState == Enumerator::Player_State::JUMP || _currentState == Enumerator::Player_State::CLING)
				break;
			_position.y = object->getBound().top - 24.51f;
			_side_y = Enumerator::Side_Collision::BOTTOM;

			break;
		}

		case Enumerator::Object_Type::PORT:
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

		case Enumerator::Object_Type::THORN:
		{
			_HP = 0;
			_isDestroy = true;
			this->setState(new DieState());
			_alive = false;
			break;
		}

		default: break;
	}
}

void Player::playerShoot(PlayerBullet_Type bulletType)
{
	PlayerBullet * playerBullet = nullptr;

	if (_listPlayerBullet.size() < 3)
	{
		playerBullet = new PlayerBullet();
		_listPlayerBullet.push_back(playerBullet);
	}
	else
	{
		for (auto bullet : _listPlayerBullet)
		{
			if (bullet->getExplosion() == true)
			{
				playerBullet = bullet;
				break;
			}
		}
		if (playerBullet == nullptr)
			return;
	}

	bool isReverseBullet = _isReverse;
	float posX;
	float posY = getBound().bottom - 18;

	if (_currentState == Enumerator::Player_State::SLIP_DOWN)
	{
		isReverseBullet = !_isReverse;
		if (_isReverse == false)
			posX = getBound().left + playerBullet->getWidth() / 4.0f;
		else
			posX = getBound().right - playerBullet->getWidth() / 4.0f;
	}
	else
	{
		if (_isReverse == false)
			posX = getBound().right - playerBullet->getWidth() / 4.0f;
		else
			posX = getBound().left + playerBullet->getWidth() / 4.0f;
	}

	playerBullet->newBullet(posX, posY, isReverseBullet, bulletType);
}