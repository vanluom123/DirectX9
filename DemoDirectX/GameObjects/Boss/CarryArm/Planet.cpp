#include "Planet.h"
#include "../../../GameComponents/GameCollision.h"
#include "../../Player/GameState/StandState/StandState.h"

Planet::Planet(Player* gp)
{
	_pPixton = new Pixton();
	_pAnim = new Animation("Resources/Enemies/CarryArm/x3_subboss_carryarm_01.png", 1, 1, 256, 88);
	_pAnimAttack = new Animation("Resources/Enemies/CarryArm/attack.png", 2, 10, 32, 32);
	_pAnimBullet = new Animation("Resources/Enemies/CarryArm/bullet.png", 1, 3, 16, 16);
	_pAnimAttack->setAnimation(0, 1);
	_pAnimAttack->setPause(1);
	_pAnimBullet->setAnimation(0, 3, 0.1);

	_HP = 1;
	_Damage = 3;
	_planetPosY = 0;
	_planetPosX = 0;
	_isMove = true;
	_pRockMan = gp;
	_pCarryArm = new CarryArm();
	_pBox1 = new Box();
	_pBox2 = new Box();
	_pBox1->setObjectType(Enumerator::Object_Type::ENEMY);
	_pBox2->setObjectType(Enumerator::Object_Type::ENEMY);
	_pBox1->setDestroy(true);
	_pBox2->setDestroy(true);
	_isAttack = false;
	_timeAttack = 0;
}

Planet::~Planet()
{
	delete _pAnim;
	delete	_pAnimAttack;
	delete	_pAnimBullet;
	delete _pPixton;
	delete _pCarryArm;
	delete _pBox1;
	delete _pBox2;
}

void Planet::draw(Camera* camera, RECT r, GVec2 scale, float angle, GVec2 rotate, D3DCOLOR color)
{
	if (!_isAllowDraw)
		return;

	_pPixton->draw(camera);

	_pAnimBullet->draw(_pAnimBullet->getPosition(), r, scale, camera->getTrans(), angle, rotate, color);

	_pAnim->setPosition(getPosition());
	_pAnim->draw(_pAnim->getPosition(), r, scale, camera->getTrans(), angle, rotate, color);

	_pAnimAttack->setPosition(_posX - 40, _posY + 32);
	_pAnimAttack->draw(_pAnimAttack->getPosition(), r, scale, camera->getTrans(), angle, rotate, color);

	_pCarryArm->draw(camera);
	_pBox1->draw(camera);
	_pBox2->draw(camera);
}

RECT Planet::getBound()
{
	RECT bound;
	bound.left = _posX + _width / 4;
	bound.right = _posX + _width / 2;
	bound.top = _posY - _height / 2;
	bound.bottom = _posY + _height / 2;

	return bound;
}
void Planet::update(float gameTime)
{
	if (!_isAllowDraw)
		return;

	_pPixton->update(gameTime);
	_pAnim->update(gameTime);
	_pAnimAttack->update(gameTime);
	_pAnimBullet->update(gameTime);

	MoveDown(gameTime);
	///Update
	_pBox1->update(gameTime);
	_pBox2->update(gameTime);
	_pCarryArm->update(gameTime);
}

