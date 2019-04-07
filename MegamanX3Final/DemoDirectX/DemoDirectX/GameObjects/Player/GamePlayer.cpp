#include "GamePlayer.h"
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

GamePlayer::GamePlayer()
{
	tag = ROCK_MAN;
	id = 0;
	pAnimation = new Animation(Define::ANIMATION_ROCKMAN, 21, 10, 49, 49, 0.15, D3DCOLOR_XRGB(100, 100, 100));
	pAniEfectCharge = new Animation(Define::ANIMATION_CHARGE, 2, 12, 55, 65, 0.02);
	pAniEfectDash = new Animation(Define::ANIMATION_DASH, 1, 11, 75, 35, 0.15);
	pAniEfectSlide = new Animation(Define::ANIMATION_SLIDE, 1, 2, 30, 30, 0.15);
	hpbar = new HPBar(tag);

	pAniEfectCharge->setPause(true);
	pAniEfectDash->setPause(true);
	pAniEfectSlide->setAnimation(0, 2, 0.1);
	pAniEfectSlide->setPause(true);

	allowJump = true;
	allowShoot = true;
	allowDash = true;
	isReverse = false;

	isShoot = false;
	alive = false;
	islock = false;

	timeShoot = 0.3f;
	timeCurrentShoot = 0.0f;
	timeChangeShoot = 0.0f;
	timeAlive = 0.0f;

	vx = 0;
	vy = 0;
	MaxHP = 15;
	HP = MaxHP;
	Damage = 0;

	currentState = FALL;

	pData = new PlayerData();
	pData->SetGamePlayer(this);
	SetState(new AppearState(pData));
}

GamePlayer::~GamePlayer()
{
	delete hpbar;
	delete pAnimation;
	delete pData;
	for (auto& bullet : listBullet)
		delete bullet;
	listBullet.clear();
}

void GamePlayer::ChangeAnimation(StateName state)
{
	switch (state)
	{
	case APPEAR:
		pAnimation->setAnimation(0, 5, 0.15, false);
		break;

	case STAND:
		pAnimation->setAnimation(1, 4, 0.1, false);
		break;

	case RUN:
		pAnimation->setAnimation(3, 10, 0.05);
		break;

	case JUMP:
		pAnimation->setAnimation(5, 3, 0.05, false);
		break;

	case FALL:
		pAnimation->setAnimation(7, 3, 0.05, false);
		break;

	case CLING:
		pAnimation->setAnimation(9, 4, 0.03, false);
		break;

	case SLIP_DOWN:
		pAnimation->setAnimation(11, 3, 0.05, false);
		break;

	case DASH:
		pAnimation->setAnimation(16, 2, 0.05, false);
		break;

	case CLIMB:
		break;

	case BLEED:
		pAnimation->setAnimation(18, 9, 0.05);
		break;

	case DIE:
		pAnimation->setAnimation(20, 3, 0.3f);
		break;

	case WIN: break;

	default: break;
	}

	this->SetWidth(pAnimation->getWidth());
	this->SetHeight(pAnimation->getHeight());
}

void GamePlayer::SetState(GameState * newState)
{
	if (currentState == newState->GetState())
		return;

	if (pData->GetGameState()) {
		delete pData->GetGameState();
		pData->SetGameState(nullptr);
	}

	pData->SetGameState(newState);
	ChangeAnimation(newState->GetState());
	currentState = newState->GetState();

	if (currentState != DASH && currentState != CLING)
		pAniEfectDash->setPause(true);

	if (currentState == SLIP_DOWN)
		posSlideDown = y;

	else
		posSlideDown = std::numeric_limits<float>::infinity();
}

void GamePlayer::handlerKeyBoard(const std::map<int, bool> & keys, float dt)
{
	if (!islock)
	{
		if (pData->GetGameState())
			pData->GetGameState()->handlerKeyBoard(keys, dt);
	}
	islock = false;
}

