#include "BlastHornet.h"
#include "BlastDeath.h"
#include "BlastMove.h"
#include "BlastAppear.h"
#include "../../../GameComponents/GameMap.h"


BlastHornet::BlastHornet()
{
	this->loadResource();
	this->m_Dx = 0.0f;
	this->m_Dy = 0.0f;

	this->m_pPlayer = nullptr;
	this->_isReverse = false;
	this->_objectType = Enumerator::Object_Type::BOSS;
	this->_MaxHP = 30;
	this->_Damage = 3;
	this->_HP = this->_MaxHP;
	this->m_HPBar = new HPBar(this->_objectType);
	this->setState(new BlastMove(this, false, false));
}


BlastHornet::~BlastHornet()
{
	for (auto& bullet : this->_listBullet)
		delete bullet;
	if (!this->_listBullet.empty())
		this->_listBullet.clear();

	delete this->m_pAppear;
	delete this->m_pIdle;
	delete this->m_pAttack;
	delete this->m_pShoot;
	delete this->m_pMove;
	delete this->m_pDeath;
	delete this->m_pState;
}

RECT BlastHornet::getBound()
{
	RECT r;
	r.left = _posX - 20;
	r.right = _posX + 30;
	r.top = _posY - 30;
	r.bottom = _posY + 45;
	return r;
}

void BlastHornet::update(float dt)
{
	for (auto& bullet : _listBullet)
		bullet->update(dt);

	// m_Dx: Distance of Blast Hornet with Player to coordinate X
	// m_Dy: Distance of Blast Hornet with Player to coordinate Y

	// m_Dx < 0: _isReverse = true
	// m_Dx > 0: _isReverse = false
	this->m_Dx = this->getPosition().x - this->m_pPlayer->getPosition().x;
	this->m_Dy = this->getPosition().y - this->m_pPlayer->getPosition().y;

	// m_DxBoss_Wall: Distance of Blast Hornet with Object Wall to coordinate X
	// m_DxBoss_Wall < 0: Object wall the right of Blast Hornets' side
	// m_DxBoss_Wall > 0: Object wall the left of Blast Hornets' side
	//m_DxBoss_Wall = this->getPosition().x - m_pGameMap->getObjectWall()->getPosition().x;

	this->m_DxPos_PosStart = abs(this->getPosition().x - this->getPositionStart().x);
	this->m_DyPos_PosStart = abs(this->getPosition().y - this->getPositionStart().y);

	if (this->_isAllowDraw)
	{
		if (this->m_currentState == Enumerator::Hornet_State::APPEAR || this->m_currentState == Enumerator::Hornet_State::ATTACK) {
			this->m_pCurrentAnimation->fixUpdate(dt);
		}
		else {
			this->m_pCurrentAnimation->update(dt);
		}

		BaseObject::update(dt);

		if (this->m_pState)
			this->m_pState->update(dt);
	}
}

void BlastHornet::onCollision(Side_Collision side)
{
	if (this->m_pState)
		this->m_pState->onCollision(side);
}

void BlastHornet::onCollision(BaseObject* obj)
{
	if (obj->getObjectType() == Enumerator::Object_Type::ROCKMAN_BULLET && !this->_isDestroy)
	{
		auto playerBullet = dynamic_cast<PlayerBullet*>(obj);
		this->_HP -= playerBullet->getDamage();
	}

	if (this->_HP <= 0)
	{
		this->setState(new BlastDeath(this));
		this->_isDestroy = true;
	}
}

void BlastHornet::draw(Camera* camera, RECT r, GVec2 scale, float angle, GVec2 rotate, D3DCOLOR color)
{
	for (auto& bullet : _listBullet)
		bullet->draw(camera, r, scale, angle, rotate, color);

	this->m_HPBar->draw(this->_HP, this->_MaxHP);

	if (this->_isAllowDraw)
	{
		if (!this->m_pState->getConfirmMoveUp())
		{
			if (this->m_Dx < 0) this->_isReverse = true;
			else this->_isReverse = false;
		}

		this->m_pCurrentAnimation->setPosition(this->getPosition());
		this->m_pCurrentAnimation->setReverse(this->_isReverse);

		if (camera)
			this->m_pCurrentAnimation->draw(this->m_pCurrentAnimation->getPosition(), r, scale, camera->getTrans(), angle, rotate, color);
		else
			this->m_pCurrentAnimation->draw(this->m_pCurrentAnimation->getPosition());
	}
}

