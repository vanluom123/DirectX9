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
	_pMap = new GameMap(Define::WORLD_MAP);
	_pPlayer = new Player();
	_pMap->setPlayer(_pPlayer);
	_pMap->loadMap();

	// Initialization and setting the position of Camera
	_pCamera = new Camera(GameGlobal::getInstance()->getWidth(), GameGlobal::getInstance()->getHeight());
	_pCamera->setPosition(128, 800);

	//_pCamera->setPosition(825, 900);
	//_pCamera->setPosition(1670, 420);
	//_pCamera->setPosition(2245, 1175);
	//_pCamera->setPosition(2900, 1175);
	//_pCamera->setPosition(4735, 1175);
	//_pCamera->setPosition(6000, 1940);
	//_pCamera->setPosition(7560, 1940);

	//_pCamera->setPosition(7722.41f, 1940.0f);
	_pMap->setViewport(_pCamera);

	// Setting the position of Player
	_pPlayer->setPosition(_pCamera->getPosition());

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
	delete _pMap;
	delete _pCamera;
	delete _pPlayer;
	delete _pAniBackground;

	GameCollision::release();
}

void BeginScene::update(float dt)
{
	Sound::getInstance()->play("BlastHornet", true, 0);
	Sound::getInstance()->setVolume(90.0f);

	// Getting Object in Camera
	_listEntityOut.clear();
	_listEntityOut.swap(_list000);
	_pMap->getQuadTree()->getObjectCamera(_listEntityOut, _pCamera->getBound());

	//Run KeyBoard play
	_pPlayer->KeyBoardEventHandler(_keys, dt);

	// Check collision all Object in Camera
	this->checkCollision(dt);
	this->checkCameraAndWorldMap(dt);
	this->checkCameraAndEnemies();

	// -------Update Object-------

	// Updating Map
	_pMap->update(dt);

	// Updating Player
	_pPlayer->update(dt);

	// Updating the list entity out
	for (auto entity : _listEntityOut)
	{
		entity->update(dt);
		if (GameCollision::getInstance()->AABBCheck(entity->getBound(), _pCamera->getBound()) == true)
			_list000.push_back(entity);
	}

	// Background
	if (_pPlayer->getPosition().x > 2600 && _pPlayer->getPosition().x < 5632)
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
	_pMap->draw();

	// Drawing Player
	_pPlayer->draw(_pCamera);

	// Drawing the list entity out
	for (auto entity : _listEntityOut)
		entity->draw(_pCamera);

	// Drawing Map
	_pMap->draw1();

	// Drawing the HP of Player
	_pPlayer->drawHP();
}

void BeginScene::onKeyDown(int keyCode)
{
	_keys[keyCode] = true;
	_pPlayer->OnKeyDown(_keys, keyCode);
}

void BeginScene::onKeyUp(int keyCode)
{
	_keys[keyCode] = false;
	_pPlayer->OnKeyUp(keyCode);
}

void BeginScene::checkCameraAndWorldMap(float dt)
{
	if (_isBoss == true)
	{
		if (_pPlayer->getBound().left < _pCamera->getBound().left)
		{
			if (_pPlayer->getVx() < 0)
				_pPlayer->setVx(0.0f);
		}
		else
		{
			if (_pPlayer->getBound().right > _curentRoom.right)
			{
				if (_pPlayer->getVx() > 0)
					_pPlayer->setVx(0.0f);
			}
		}
	}

	if (GameCollision::getInstance()->pointCollision(_pPlayer->getPosition().x, _pPlayer->getPosition().y, _curentRoom) == false)
	{
		bool noRoom = true;
		for (auto Room : _pMap->getListRoom())
		{
			if (GameCollision::getInstance()->pointCollision(_pPlayer->getPosition().x, _pPlayer->getPosition().y, Room) == true)
			{
				noRoom = false;
				_nextRoom = Room;
				_curentRoom = Room;

				auto centerX = _curentRoom.left + (_curentRoom.right - _curentRoom.left) / 2;
				if (_pPlayer->getPosition().x < centerX)
				{
					if (_pCamera->getBound().left < _curentRoom.left)
					{
						_direction = 1;
						_curentRoom.left = _pCamera->getBound().left;
					}
				}
				else
				{
					if (_pCamera->getBound().right > _curentRoom.right)
					{
						_direction = -1;
						_curentRoom.right = _pCamera->getBound().right;
					}
				}
				break;
			}
		}
		if (noRoom == true)
			_pPlayer->setState(new DieState(_pPlayer));
	}

	if (_direction == 1)
	{
		_curentRoom.left += 300 * dt;
		if (_curentRoom.left >= _nextRoom.left)
		{
			_curentRoom.left = _nextRoom.left;
			_direction = 0;
		}
	}
	else if (_direction == -1)
	{
		_curentRoom.right -= 300 * dt;
		if (_curentRoom.right <= _nextRoom.right)
		{
			_curentRoom.right = _nextRoom.right;
			_direction = 0;
		}
	}
	else
	{
		// Setting the position of Camera to the position of Player
		// When Player moved, Camera moved to Player
		_pCamera->setPosition(_pPlayer->getPosition());
	}

	if (_pCamera->getBound().left < _curentRoom.left)
		_pCamera->setPosition(_curentRoom.left + _pCamera->getWidth() / 2, _pCamera->getPosition().y);
	else if (_pCamera->getBound().right > _curentRoom.right)
		_pCamera->setPosition(_curentRoom.right - _pCamera->getWidth() / 2, _pCamera->getPosition().y);

	if (_pCamera->getBound().top < _curentRoom.top)
		_pCamera->setPosition(_pCamera->getPosition().x, _curentRoom.top + _pCamera->getHeight() / 2);
	else if (_pCamera->getBound().bottom > _curentRoom.bottom)
		_pCamera->setPosition(_pCamera->getPosition().x, _curentRoom.bottom - _pCamera->getHeight() / 2);
}

