#include "Planet.h"
#include "../../../GameComponents/GameCollision.h"
#include "../../Player/GameState/StandState/StandState.h"

Planet::Planet(Player* gp)
{
	pixton = new Pixton();
	anim = new Animation("Resources/Enemies/CarryArm/x3_subboss_carryarm_01.png", 1, 1, 256, 88);
	animAttack = new Animation("Resources/Enemies/CarryArm/attack.png", 2, 10, 32, 32);
	animBullet = new Animation("Resources/Enemies/CarryArm/bullet.png", 1, 3, 16, 16);
	animAttack->SetAnimation(0, 1);
	animAttack->SetPause(1);
	animBullet->SetAnimation(0, 3, 0.1);

	_HP = 1;
	_Damage = 3;
	posY = 0;
	posX = 0;
	isMove = true;
	rockman = gp;
	carryArms = new CarryArms();
	box1 = new Box();
	box2 = new Box();
	box1->SetObjectType(ENEMY);
	box2->SetObjectType(ENEMY);
	box1->SetDie(true);
	box2->SetDie(true);
	isAttack = false;
	timeAttack = 0;
}

Planet::~Planet()
{
	delete anim;
	delete	animAttack;
	delete	animBullet;
	delete pixton;
	delete carryArms;
	delete box1;
	delete box2;
}

void Planet::Draw(Camera* camera, RECT r, GVec2 scale, float angle, GVec2 rotate, D3DCOLOR color)
{
	if (!_isAllowDraw)
		return;

	pixton->Draw(camera);

	animBullet->Draw(animBullet->GetPosition(), r, scale, camera->GetTrans(), angle, rotate, color);

	anim->SetPosition(GetPosition());
	anim->Draw(anim->GetPosition(), r, scale, camera->GetTrans(), angle, rotate, color);

	animAttack->SetPosition(_posX - 40, _posY + 32);
	animAttack->Draw(animAttack->GetPosition(), r, scale, camera->GetTrans(), angle, rotate, color);

	carryArms->Draw(camera);
	box1->Draw(camera);
	box2->Draw(camera);
}

RECT Planet::GetBound()
{
	RECT r;
	r.left = _posX + _width / 4;
	r.right = _posX + _width / 2;
	r.top = _posY - _height / 2;
	r.bottom = _posY + _height / 2;

	return r;
}
void Planet::Update(float gameTime)
{
	if (!_isAllowDraw)
		return;

	pixton->Update(gameTime);
	anim->Update(gameTime);
	animAttack->Update(gameTime);
	animBullet->Update(gameTime);

	MoveDown(gameTime);
	///Update
	box1->Update(gameTime);
	box2->Update(gameTime);
	carryArms->Update(gameTime);
}

void Planet::MoveDown(float gameTime)
{
	if (isMove)
	{
		rockman->SetState(new StandState(rockman->GetPlayerData()));
		rockman->SetLock(true);
		_posY += 40 * gameTime;
		if (_posY > _starty)
		{
			_posY = _starty;
			isMove = pixton->MoveDown(gameTime, _posX, _posY);
			if (isMove)
			{
				timeplay = 30;
				box1->SetPositionStart(_posX + 32, _posY - _height);
				box2->SetPositionStart(_posX + 88, _posY - _height);
				carryArms->SetPositionStart(_posX + 160, _posY + _height);
			}
		}
	}
	else
	{
		//Check EndGame
		timeplay -= gameTime;
		if (timeplay < 0 && box1->GetDie() && box2->GetDie())
		{
			if (!pixton->MoveUp(gameTime, _posX, _posY))
				_posY -= 40 * gameTime;
			rockman->SetState(new StandState(rockman->GetPlayerData()));
			rockman->SetLock(true);
			return;
		}

		//Planet attack when have 2 box on the pixton
		if (box1->GetBottom() && box2->GetBottom())
			if (!isAttack && animAttack->GetPause())
			{
				isAttack = true;
				animAttack->SetAnimation(0, 10, 0.15, false);
			}

		if (isAttack && animAttack->GetPause())
		{
			posY += 50 * gameTime;
			if (rockman->GetPosition().x > animBullet->GetPosition().x)
				posX += 20 * gameTime;
			else
				posX -= 20 * gameTime;
			if (posY > 76)
			{
				posY = 76;
				if (rockman->GetPosition().x > animAttack->GetPosition().x)
					posX += 150 * gameTime;
				else
					posX -= 150 * gameTime;

				timeAttack += gameTime;
				if (timeAttack > 0.2)
				{
					posY = 0;
					posX = 0;
					isAttack = false;
					animAttack->SetAnimation(1, 10, 0.15, false);
					animBullet->SetPosition(0, 0);
					timeAttack = 0;
				}
			}
			animBullet->SetPosition(animAttack->GetPosition().x + posX, _posY + 48 + posY);

			BaseObject * e = new BaseObject();
			e->SetPosition(animBullet->GetPosition());
			e->SetHeight(16);
			e->SetWidth(16);
			e->SetDamage(3);
			e->SetObjectType(BaseObject::ENEMY_BULLET);
			if (GameCollision::IsCollision(e->GetBound(), rockman->GetBound()))
				rockman->OnCollision(e);

			delete e;
		}
		else
			animBullet->SetPosition(0, 0);
		//Select Box
		if (carryArms->GetState() == CarryArmsState::STAND)
		{
			if (box1->GetDie())
			{
				box1->NewEntity();
				box1->SetVy(80);
				carryArms->SetPosition(_posX + 32, _posY - _height - 48);
				carryArms->SetState(CarryArmsState::MOVE_DOWN);
			}
			else if (box2->GetDie())
			{
				box2->NewEntity();
				box2->SetVy(80);
				carryArms->SetPosition(_posX + 88, _posY - _height - 48);
				carryArms->SetState(CarryArmsState::MOVE_DOWN);
			}
		}

		///Box Collision with pixton
		if (GameCollision::IsCollision(box1->GetBound(), pixton->GetBound()))
		{
			box1->SetPosition(_posX + 32, pixton->GetBound().top - 25);
			box1->SetVy(0);
			box1->SetBottom(true);
			carryArms->SetState(CarryArmsState::EVENT_MOVE_UP_2);
		}
		if (GameCollision::IsCollision(box2->GetBound(), pixton->GetBound()))
		{
			box2->SetPosition(_posX + 88, pixton->GetBound().top - 25);
			box2->SetVy(0);
			box2->SetBottom(true);
			carryArms->SetState(CarryArmsState::EVENT_MOVE_UP_2);
		}

		///Box Collision with rockman
		if (!box1->GetDie())
			if (GameCollision::IsCollision(box1->GetBound(), rockman->GetBound()))
				rockman->OnCollision(box1);
		if (!box2->GetDie())
			if (GameCollision::IsCollision(box2->GetBound(), rockman->GetBound()))
				rockman->OnCollision(box2);

		///Box Collision with rockmanBullet
		for (auto& rockmanBullet : *rockman->GetPlayerBullet())
		{
			if (rockmanBullet->GetExplosion())
				continue;

			if (!box1->GetDie())
				if (GameCollision::IsCollision(box1->GetBound(), rockmanBullet->GetBound()))
				{
					box1->OnCollision(rockmanBullet);
					rockmanBullet->OnCollision(box1);
				}
			if (!box2->GetDie())
				if (GameCollision::IsCollision(box2->GetBound(), rockmanBullet->GetBound()))
				{
					box2->OnCollision(rockmanBullet);
					rockmanBullet->OnCollision(box2);
				}
		}
	}
}
