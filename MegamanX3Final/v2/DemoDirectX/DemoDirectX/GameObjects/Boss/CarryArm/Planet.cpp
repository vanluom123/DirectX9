#include "Planet.h"
#include "../../../GameComponents/GameCollision.h"
#include "../../Player/GameState/StandState/StandState.h"

Planet::Planet(Player* gp)
{
	_pPixton = new Pixton();
	_pAnim = new Animation("Resources/Enemies/CarryArm/x3_subboss_carryarm_01.png", 1, 1, 256, 88);
	_pAnimAttack = new Animation("Resources/Enemies/CarryArm/attack.png", 2, 10, 32, 32);
	_pAnimBullet = new Animation("Resources/Enemies/CarryArm/bullet.png", 1, 3, 16, 16);
	_pAnimAttack->SetAnimation(0, 1);
	_pAnimAttack->SetPause(1);
	_pAnimBullet->SetAnimation(0, 3, 0.1);

	_HP = 1;
	_Damage = 3;
	_planetPosY = 0;
	_planetPosX = 0;
	_isMove = true;
	_pRockMan = gp;
	_pCarryArm = new CarryArm();
	_pBox1 = new Box();
	_pBox2 = new Box();
	_pBox1->SetObjectType(ENEMY);
	_pBox2->SetObjectType(ENEMY);
	_pBox1->SetDie(true);
	_pBox2->SetDie(true);
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

void Planet::Draw(Camera* camera, RECT r, GVec2 scale, float angle, GVec2 rotate, D3DCOLOR color)
{
	if (!_isAllowDraw)
		return;

	_pPixton->Draw(camera);

	_pAnimBullet->Draw(_pAnimBullet->GetPosition(), r, scale, camera->GetTrans(), angle, rotate, color);

	_pAnim->SetPosition(GetPosition());
	_pAnim->Draw(_pAnim->GetPosition(), r, scale, camera->GetTrans(), angle, rotate, color);

	_pAnimAttack->SetPosition(_posX - 40, _posY + 32);
	_pAnimAttack->Draw(_pAnimAttack->GetPosition(), r, scale, camera->GetTrans(), angle, rotate, color);

	_pCarryArm->Draw(camera);
	_pBox1->Draw(camera);
	_pBox2->Draw(camera);
}

RECT Planet::GetBound()
{
	RECT bound;
	bound.left = _posX + _width / 4;
	bound.right = _posX + _width / 2;
	bound.top = _posY - _height / 2;
	bound.bottom = _posY + _height / 2;

	return bound;
}
void Planet::Update(float gameTime)
{
	if (!_isAllowDraw)
		return;

	_pPixton->Update(gameTime);
	_pAnim->Update(gameTime);
	_pAnimAttack->Update(gameTime);
	_pAnimBullet->Update(gameTime);

	MoveDown(gameTime);
	///Update
	_pBox1->Update(gameTime);
	_pBox2->Update(gameTime);
	_pCarryArm->Update(gameTime);
}

void Planet::MoveDown(float gameTime)
{
	if (_isMove)
	{
		_pRockMan->SetState(new StandState(_pRockMan->GetPlayerData()));
		_pRockMan->SetLock(true);
		_posY += 40 * gameTime;
		if (_posY > _starty)
		{
			_posY = _starty;
			_isMove = _pPixton->MoveDown(gameTime, _posX, _posY);
			if (_isMove)
			{
				_timeplay = 30;
				_pBox1->SetPositionStart(_posX + 32, _posY - _height);
				_pBox2->SetPositionStart(_posX + 88, _posY - _height);
				_pCarryArm->SetPositionStart(_posX + 160, _posY + _height);
			}
		}
	}
	else
	{
		//Check EndGame
		_timeplay -= gameTime;
		if (_timeplay < 0 && _pBox1->GetDie() && _pBox2->GetDie())
		{
			if (!_pPixton->MoveUp(gameTime, _posX, _posY))
				_posY -= 40 * gameTime;
			_pRockMan->SetState(new StandState(_pRockMan->GetPlayerData()));
			_pRockMan->SetLock(true);
			return;
		}

		//Planet attack when have 2 box on the pixton
		if (_pBox1->GetBottom() && _pBox2->GetBottom())
			if (!_isAttack && _pAnimAttack->GetPause())
			{
				_isAttack = true;
				_pAnimAttack->SetAnimation(0, 10, 0.15, false);
			}

		if (_isAttack && _pAnimAttack->GetPause())
		{
			_planetPosY += 50 * gameTime;
			if (_pRockMan->GetPosition().x > _pAnimBullet->GetPosition().x)
				_planetPosX += 20 * gameTime;
			else
				_planetPosX -= 20 * gameTime;
			if (_planetPosY > 76)
			{
				_planetPosY = 76;
				if (_pRockMan->GetPosition().x > _pAnimAttack->GetPosition().x)
					_planetPosX += 150 * gameTime;
				else
					_planetPosX -= 150 * gameTime;

				_timeAttack += gameTime;
				if (_timeAttack > 0.2)
				{
					_planetPosY = 0;
					_planetPosX = 0;
					_isAttack = false;
					_pAnimAttack->SetAnimation(1, 10, 0.15, false);
					_pAnimBullet->SetPosition(0, 0);
					_timeAttack = 0;
				}
			}
			_pAnimBullet->SetPosition(_pAnimAttack->GetPosition().x + _planetPosX, _posY + 48 + _planetPosY);

			BaseObject * e = new BaseObject();
			e->SetPosition(_pAnimBullet->GetPosition());
			e->SetHeight(16);
			e->SetWidth(16);
			e->SetDamage(3);
			e->SetObjectType(BaseObject::ENEMY_BULLET);
			if (GameCollision::IsCollision(e->GetBound(), _pRockMan->GetBound()))
				_pRockMan->OnCollision(e);

			delete e;
		}
		else
			_pAnimBullet->SetPosition(0, 0);
		//Select Box
		if (_pCarryArm->GetState() == eCarryArmState::CARRY_ARM_STAND)
		{
			if (_pBox1->GetDie())
			{
				_pBox1->NewEntity();
				_pBox1->SetVy(80);
				_pCarryArm->SetPosition(_posX + 32, _posY - _height - 48);
				_pCarryArm->SetState(eCarryArmState::CARRY_ARM_MOVE_DOWN);
			}
			else if (_pBox2->GetDie())
			{
				_pBox2->NewEntity();
				_pBox2->SetVy(80);
				_pCarryArm->SetPosition(_posX + 88, _posY - _height - 48);
				_pCarryArm->SetState(eCarryArmState::CARRY_ARM_MOVE_DOWN);
			}
		}

		///Box Collision with pixton
		if (GameCollision::IsCollision(_pBox1->GetBound(), _pPixton->GetBound()))
		{
			_pBox1->SetPosition(_posX + 32, _pPixton->GetBound().top - 25);
			_pBox1->SetVy(0);
			_pBox1->SetBottom(true);
			_pCarryArm->SetState(eCarryArmState::CARRY_ARM_EVENT_MOVE_UP_2);
		}
		if (GameCollision::IsCollision(_pBox2->GetBound(), _pPixton->GetBound()))
		{
			_pBox2->SetPosition(_posX + 88, _pPixton->GetBound().top - 25);
			_pBox2->SetVy(0);
			_pBox2->SetBottom(true);
			_pCarryArm->SetState(eCarryArmState::CARRY_ARM_EVENT_MOVE_UP_2);
		}

		///Box Collision with rockman
		if (!_pBox1->GetDie())
			if (GameCollision::IsCollision(_pBox1->GetBound(), _pRockMan->GetBound()))
				_pRockMan->OnCollision(_pBox1);
		if (!_pBox2->GetDie())
			if (GameCollision::IsCollision(_pBox2->GetBound(), _pRockMan->GetBound()))
				_pRockMan->OnCollision(_pBox2);

		///Box Collision with rockmanBullet
		for (auto& rockmanBullet : *_pRockMan->GetPlayerBullet())
		{
			if (rockmanBullet->GetExplosion())
				continue;

			if (!_pBox1->GetDie())
				if (GameCollision::IsCollision(_pBox1->GetBound(), rockmanBullet->GetBound()))
				{
					_pBox1->OnCollision(rockmanBullet);
					rockmanBullet->OnCollision(_pBox1);
				}
			if (!_pBox2->GetDie())
				if (GameCollision::IsCollision(_pBox2->GetBound(), rockmanBullet->GetBound()))
				{
					_pBox2->OnCollision(rockmanBullet);
					rockmanBullet->OnCollision(_pBox2);
				}
		}
	}
}
