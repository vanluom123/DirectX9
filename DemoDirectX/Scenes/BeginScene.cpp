#include "BeginScene.h"
#include "../GameDefines/GameDefine.h"
#include "../GameComponents/GameGlobal.h"
#include "../GameComponents/GameCollision.h"
#include "../GameObjects/Player/GameState/DieState/DieState.h"
#include "../GameComponents/Sound.h"

BeginScene::BeginScene()
{
	// BackGround
	_backColor = 0x000000;

	// Initialization and setting the position of AniBackground
	_pAniBackground = new Animation("Resources/Map/BackGround.png", 2, 1, 512, 256);
	_pAniBackground->setPosition(128, 128);
	_pAniBackground->setAnimation(0, 1);

	// Initialization and setting the position of Map
	GameMap::getInstance()->initialize(Define::WORLD_MAP);
	GameMap::getInstance()->loadMap();

	// Initialization and setting the position of Camera
	Camera::getInstance()->initialize(GameGlobal::getInstance()->getWidth(), GameGlobal::getInstance()->getHeight());
	Camera::getInstance()->setPosition(128, 800);

	//Camera::getInstance()->setPosition(825, 900);
	//Camera::getInstance()->setPosition(1670, 420);
	//Camera::getInstance()->setPosition(2245, 1175);
	//Camera::getInstance()->setPosition(2900, 1175);
	//Camera::getInstance()->setPosition(4735, 1175);
	//Camera::getInstance()->setPosition(6000, 1940);
	//Camera::getInstance()->setPosition(7560, 1940);
	//Camera::getInstance()->setPosition(7722.41f, 1940.0f);

	// Setting the position of Player
	Player::getInstance()->setPosition(Camera::getInstance()->getPosition());

	// Other
	_isBoss = false;
	_curentRoom = { 0, 768, 768, 1024 };

	// NEXT ROOM
	_nextRoom = RECT();

	// Clear the list entity out
	_listEntityOut.clear();
	_list000.clear();
}

BeginScene::~BeginScene()
{
	Camera::release();
	QuadTree::release();
	GameCollision::release();
	GameMap::release();
	Sound::release();

	delete _pAniBackground;

	for (int i = 0; i < _list000.size(); i++)
		delete _list000.at(i);

	if (!_list000.empty())
		_list000.clear();

	for (int i = 0; i < _listEntityOut.size(); i++)
		delete _listEntityOut.at(i);

	if (!_listEntityOut.empty())
		_listEntityOut.clear();
}

void BeginScene::update(float dt)
{
	Sound::getInstance()->play("BlastHornet", true, 0);
	Sound::getInstance()->setVolume(90.0f);

	// Getting Object in Camera
	_listEntityOut.clear();
	_listEntityOut.swap(_list000);
	QuadTree::getInstance()->getObjectCamera(_listEntityOut, Camera::getInstance()->getBound());

	//Run KeyBoard play
	Player::getInstance()->KeyBoardEventHandler(_keys, dt);

	// Check collision all Object in Camera
	this->checkCollision(dt);
	Camera::getInstance()->checkViewportWithMapWorld(_isBoss, _curentRoom, _nextRoom, _direction, dt);
	Camera::getInstance()->checkViewportWithEnemies(_listEntityOut);

	// -------Update Object-------

	// Updating Map
	GameMap::getInstance()->update(dt);

	// Updating Player
	Player::getInstance()->update(dt);

	// Updating the list entity out
	for (auto entity : _listEntityOut)
	{
		entity->update(dt);
		if (GameCollision::getInstance()->AABBCheck(entity->getBound(), Camera::getInstance()->getBound()))
			_list000.push_back(entity);
	}

	// Background
	if (Player::getInstance()->getPosition().x > 2600 && Player::getInstance()->getPosition().x < 5632)
		_pAniBackground->setAnimation(1, 1);
	else
		_pAniBackground->setAnimation(0, 1);

	// Update any background
	_pAniBackground->update(dt);
}

void BeginScene::draw()
{
	// Drawing AniBackground
	_pAniBackground->draw();

	// Drawing Map
	GameMap::getInstance()->draw();

	// Drawing Player
	Player::getInstance()->draw(Camera::getInstance());

	// Drawing the list entity out
	for (auto entity : _listEntityOut)
		entity->draw(Camera::getInstance());

	// Drawing Map
	GameMap::getInstance()->draw1();

	// Drawing the HP of Player
	Player::getInstance()->drawHP();
}

void BeginScene::onKeyDown(int keyCode)
{
	_keys[keyCode] = true;
	Player::getInstance()->OnKeyDown(_keys, keyCode);
}

void BeginScene::onKeyUp(int keyCode)
{
	_keys[keyCode] = false;
	Player::getInstance()->OnKeyUp(keyCode);
}

