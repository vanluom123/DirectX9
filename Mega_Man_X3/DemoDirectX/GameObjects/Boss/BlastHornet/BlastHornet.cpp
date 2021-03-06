#include "BlastHornet.h"
#include "BlastDeath.h"
#include "BlastMove.h"
#include "BlastAppear.h"
#include "../../../GameComponents/GameMap.h"


BlastHornet::BlastHornet()
{
	loadResource();
	m_Dx = 0.0f;
	m_Dy = 0.0f;

	m_pPlayer = nullptr;
	_isReverse = false;
	_objectType = eObject_Boss;
	_MaxHP = 30;
	_Damage = 3;
	_HP = _MaxHP;
	m_HPBar = new HPBar(_objectType);
	setState(new BlastMove(this, false, false));
}


BlastHornet::~BlastHornet()
{
	for (auto& bullet : _listBullet)
		delete bullet;
	if (!_listBullet.empty())
		_listBullet.clear();

	delete m_pAppear;
	delete m_pIdle;
	delete m_pAttack;
	delete m_pShoot;
	delete m_pMove;
	delete m_pDeath;
	delete m_pState;
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
	m_Dx = this->getPosition().x - m_pPlayer->getPosition().x;
	m_Dy = this->getPosition().y - m_pPlayer->getPosition().y;

	// m_DxBoss_Wall: Distance of Blast Hornet with Object Wall to coordinate X
	// m_DxBoss_Wall < 0: Object wall the right of Blast Hornets' side
	// m_DxBoss_Wall > 0: Object wall the left of Blast Hornets' side
	//m_DxBoss_Wall = this->getPosition().x - m_pGameMap->getObjectWall()->getPosition().x;

	m_DxPos_PosStart = abs(this->getPosition().x - this->getPositionStart().x);
	m_DyPos_PosStart = abs(this->getPosition().y - this->getPositionStart().y);

	if (_isAllowDraw)
	{
		if (m_currentState == eHornet_Appear || m_currentState == eHornet_Attack) {
			m_pCurrentAnimation->fixUpdate(dt);
		}
		else {
			m_pCurrentAnimation->update(dt);
		}

		BaseObject::update(dt);

		if (m_pState)
			m_pState->update(dt);
	}
}

void BlastHornet::onCollision(Side_Collision side)
{
	if (m_pState)
		m_pState->onCollision(side);
}

void BlastHornet::onCollision(BaseObject* obj)
{
	if (obj->getObjectType() == eObject_RockMan_Bullet && !_isDie)
	{
		auto playerBullet = dynamic_cast<PlayerBullet*>(obj);
		_HP -= playerBullet->getDamage();
	}

	if (_HP <= 0)
	{
		setState(new BlastDeath(this));
		_isDie = true;
	}
}

void BlastHornet::draw(Camera* camera, RECT r, GVec2 scale, float angle, GVec2 rotate, D3DCOLOR color)
{
	for (auto& bullet : _listBullet)
		bullet->draw(camera, r, scale, angle, rotate, color);

	m_HPBar->draw(_HP, _MaxHP);

	if (_isAllowDraw)
	{
		if (!m_pState->getConfirmMoveUp())
		{
			if (m_Dx < 0) _isReverse = true;
			else _isReverse = false;
		}

		m_pCurrentAnimation->setPosition(this->getPosition());
		m_pCurrentAnimation->setReverse(_isReverse);

		if (camera)
			m_pCurrentAnimation->draw(m_pCurrentAnimation->getPosition(), r, scale, camera->getTrans(), angle, rotate, color);
		else
			m_pCurrentAnimation->draw(m_pCurrentAnimation->getPosition());
	}
}

void BlastHornet::setState(BlastHornetState* new_state)
{
	if (m_currentState == new_state->getState())
		return;

	delete m_pState;
	m_pState = new_state;
	m_currentState = new_state->getState();
	changeAnimation(new_state->getState());
}

void BlastHornet::loadResource()
{
	// Idle
	m_pIdle = new Animation(Define::BLAST_HORNET_IDLE, 1, 4, 96, 96, 0.05f, D3DCOLOR_XRGB(0, 128, 128));
	// Move
	m_pMove = new Animation(Define::BLAST_HORNET_IDLE, 1, 4, 96, 96, 0.05f, D3DCOLOR_XRGB(0, 128, 128));
	// Appear
	m_pAppear = new Animation(Define::BLAST_HORNET_APPEAR, 4, 9, 102, 104, 0.05f, D3DCOLOR_XRGB(0, 128, 128));
	// Attack
	m_pAttack = new Animation(Define::BLAST_HORNET_ATTACK, 4, 9, 102, 104, 0.05f, D3DCOLOR_XRGB(0, 128, 128));
	// Shoot
	m_pShoot = new Animation(Define::BLAST_HORNET_SHOOT, 1, 15, 96, 96, 0.05f, D3DCOLOR_XRGB(0, 128, 128));
	// Death
	m_pDeath = new Animation(Define::EXPLOSIONS, 1, 8, 35, 30, 0.05f);
}

void BlastHornet::changeAnimation(Hornet_State state)
{
	switch (state)
	{
		case eHornet_Appear:
			m_pCurrentAnimation = m_pAppear;
			m_pCurrentAnimation->setLoop(false);
			break;

		case eHornet_Idle:
			m_pCurrentAnimation = m_pIdle;
			m_pCurrentAnimation->setAnimation(0, 4, 0.05f);
			break;

		case eHornet_Attack:
			m_pCurrentAnimation = m_pAttack;
			m_pCurrentAnimation->setLoop(false);
			break;

		case eHornet_Shoot:
			m_pCurrentAnimation = m_pShoot;
			m_pCurrentAnimation->setAnimation(0, 15, 0.05f, false);
			break;

		case eHornet_Move:
			m_pCurrentAnimation = m_pMove;
			m_pCurrentAnimation->setAnimation(0, 4, 0.05f);
			break;

		case eHornet_Death:
			m_pCurrentAnimation = m_pDeath;
			m_pCurrentAnimation->setAnimation(0, 8, 0.05f, false);
			break;

		default:
			break;
	}

	setWidth(m_pCurrentAnimation->getWidth());
	setHeight(m_pCurrentAnimation->getHeight());
}

Animation* BlastHornet::getAnimBlast()
{
	return m_pCurrentAnimation;
}

Player* BlastHornet::getPlayer()
{
	return m_pPlayer;
}

void BlastHornet::setPlayer(Player* val)
{
	m_pPlayer = val;
}

void BlastHornet::setGameMap(GameMap* val)
{
	m_pGameMap = val;
}

float BlastHornet::getDx() const
{
	return m_Dx;
}

float BlastHornet::getDy() const
{
	return m_Dy;
}

float BlastHornet::getDxPos_PosStart() const { return m_DxPos_PosStart; }

float BlastHornet::getDyPos_PosStart() const { return m_DyPos_PosStart; }

float BlastHornet::getTempDxPos_PosStart() const { return m_tempDxPos_PosStart; }

void BlastHornet::setTempDxPos_PosStart(float val) { m_tempDxPos_PosStart = val; }

float BlastHornet::getTempDyPos_PosStart() const { return m_tempDyPos_PosStart; }

void BlastHornet::setTempDyPos_PosStart(float val) { m_tempDyPos_PosStart = val; }
