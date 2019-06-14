#include "Blast.h"
#include "BlastDeath.h"
#include "BlastStand.h"
#include "BlastAppear.h"
#include "../../../GameDefines/GameDefine.h"

Blast::Blast()
{
	loadResource();

	_objectType = eObjectType::BOSS;
	_MaxHP = 30;
	_Damage = 3;
	_HP = _MaxHP;
	_currentState = eBlastState::BLAST_STATE_UNKNOWN;
	_HPBar = new HPBar(_objectType);

	_data = new BlastData;
	_data->blast = this;
	_data->state = nullptr;

	setState(new BlastAppear(_data));
	setWidth(_animation[_currentState]->getWidth());
	setHeight(_animation[_currentState]->getHeight());
}


Blast::~Blast()
{
	for (auto& it = _animation.begin(); it != _animation.end(); ++it)
		delete it->second;
	if (!_animation.empty())
		_animation.clear();

	delete _data;

	for (auto& i : _listBullet)
		delete i;
	if (!_listBullet.empty())
		_listBullet.clear();
}

RECT Blast::getBound()
{
	RECT bound;
	bound.left = _posX - 20;
	bound.right = _posX + 30;
	bound.top = _posY - 30;
	bound.bottom = _posY + 45;
	return bound;
}

void Blast::update(float dt)
{
	for (auto& bullet : _listBullet)
		bullet->update(dt);

	if (_isAllowDraw)
	{
		_animation[_currentState]->update(dt);

		BaseObject::update(dt);

		switch (_currentState)
		{
		case eBlastState::BLAST_STATE_APPEAR:
			break;
		case eBlastState::BLAST_STATE_STAND:
			break;
		case eBlastState::BLAST_STATE_ATTACK:
			break;
		case eBlastState::BLAST_STATE_SHOOT:
			break;
		case eBlastState::BLAST_STATE_SINE_MOVEMENT:
			break;
		case eBlastState::BLAST_STATE_DEATH:
			break;
		case eBlastState::BLAST_STATE_UNKNOWN:
			break;
		default:
			break;
		}
	}
}

void Blast::onCollision(eSideCollision side)
{
	switch (_currentState)
	{
	case eBlastState::BLAST_STATE_APPEAR:
		break;
	case eBlastState::BLAST_STATE_STAND:
		break;
	case eBlastState::BLAST_STATE_ATTACK:
		break;
	case eBlastState::BLAST_STATE_SHOOT:
		break;
	case eBlastState::BLAST_STATE_SINE_MOVEMENT:
		break;
	case eBlastState::BLAST_STATE_DEATH:
		break;
	case eBlastState::BLAST_STATE_UNKNOWN:
		break;
	default:
		break;
	}
}

void Blast::onCollision(BaseObject* obj)
{
	if (obj->getObjectType() == eObjectType::ROCK_MAN_BULLET && !_isDie)
	{
		_HP -= 1 + obj->getDamage() / 2;

		if (_HP <= 0)
		{
			setState(new BlastDeath(_data));
			_isDie = true;
		}
	}
}

void Blast::draw(Camera* camera, RECT r, GVec2 scale, float angle, GVec2 rotate, D3DCOLOR color)
{
	for (auto& i : _listBullet)
		i->draw(camera, r, scale, angle, rotate, color);

	_HPBar->draw(_HP, _MaxHP);

	if (_isAllowDraw)
	{
		_animation[_currentState]->setPosition(getPosition());
		_animation[_currentState]->setReverse(_isReverse);
		if (camera)
			_animation[_currentState]->draw(_animation[_currentState]->getPosition(), r, scale, camera->getTrans(), angle, rotate, color);
		else
			_animation[_currentState]->draw(_animation[_currentState]->getPosition());
	}
}

void Blast::setState(BlastState* state)
{
	if (_currentState != state->getState())
	{
		_currentState = state->getState();
		SAFE_DELETE(_data->state);
		_data->state = state;
	}
}

void Blast::changeAnimation(eBlastState state)
{
	switch (state)
	{
	case eBlastState::BLAST_STATE_APPEAR:
	{
		_pAnim = new Animation("Resources/Enemies/BlastHornet/State/Appear/AppearSpriteSheet.png", 4, 9, 102, 104, 0.05f, D3DCOLOR_XRGB(0, 128, 128));
	}
	break;

	case eBlastState::BLAST_STATE_SINE_MOVEMENT:
	case eBlastState::BLAST_STATE_STAND:
	{
		_pAnim = new Animation("Resources/Enemies/BlastHornet/State/Stand/standspritesheet.png", 1, 4, 96, 96, 0.05f, D3DCOLOR_XRGB(0, 128, 128));
		_pAnim->setAnimation(0, 4, 0.05f);
	}
	break;

	case eBlastState::BLAST_STATE_ATTACK:
	{
		_pAnim = new Animation("Resources/Enemies/BlastHornet/State/Attack/attackspritesheet.png", 4, 9, 102, 104, 0.05f, D3DCOLOR_XRGB(0, 128, 128));
	}
	break;

	case eBlastState::BLAST_STATE_SHOOT:
	{
		_pAnim = new Animation("Resources/Enemies/BlastHornet/State/Shooter/shooterspirtesheet.png", 1, 15, 96, 96, 0.05f, D3DCOLOR_XRGB(0, 128, 128));
		_pAnim->setAnimation(0, 15, 0.05f, false);
	}
	break;

	case eBlastState::BLAST_STATE_DEATH:
	{
		_pAnim = new Animation(Define::EXPLOSIONS, 1, 8, 35, 30, 0.05f);
		_pAnim->setAnimation(0, 8, 0.05f, false);
	}
	break;

	default:
		break;
	}

	setWidth(_pAnim->getWidth());
	setHeight(_pAnim->getHeight());
}

void Blast::loadResource()
{
	_animation[eBlastState::BLAST_STATE_STAND] = new Animation("Resources/Enemies/BlastHornet/State/Stand/standspritesheet.png", 1, 4, 96, 96, 0.05f, D3DCOLOR_XRGB(0, 128, 128));
	_animation[eBlastState::BLAST_STATE_STAND]->setAnimation(0, 4, 0.05f);

	_animation[eBlastState::BLAST_STATE_APPEAR] = new Animation("Resources/Enemies/BlastHornet/State/Appear/AppearSpriteSheet.png", 4, 9, 102, 104, 0.05f, D3DCOLOR_XRGB(0, 128, 128));

	_animation[eBlastState::BLAST_STATE_ATTACK] = new Animation("Resources/Enemies/BlastHornet/State/Attack/attackspritesheet.png", 4, 9, 102, 104, 0.05f, D3DCOLOR_XRGB(0, 128, 128));

	_animation[eBlastState::BLAST_STATE_SHOOT] = new Animation("Resources/Enemies/BlastHornet/State/Shooter/shooterspirtesheet.png", 1, 15, 96, 96, 0.05f, D3DCOLOR_XRGB(0, 128, 128));
	_animation[eBlastState::BLAST_STATE_SHOOT]->setAnimation(0, 15, 0.05f, false);

	_animation[eBlastState::BLAST_STATE_DEATH] = new Animation(Define::EXPLOSIONS, 1, 8, 35, 30, 0.05f);
	_animation[eBlastState::BLAST_STATE_DEATH]->setAnimation(0, 8, 0.05f, false);
}

std::vector<BlastBullet*>* Blast::getListBullet()
{
	return &_listBullet;
}

Animation* Blast::getAnimation(eBlastState e)
{
	Animation* anim = _animation.find(e)->second;
	return new Animation(*anim);
}