void BlastHornet::setState(BlastHornetState* new_state)
{
	if (this->m_currentState == new_state->getState())
		return;

	delete this->m_pState;
	this->m_pState = new_state;
	this->m_currentState = new_state->getState();
	this->changeAnimation(new_state->getState());
}

void BlastHornet::loadResource()
{
	// Idle
	this->m_pIdle = new Animation(Define::BLAST_HORNET_IDLE, 1, 4, 96, 96, 0.05f, D3DCOLOR_XRGB(0, 128, 128));
	// Move
	this->m_pMove = new Animation(Define::BLAST_HORNET_IDLE, 1, 4, 96, 96, 0.05f, D3DCOLOR_XRGB(0, 128, 128));
	// Appear
	this->m_pAppear = new Animation(Define::BLAST_HORNET_APPEAR, 4, 9, 102, 104, 0.05f, D3DCOLOR_XRGB(0, 128, 128));
	// Attack
	this->m_pAttack = new Animation(Define::BLAST_HORNET_ATTACK, 4, 9, 102, 104, 0.05f, D3DCOLOR_XRGB(0, 128, 128));
	// Shoot
	this->m_pShoot = new Animation(Define::BLAST_HORNET_SHOOT, 1, 15, 96, 96, 0.05f, D3DCOLOR_XRGB(0, 128, 128));
	// Death
	this->m_pDeath = new Animation(Define::EXPLOSIONS, 1, 8, 35, 30, 0.05f);
}

void BlastHornet::changeAnimation(Hornet_State state)
{
	switch (state)
	{
		case Enumerator::Hornet_State::APPEAR:
			this->m_pCurrentAnimation = this->m_pAppear;
			this->m_pCurrentAnimation->setLoop(false);
			break;

		case Enumerator::Hornet_State::STAND:
			this->m_pCurrentAnimation = this->m_pIdle;
			this->m_pCurrentAnimation->setAnimation(0, 4, 0.05f);
			break;

		case Enumerator::Hornet_State::ATTACK:
			this->m_pCurrentAnimation = this->m_pAttack;
			this->m_pCurrentAnimation->setLoop(false);
			break;

		case Enumerator::Hornet_State::SHOOT:
			this->m_pCurrentAnimation = this->m_pShoot;
			this->m_pCurrentAnimation->setAnimation(0, 15, 0.05f, false);
			break;

		case Enumerator::Hornet_State::MOVE:
			this->m_pCurrentAnimation = this->m_pMove;
			this->m_pCurrentAnimation->setAnimation(0, 4, 0.05f);
			break;

		case Enumerator::Hornet_State::DEATH:
			this->m_pCurrentAnimation = this->m_pDeath;
			this->m_pCurrentAnimation->setAnimation(0, 8, 0.05f, false);
			break;

		default:
			break;
	}

	this->setWidth(this->m_pCurrentAnimation->getWidth());
	this->setHeight(this->m_pCurrentAnimation->getHeight());
}

Animation* BlastHornet::getAnimBlast()
{
	return this->m_pCurrentAnimation;
}

Player* BlastHornet::getPlayer()
{
	return this->m_pPlayer;
}

void BlastHornet::setPlayer(Player* val)
{
	this->m_pPlayer = val;
}

void BlastHornet::setGameMap(GameMap* val)
{
	this->m_pGameMap = val;
}

float BlastHornet::getDx() const
{
	return this->m_Dx;
}

float BlastHornet::getDy() const
{
	return this->m_Dy;
}

float BlastHornet::getDxPos_PosStart() const { return this->m_DxPos_PosStart; }

float BlastHornet::getDyPos_PosStart() const { return this->m_DyPos_PosStart; }

float BlastHornet::getTempDxPos_PosStart() const { return this->m_tempDxPos_PosStart; }

void BlastHornet::setTempDxPos_PosStart(float val) { this->m_tempDxPos_PosStart = val; }

float BlastHornet::getTempDyPos_PosStart() const { return this->m_tempDyPos_PosStart; }

void BlastHornet::setTempDyPos_PosStart(float val) { this->m_tempDyPos_PosStart = val; }