void BeginScene::checkCameraAndEnemies()
{
	for (auto entityOut : _listEntityOut)
	{
		if (entityOut->getObjectType() != Enumerator::Object_Type::ENEMY)
			continue;

		bool isReverse = (_pPlayer->getPosition().x > entityOut->getPosition().x) ? true : false;
		entityOut->setReverse(isReverse);

		if (GameCollision::getInstance()->AABBCheck(_pCamera->getBound(), entityOut->getBound()) == false
			&& GameCollision::getInstance()->pointCollision(entityOut->getPositionStart().x, entityOut->getPositionStart().y, _pCamera->getBound()) == false)
			entityOut->newObject();
	}
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
	this->checkCollision(_pPlayer, dt);

	// Player bullet with object
	for (auto playerBullet : _pPlayer->getPlayerBullet())
	{
		if (playerBullet->getExplosion() == true)
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
		if (entityOut->getObjectType() != Enumerator::Object_Type::ENEMY && entityOut->getObjectType() != Enumerator::Object_Type::BOSS)
			continue;

		for (auto enemyBullet : entityOut->getListBullet())
		{
			if (enemyBullet->IsDestroy() == true)
				continue;

			if (enemyBullet->getObjectType() == Enumerator::Object_Type::ITEM)
			{
				this->checkCollision(enemyBullet, dt);
				this->checkCollision(_pPlayer, enemyBullet, dt);
				continue;
			}

			this->checkCollision(_pPlayer, enemyBullet, dt);

			vector<BaseObject*> listStaticEntity;
			_pMap->getQuadTree()->getObjectCollide(listStaticEntity, enemyBullet->getBound());

			for (auto staticEntity : listStaticEntity)
				this->checkCollision(staticEntity, enemyBullet, dt);
		}
	}
}

void BeginScene::checkCollision(BaseObject* obj, float dt)
{
	for (auto entityOut : _listEntityOut)
	{
		if (obj->getId() != entityOut->getId())
			this->checkCollision(obj, entityOut, dt);
	}

	vector<BaseObject*> listEntityStatic;
	_pMap->getQuadTree()->getObjectCollide(listEntityStatic, obj->getBound());

	float colTime = 1.0f;
	Side_Collision side = Side_Collision::NONE;
	GVec2 distance = Gvec2Zero;
	RECT broad = RECT();

	for (auto entityStatic : listEntityStatic)
	{
		if (obj->getId() == entityStatic->getId())
			continue;

		if (obj->IsDestroy() == true || entityStatic->IsDestroy() == true)
			continue;

		distance = GameCollision::getInstance()->Distance(obj, entityStatic, dt);
		broad = GameCollision::getInstance()->getBroadphase(obj->getBound(), distance);

		if (GameCollision::getInstance()->AABBCheck(broad, entityStatic->getBound()) == true)
		{
			colTime = GameCollision::getInstance()->sweptAABB(obj->getBound(), entityStatic->getBound(), distance, side);
			if (colTime < 1.0f)
				obj->checkTimeCollision(colTime, side, entityStatic);
		}
	}
}

void BeginScene::checkCollision(BaseObject* obj, BaseObject* other, float dt)
{
	if (obj->IsDestroy() == true || other->IsDestroy() == true)
		return;

	GVec2 distance = GameCollision::getInstance()->Distance(obj, other, dt);
	RECT broad = GameCollision::getInstance()->getBroadphase(obj->getBound(), distance);

	float colTime = 1.0f;
	Side_Collision side = Side_Collision::NONE;

	if (GameCollision::getInstance()->AABBCheck(broad, other->getBound()) == true)
	{
		if (GameCollision::getInstance()->AABBCheck(obj->getBound(), other->getBound()) == true)
		{
			obj->onCollision(other);
			other->onCollision(obj);
		}
		else
		{
			colTime = GameCollision::getInstance()->sweptAABB(obj->getBound(), other->getBound(), distance, side);
			if (colTime < 1.0f)
			{
				obj->onCollision(other);
				other->onCollision(obj);
			}
		}
	}
}