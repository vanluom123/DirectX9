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
	_pCamera = new Camera(GameGlobal::getWidth(), GameGlobal::getHeight());
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
	GameGlobal::getKeyboard()->releaseKeyboard();
}

void BeginScene::update(float dt)
{
	// Getting status of keyboard
	GameGlobal::getKeyboard()->getKeyState();

	Sound::getInstance()->play("BlastHornet", true, 0);
	Sound::getInstance()->setVolume(90.0f);

	// Getting Object in Camera
	_listEntityOut.clear();
	_listEntityOut.swap(_list000);
	_pMap->getQuadTree()->getObjectCamera(_listEntityOut, _pCamera->getBound());

	//Run KeyBoard play
	_pPlayer->KeyBoardEventHandler(_keys, dt);

	// Check collision all Object in Camera
	checkCollision(dt);
	checkCameraAndWorldMap(dt);
	checkCameraAndEnemies();

	// -------Update Object-------

	// Updating Map
	_pMap->update(dt);

	// Updating Player
	_pPlayer->update(dt);

	// Updating the list entity out
	for (auto& entity : _listEntityOut)
	{
		entity->update(dt);
		bool isColl_Entity_Camera = GameCollision::isCollision(entity->getBound(), _pCamera->getBound());
		if (isColl_Entity_Camera)
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
	for (auto& entity : _listEntityOut)
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
	if (_isBoss)
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

	bool isPointColl_Player_CurrentRoom = GameCollision::pointCollision(_pPlayer->getPosition().x, _pPlayer->getPosition().y, _curentRoom);
	if (!isPointColl_Player_CurrentRoom)
	{
		bool noRoom = true;
		for (auto& Room : _pMap->getListRoom())
		{
			bool isPointColl_Player_Room = GameCollision::pointCollision(_pPlayer->getPosition().x, _pPlayer->getPosition().y, Room);
			if (isPointColl_Player_Room)
			{
				noRoom = false;
				_nextRoom = Room;
				_curentRoom = Room;

				float dxPlayerCurrentRoom = _pPlayer->getPosition().x - (_curentRoom.left + (_curentRoom.right - _curentRoom.left) / 2);
				if (dxPlayerCurrentRoom < 0)
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
		if (noRoom)
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
	for (auto& entity : _listEntityOut)
	{
		if (entity->getObjectType() == eObject_Enemy)
		{
			if (_pPlayer->getPosition().x > entity->getPosition().x)
				entity->setReverse(true);
			else
				entity->setReverse(false);

			bool isCollCameraWithEntity = GameCollision::isCollision(_pCamera->getBound(), entity->getBound());
			bool isPointCollCameraWithEntity = GameCollision::pointCollision(entity->getPositionStart().x, entity->getPositionStart().y, _pCamera->getBound());
			if (!(isCollCameraWithEntity || isPointCollCameraWithEntity))
				entity->newObject();
		}
	}
}

void BeginScene::checkCollision(float dt)
{
	// Check Boss and lock Port
	_isBoss = false;
	for (auto& entity : _listEntityOut)
	{
		if (entity->getObjectType() == eObject_Boss)
		{
			if (entity->getHP() > 0)
			{
				_isBoss = true;
				for (auto& obj : _listEntityOut)
				{
					if (obj->getObjectType() == eObject_Port)
					{
						if (obj->getHP() == 0)
						{
							obj->setHP(1);//HP = 1 Port closed
							break;
						}
					}
				}
			}
			else
			{
				for (auto& obj : _listEntityOut)
				{
					if (obj->getObjectType() == eObject_Port)
					{
						if (obj->getHP() == 1)
						{
							obj->setHP(0);//HP = 0 Port is ready
							break;
						}
					}
				}
			}
			break;
		}
	}

	// Player with Object
	checkCollision(_pPlayer, dt);
	for (auto& playerBullet : *_pPlayer->getPlayerBullet())
	{
		if (playerBullet->getExplosion())
			continue;

		for (auto& entity : _listEntityOut)
		{
			checkCollision(entity, playerBullet, dt);
			
			// Checking enemy bullet with player bullet
			for (auto& enemyBullet : *entity->getListBullet())
				checkCollision(enemyBullet, playerBullet, dt);
		}
	}

	// Object with Object
	for (auto& entity : _listEntityOut)
	{
		checkCollision(entity, dt);

		// CheckCollision Enemy and EnemyBullet
		if (entity->getObjectType() == eObject_Enemy || entity->getObjectType() == eObject_Boss)
		{
			for (auto& bullet : *entity->getListBullet())
			{
				if (bullet->getDie())
					continue;

				if (bullet->getObjectType() == eObject_Item)
				{
					checkCollision(bullet, dt);
					checkCollision(_pPlayer, bullet, dt);
					continue;
				}

				checkCollision(_pPlayer, bullet, dt);

				std::vector<BaseObject*> listStaticEntity;
				_pMap->getQuadTree()->getObjectCollide(listStaticEntity, bullet->getBound());

				for (auto& obj : listStaticEntity)
					checkCollision(obj, bullet, dt);
			}
		}
	}
}

void BeginScene::checkCollision(BaseObject* obj, float dt)
{
	for (auto& entity : _listEntityOut)
	{
		if (obj->getId() != entity->getId())
			checkCollision(obj, entity, dt);
	}

	std::vector<BaseObject*> listEntityStatic;
	_pMap->getQuadTree()->getObjectCollide(listEntityStatic, obj->getBound());

	for (auto& entity : listEntityStatic)
	{
		if (obj->getId() != entity->getId())
		{
			if (obj->getDie() || entity->getDie())
				continue;

			GVec2 distance = GameCollision::Distance(obj, entity, dt);
			RECT broad = GameCollision::getBroadphase(obj->getBound(), distance);

			bool isColl_Broad_Entity = GameCollision::isCollision(broad, entity->getBound());
			if (isColl_Broad_Entity)
			{
				Side_Collision other_with_entity;
				float collision_time = GameCollision::sweptAABB(obj->getBound(), entity->getBound(), distance, other_with_entity);

				if (collision_time < 1.0f)
					obj->checkTimeCollision(collision_time, other_with_entity, entity);
			}
		}
	}
}

void BeginScene::checkCollision(BaseObject* obj, BaseObject* other, float dt)
{
	if (obj->getDie() || other->getDie())
		return;

	GVec2 distance = GameCollision::Distance(obj, other, dt);
	RECT broad = GameCollision::getBroadphase(obj->getBound(), distance);

	bool isColl_Broad_Other = GameCollision::isCollision(broad, other->getBound());
	if (isColl_Broad_Other)
	{
		bool isColl_Obj_Other = GameCollision::isCollision(obj->getBound(), other->getBound());
		if (isColl_Obj_Other)
		{
			obj->onCollision(other);
			other->onCollision(obj);
			return;
		}

		Side_Collision other_with_entity;
		float collision_time = GameCollision::sweptAABB(obj->getBound(), other->getBound(), distance, other_with_entity);

		if (collision_time < 1.0f)
		{
			obj->onCollision(other);
			other->onCollision(obj);
		}
	}
}