void GamePlayer::onKeyDown(std::map<int, bool> keys, int Key)
{
	if (islock)
		return;

	if (currentState == DIE
		|| currentState == APPEAR
		|| currentState == WIN
		|| currentState == BLEED)
		return;

	if (Key == VK_JUMP && allowJump)
	{
		allowJump = false;
		switch (currentState)
		{
		case STAND: case RUN: case DASH:
		{
			SetState(new JumpState(pData));
			break;
		}
		case SLIP_DOWN:
		{

			pAniEfectDash->setReverse(!isReverse);
			if (isReverse)
				pAniEfectDash->setPosition(x, y + 12);
			else
				pAniEfectDash->setPosition(x, y + 12);

			pAniEfectDash->setAnimation(1, 1, 0.005, false);
			if (keys[VK_SLIDE])
				SetState(new ClingState(pData, true));
			else
				SetState(new ClingState(pData));
			break;
		}
		default: break;
		}
	}

	if (Key == VK_SHOOT && allowShoot)
	{
		if (currentState == BLEED)
			return;

		if (!isShoot)
		{
			isShoot = true;
			pAnimation->setShoot(isShoot);

		}
		PlayerShoot(PlayerBullet::NORMAL);
		Sound::getInstance()->play("ShootingBullet", false, 1);

		allowShoot = false;
		timeCurrentShoot = 0.0f;
	}

	if (Key == VK_SLIDE && allowDash)
	{
		allowDash = false;

		switch (currentState)
		{
		case STAND: case RUN:
			pAniEfectDash->setReverse(isReverse);
			pAniEfectDash->setPosition(x, y + 12);
			pAniEfectDash->setAnimation(0, 11, 0.05, false);
			SetState(new DashState(pData));
			break;
		default: break;
		}
	}
}

void GamePlayer::onKeyUp(int Key)
{
	if (islock)
		return;

	switch (Key)
	{
	case VK_JUMP:
	{
		if (currentState == JUMP || currentState == CLING)
			vy = 0;
		allowJump = true;
		break;
	}
	case VK_SHOOT:
	{
		allowShoot = true;
		pAniEfectCharge->setPause(true);

		if (currentState == BLEED)
			return;

		if (timeChangeShoot > timeShoot * 4)
		{
			isShoot = true;
			pAnimation->setShoot(isShoot);
			//The second level
			PlayerShoot(PlayerBullet::SECOND_LEVEL);
			Sound::getInstance()->stop("AbsorbLongEnergy");
			Sound::getInstance()->play("GiveUpLongEnergy", false, 1);
		}
		else
		{
			if (timeChangeShoot > timeShoot * 2)
			{
				isShoot = true;
				pAnimation->setShoot(isShoot);
				//The first level
				PlayerShoot(PlayerBullet::FIRST_LEVEL);
				Sound::getInstance()->stop("AbsorbShortEnergy");
				Sound::getInstance()->play("GiveUpShortEnergy", false, 1);
			}
		}

		timeChangeShoot = 0.0f;

		break;
	}
	case VK_SLIDE:
	{
		if (currentState == DASH)
			SetState(new StandState(pData));
		allowDash = true;
		break;
	}
	default:break;
	}
}

RECT GamePlayer::GetBound()
{
	RECT r;

	r.left = x - 13;
	r.right = x + 13;
	r.top = y - 15;
	r.bottom = y + 49 / 2.0f;

	return r;
}

void GamePlayer::Update(float dt)
{
	OnNoCollisionWithBottom();

	for (auto& bullet : listBullet)
		bullet->Update(dt);

	if (isShoot)
	{
		timeCurrentShoot += dt;
		if (timeCurrentShoot > timeShoot)
		{
			isShoot = false;
			pAnimation->setShoot(isShoot);
			timeCurrentShoot = 0;
		}
	}

	//Animation Charge Bullet
	if (!allowShoot)
	{
		timeChangeShoot += dt;

		if (timeChangeShoot > timeShoot * 4)
		{
			Sound::getInstance()->stop("AbsorbShortEnergy");
			Sound::getInstance()->play("AbsorbLongEnergy", true, 0);
			pAniEfectCharge->setPause(false);
			if (pAniEfectCharge->getCurrentRow() != 1)
				pAniEfectCharge->setAnimation(1, 12, 0.017);
		}
		else if (timeChangeShoot > timeShoot * 2)
		{
			Sound::getInstance()->play("AbsorbShortEnergy", true, 0);
			pAniEfectCharge->setPause(false);
			if (pAniEfectCharge->getCurrentRow() != 0)
				pAniEfectCharge->setAnimation(0, 12, 0.02);
		}
	}


	//thời gian bất tử
	if (alive)
	{
		timeAlive += dt;
		if (timeAlive > 1.5f)
		{
			alive = false;
			allowDraw = true;
			timeAlive = 0.0f;
		}
		else
		{
			int TimePause = timeAlive / 0.05f;//0.1 time twinkle
			if (TimePause % 2 == 0)
				allowDraw = true;
			else if (TimePause % 2 == 1)
				allowDraw = false;
		}
	}

	if (y - posSlideDown > 8)
		pAniEfectSlide->setPause(false);
	else
		pAniEfectSlide->setPause(true);

	Entity::Update(dt);
	pAnimation->update(dt);
	pAniEfectCharge->update(dt);
	pAniEfectDash->update(dt);
	pAniEfectSlide->update(dt);

	if (pData->GetGameState())
		pData->GetGameState()->update(dt);
}