void BeginScene::checkCollision(float dt)
{
	// Check Boss and lock Port
	_isBoss = false;
	for (auto entity : _listEntityOut)
	{
		if (entity->getObjectType() != Enumerator::Object_Type::BOSS)
			continue;

		if (entity->getHP() <= 0)
		{
			for (auto obj : _listEntityOut)
			{
				if (obj->getObjectType() != Enumerator::Object_Type::PORT)
					continue;

				if (obj->getHP() != 1)
					continue;

				//HP = 0 Port is ready
				obj->setHP(0);
				break;
			}

			break;
		}

		_isBoss = true;
		for (auto obj : _listEntityOut)
		{
			if (obj->getObjectType() == Enumerator::Object_Type::PORT)
			{
				if (obj->getHP() == 0)
				{
					//HP = 1 Port closed
					obj->setHP(1);
					break;
				}
			}
		}
	}

	// Player with Object
	this->checkCollision(Player::getInstance(), dt);

	// Player bullet with object
	for (auto playerBullet : Player::getInstance()->getPlayerBullet())
	{
		if (playerBullet->getExplosion())
			continue;

		for (auto entityOut : _listEntityOut)
		{
			this->checkCollision(entityOut, playerBullet, dt);

			// Checking enemy bullet with player bullet
			for (auto enemyBullet : entityOut->getListBullet())
				this->checkCollision(enemyBullet, playerBullet, dt);
		}
	}

	// Object with Object
	for (auto entityOut : _listEntityOut)
	{
		this->checkCollision(entityOut, dt);

		// CheckCollision Enemy and EnemyBullet
		if (entityOut->getObjectType() != Enumerator::Object_Type::ENEMY &&
			entityOut->getObjectType() != Enumerator::Object_Type::BOSS)
			continue;

		for (auto enemyBullet : entityOut->getListBullet())
		{
			if (enemyBullet->IsDestroy())
				continue;

			if (enemyBullet->getObjectType() == Enumerator::Object_Type::ITEM)
			{
				this->checkCollision(enemyBullet, dt);
				this->checkCollision(Player::getInstance(), enemyBullet, dt);
				continue;
			}

			this->checkCollision(Player::getInstance(), enemyBullet, dt);

			vector<BaseObject *> listStaticEntity;
			QuadTree::getInstance()->getObjectCollide(listStaticEntity, enemyBullet->getBound());

			for (auto staticEntity : listStaticEntity)
				this->checkCollision(staticEntity, enemyBullet, dt);
		}
	}
}

void BeginScene::checkCollision(BaseObject * obj, float dt)
{
	for (auto entityOut : _listEntityOut)
	{
		if (obj->getId() != entityOut->getId())
			this->checkCollision(obj, entityOut, dt);
	}

	vector<BaseObject *> listEntityStatic;
	QuadTree::getInstance()->getObjectCollide(listEntityStatic, obj->getBound());

	for (auto entityStatic : listEntityStatic)
	{
		if (obj->getId() == entityStatic->getId())
			continue;

		if (obj->IsDestroy() ||
			entityStatic->IsDestroy())
			continue;

		auto distance = GameCollision::getInstance()->Distance(obj, entityStatic, dt);
		auto broad = GameCollision::getInstance()->getBroadphase(obj->getBound(), distance);

		if (GameCollision::getInstance()->AABBCheck(broad, entityStatic->getBound()))
		{
			if (!GameCollision::getInstance()->isNested(obj->getBound(), entityStatic->getBound()))
			{
				Side_Collision side = Side_Collision::NONE;
				float colTime = GameCollision::getInstance()->sweptAABB(obj->getBound(), entityStatic->getBound(), distance, side);
				if (colTime < 1.0f)
					obj->checkTimeCollision(colTime, side, entityStatic);
			}
		}
	}
}

void BeginScene::checkCollision(BaseObject * obj, BaseObject * other, float dt)
{
	if (obj->IsDestroy() || other->IsDestroy())
		return;

	GVec2 distance = GameCollision::getInstance()->Distance(obj, other, dt);
	RECT broad = GameCollision::getInstance()->getBroadphase(obj->getBound(), distance);

	if (GameCollision::getInstance()->AABBCheck(broad, other->getBound()))
	{
		if (GameCollision::getInstance()->isNested(obj->getBound(), other->getBound()))
		{
			obj->onCollision(other);
			other->onCollision(obj);
		}
		else
		{
			Side_Collision side = Side_Collision::NONE;
			float colTime = GameCollision::getInstance()->sweptAABB(obj->getBound(), other->getBound(), distance, side);
			if (colTime < 1.0f)
			{
				obj->onCollision(other);
				other->onCollision(obj);
			}
		}
	}
}