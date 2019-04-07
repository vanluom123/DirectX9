#include "Planet.h"
#include "../../../GameComponents/GameCollision.h"
#include "../../Player/GameState/StandState/StandState.h"

Planet::Planet(GamePlayer* gp)
{
	pixton = new Pixton();
	anim = new Animation("Resources/Enemies/CarryArm/x3_subboss_carryarm_01.png", 1, 1, 256, 88);
	animAttack = new Animation("Resources/Enemies/CarryArm/attack.png", 2, 10, 32, 32);
	animBullet = new Animation("Resources/Enemies/CarryArm/bullet.png", 1, 3, 16, 16);
	animAttack->setAnimation(0, 1);
	animAttack->setPause(1);
	animBullet->setAnimation(0, 3, 0.1);

	HP = 1;
	Damage = 3;
	posY = 0;
	posX = 0;
	isMove = true;
	rockman = gp;
	carryArms = new CarryArms();
	box1 = new Box();
	box2 = new Box();
	box1->SetTag(ENEMY);
	box2->SetTag(ENEMY);
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

void Planet::Draw(Camera* camera, RECT r, D3DXVECTOR2 scale, float angle, D3DXVECTOR2 rotate, D3DCOLOR color)
{
	if (!allowDraw)
		return;

	pixton->Draw(camera);

	animBullet->draw(animBullet->getPosition(), r, scale, camera->getTrans(), angle, rotate, color);

	anim->setPosition(GetPosition());
	anim->draw(anim->getPosition(), r, scale, camera->getTrans(), angle, rotate, color);

	animAttack->setPosition(x - 40, y + 32);
	animAttack->draw(animAttack->getPosition(), r, scale, camera->getTrans(), angle, rotate, color);

	carryArms->Draw(camera);
	box1->Draw(camera);
	box2->Draw(camera);
}

RECT Planet::GetBound()
{
	RECT r;
	r.left = x + width / 4;
	r.right = x + width / 2;
	r.top = y - height / 2;
	r.bottom = y + height / 2;

	return r;
}
void Planet::Update(float gameTime)
{
	if (!allowDraw)
		return;

	pixton->Update(gameTime);
	anim->update(gameTime);
	animAttack->update(gameTime);
	animBullet->update(gameTime);

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
		y += 40 * gameTime;
		if (y > starty)
		{
			y = starty;
			isMove = pixton->MoveDown(gameTime, x, y);
			if (isMove)
			{
				timeplay = 30;
				box1->SetPositionStart(x + 32, y - height);
				box2->SetPositionStart(x + 88, y - height);
				carryArms->SetPositionStart(x + 160, y + height);
			}
		}
	}
	else
	{
		//Check EndGame
		timeplay -= gameTime;
		if (timeplay < 0 && box1->GetDie() && box2->GetDie())
		{
			if (!pixton->MoveUp(gameTime, x, y))
				y -= 40 * gameTime;
			rockman->SetState(new StandState(rockman->GetPlayerData()));
			rockman->SetLock(true);
			return;
		}

		//Planet attack when have 2 box on the pixton
		if (box1->GetBottom() && box2->GetBottom())
			if (!isAttack && animAttack->getPause())
			{
				isAttack = true;
				animAttack->setAnimation(0, 10, 0.15, false);
			}

		if (isAttack && animAttack->getPause())
		{
			posY += 50 * gameTime;
			if (rockman->GetPosition().x > animBullet->getPosition().x)
				posX += 20 * gameTime;
			else
				posX -= 20 * gameTime;
			if (posY > 76)
			{
				posY = 76;
				if (rockman->GetPosition().x > animAttack->getPosition().x)
					posX += 150 * gameTime;
				else
					posX -= 150 * gameTime;

				timeAttack += gameTime;
				if (timeAttack > 0.2)
				{
					posY = 0;
					posX = 0;
					isAttack = false;
					animAttack->setAnimation(1, 10, 0.15, false);
					animBullet->setPosition(0, 0);
					timeAttack = 0;
				}
			}
			animBullet->setPosition(animAttack->getPosition().x + posX, y + 48 + posY);

			Entity * e = new Entity();
			e->SetPosition(animBullet->getPosition());
			e->SetHeight(16);
			e->SetWidth(16);
			e->SetDamage(3);
			e->SetTag(Entity::ENEMY_BULLET);
			if (GameCollision::IsCollision(e->GetBound(), rockman->GetBound()))
				rockman->OnCollision(e);

			delete e;
		}
		else
			animBullet->setPosition(0, 0);
		//Select Box
		if (carryArms->GetState() == CarryArmsState::STAND)
		{
			if (box1->GetDie())
			{
				box1->NewEntity();
				box1->SetVy(80);
				carryArms->SetPosition(x + 32, y - height - 48);
				carryArms->SetState(CarryArmsState::MOVE_DOWN);
			}
			else if (box2->GetDie())
			{
				box2->NewEntity();
				box2->SetVy(80);
				carryArms->SetPosition(x + 88, y - height - 48);
				carryArms->SetState(CarryArmsState::MOVE_DOWN);
			}
		}

		///Box Collision with pixton
		if (GameCollision::IsCollision(box1->GetBound(), pixton->GetBound()))
		{
			box1->SetPosition(x + 32, pixton->GetBound().top - 25);
			box1->SetVy(0);
			box1->SetBottom(true);
			carryArms->SetState(CarryArmsState::EVENT_MOVE_UP_2);
		}
		if (GameCollision::IsCollision(box2->GetBound(), pixton->GetBound()))
		{
			box2->SetPosition(x + 88, pixton->GetBound().top - 25);
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
		for (auto& rockmanBullet : *rockman->getPlayerBullet())
		{
			if (rockmanBullet->getExplosions())
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