void Planet::MoveDown(float gameTime)
{
	if (_isMove)
	{
		_pRockMan->setState(new StandState(_pRockMan));
		_pRockMan->setLock(true);
		_posY += 40 * gameTime;
		if (_posY > _starty)
		{
			_posY = _starty;
			_isMove = _pPixton->MoveDown(gameTime, _posX, _posY);
			if (_isMove)
			{
				_timeplay = 30;
				_pBox1->setPositionStart(_posX + 32, _posY - _height);
				_pBox2->setPositionStart(_posX + 88, _posY - _height);
				_pCarryArm->setPositionStart(_posX + 160, _posY + _height);
			}
		}
	}
	else
	{
		//Check EndGame
		_timeplay -= gameTime;
		if (_timeplay < 0 && _pBox1->IsDestroy() && _pBox2->IsDestroy())
		{
			if (!_pPixton->MoveUp(gameTime, _posX, _posY))
				_posY -= 40 * gameTime;
			_pRockMan->setState(new StandState(_pRockMan));
			_pRockMan->setLock(true);
			return;
		}

		//Planet attack when have 2 box on the pixton
		if (_pBox1->getIsBottom() && _pBox2->getIsBottom())
			if (!_isAttack && _pAnimAttack->getPause())
			{
				_isAttack = true;
				_pAnimAttack->setAnimation(0, 10, 0.15, false);
			}

		if (_isAttack && _pAnimAttack->getPause())
		{
			_planetPosY += 50 * gameTime;
			if (_pRockMan->getPosition().x > _pAnimBullet->getPosition().x)
				_planetPosX += 20 * gameTime;
			else
				_planetPosX -= 20 * gameTime;
			if (_planetPosY > 76)
			{
				_planetPosY = 76;
				if (_pRockMan->getPosition().x > _pAnimAttack->getPosition().x)
					_planetPosX += 150 * gameTime;
				else
					_planetPosX -= 150 * gameTime;

				_timeAttack += gameTime;
				if (_timeAttack > 0.2)
				{
					_planetPosY = 0;
					_planetPosX = 0;
					_isAttack = false;
					_pAnimAttack->setAnimation(1, 10, 0.15, false);
					_pAnimBullet->setPosition(0, 0);
					_timeAttack = 0;
				}
			}
			_pAnimBullet->setPosition(_pAnimAttack->getPosition().x + _planetPosX, _posY + 48 + _planetPosY);

			BaseObject * e = new BaseObject();
			e->setPosition(_pAnimBullet->getPosition());
			e->setHeight(16);
			e->setWidth(16);
			e->setDamage(3);
			e->setObjectType(Enumerator::Object_Type::ENEMY_BULLET);
			if (GameCollision::getInstance()->AABBCheck(e->getBound(), _pRockMan->getBound()))
				_pRockMan->onCollision(e);

			delete e;
		}
		else
			_pAnimBullet->setPosition(0, 0);
		//Select Box
		if (_pCarryArm->getState() == Carry_State::STAND)
		{
			if (_pBox1->IsDestroy())
			{
				_pBox1->newObject();
				_pBox1->setVy(80);
				_pCarryArm->setPosition(_posX + 32, _posY - _height - 48);
				_pCarryArm->setState(Carry_State::MOVE_DOWN);
			}
			else if (_pBox2->IsDestroy())
			{
				_pBox2->newObject();
				_pBox2->setVy(80);
				_pCarryArm->setPosition(_posX + 88, _posY - _height - 48);
				_pCarryArm->setState(Carry_State::MOVE_DOWN);
			}
		}

		///Box Collision with pixton
		if (GameCollision::getInstance()->AABBCheck(_pBox1->getBound(), _pPixton->getBound()))
		{
			_pBox1->setPosition(_posX + 32, _pPixton->getBound().top - 25);
			_pBox1->setVy(0);
			_pBox1->setIsBottom(true);
			_pCarryArm->setState(Carry_State::EVENT_MOVE_UP_2);
		}
		if (GameCollision::getInstance()->AABBCheck(_pBox2->getBound(), _pPixton->getBound()))
		{
			_pBox2->setPosition(_posX + 88, _pPixton->getBound().top - 25);
			_pBox2->setVy(0);
			_pBox2->setIsBottom(true);
			_pCarryArm->setState(Carry_State::EVENT_MOVE_UP_2);
		}

		///Box Collision with player
		if (!_pBox1->IsDestroy())
			if (GameCollision::getInstance()->AABBCheck(_pBox1->getBound(), _pRockMan->getBound()))
				_pRockMan->onCollision(_pBox1);
		if (!_pBox2->IsDestroy())
			if (GameCollision::getInstance()->AABBCheck(_pBox2->getBound(), _pRockMan->getBound()))
				_pRockMan->onCollision(_pBox2);

		///Box Collision with playerBullet
		for (auto playerBullet : _pRockMan->getPlayerBullet())
		{
			if (playerBullet->getExplosion())
				continue;

			if (!_pBox1->IsDestroy())
				if (GameCollision::getInstance()->AABBCheck(_pBox1->getBound(), playerBullet->getBound()))
				{
					_pBox1->onCollision(playerBullet);
					playerBullet->onCollision(_pBox1);
				}
			if (!_pBox2->IsDestroy())
				if (GameCollision::getInstance()->AABBCheck(_pBox2->getBound(), playerBullet->getBound()))
				{
					_pBox2->onCollision(playerBullet);
					playerBullet->onCollision(_pBox2);
				}
		}
	}
}