void GamePlayer::drawHP()
{
	hpbar->draw(HP, MaxHP);
}

void GamePlayer::Draw(Camera * camera, RECT rect, D3DXVECTOR2 scale, float angle, D3DXVECTOR2 rotationCenter,
	D3DCOLOR color)
{
	for (auto& bullet : listBullet)
		bullet->Draw(camera);

	if (!allowDraw)
		return;

	pAnimation->setReverse(isReverse);
	pAnimation->setPosition(GetPosition());

	if (camera)
	{
		pAnimation->draw(pAnimation->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
		if (!pAniEfectCharge->getPause())
		{
			pAniEfectCharge->setReverse(isReverse);
			pAniEfectCharge->setPosition(x, y + 6);
			pAniEfectCharge->draw(pAniEfectCharge->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
		}

		if (!pAniEfectDash->getPause())
			pAniEfectDash->draw(pAniEfectDash->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);

		if (!pAniEfectSlide->getPause())
		{
			pAniEfectSlide->setReverse(isReverse);
			if (isReverse)
				pAniEfectSlide->setPosition(x - 15, y);
			else
				pAniEfectSlide->setPosition(x + 15, y);

			pAniEfectSlide->draw(pAniEfectSlide->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
		}
	}
	else
		pAnimation->draw(pAnimation->getPosition());
}

void GamePlayer::OnCollision(SideCollisions side)
{
	if (sideX != NONE)
	{
		if (entityX->GetTag() == PORT)
		{
			if (entityX->GetHP() <= 0)
			{
				sideX = Entity::NONE;
				collisionTimeMinX = 1.0f;
				return;
			}
		}
	}
	if (pData->GetGameState())
		pData->GetGameState()->onCollision(side);
}

void GamePlayer::OnNoCollisionWithBottom()
{
	if (sideY != BOTTOM)
	{
		switch (currentState)
		{
		case STAND:case RUN:case DASH:
			SetState(new FallState(pData));
			break;
		default:break;
		}
	}
}

void GamePlayer::OnCollision(Entity * object)
{
	switch (object->GetTag())
	{
	case Entity::ENEMY:
	case Entity::ENEMY_BULLET:
	case Entity::BOSS:
	{
		if (alive)
			return;

		//HP -= object->getDamage();
		alive = true;
		if (HP <= 0)
		{
			SetState(new DieState(pData));
			alive = false;
			isDie = true;
			return;
		}

		pAnimation->setShoot(false);

		if (x < object->GetPosition().x)
			SetState(new BleedState(pData, 1));
		else
			SetState(new BleedState(pData, -1));
		break;
	}

	case Entity::ELEVATOR:
	{
		if (currentState == JUMP || currentState == CLING)
			break;
		y = object->GetBound().top - 24.51f;
		sideY = BOTTOM;
		break;
	}

	case Entity::PORT:
	{
		if (object->GetHP() <= 0 && GetBound().top > object->GetBound().top)
		{
			islock = true;
			if (object->GetDamage() > 0)
				pAnimation->setPause(false);
			else
				pAnimation->setPause(true);
		}
		break;
	}

	case Entity::THORN:
	{
		HP = 0;
		isDie = true;
		SetState(new DieState(pData));
		alive = false;
		break;
	}

	case Entity::TAG_NONE:
		break;
	default:
		break;
	}
}

void GamePlayer::PlayerShoot(PlayerBullet::BulletType bulletType)
{
	PlayerBullet* playerBullet = NULL;
	if (listBullet.size() < 3)
	{
		playerBullet = new PlayerBullet();
		listBullet.push_back(playerBullet);
	}
	else
	{
		for (auto& bullet : listBullet)
			if (bullet->getExplosions())
			{
				playerBullet = bullet;
				break;
			}
		if (playerBullet == NULL)
			return;
	}

	bool isReverseBullet = isReverse;
	float posX = 0;
	float posY = this->GetBound().bottom - 18;

	if (currentState == SLIP_DOWN)
	{
		isReverseBullet = !isReverse;
		if (!isReverse)
			posX = this->GetBound().left + playerBullet->GetWidth() / 4.0f;
		else
			posX = this->GetBound().right - playerBullet->GetWidth() / 4.0f;
	}
	else
	{
		if (!isReverse)
			posX = this->GetBound().right - playerBullet->GetWidth() / 4.0f;
		else
			posX = this->GetBound().left + playerBullet->GetWidth() / 4.0f;
	}

	playerBullet->newBullet(posX, posY, isReverseBullet, bulletType);
}