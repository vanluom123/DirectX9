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
	_pAniBackground->SetPosition(128, 128);
	_pAniBackground->SetAnimation(0, 1);

	// Initialization and setting the position of Map
	_pMap = new GameMap(Define::WORLD_MAP);
	_pPlayer = new Player();
	_pMap->SetPlayer(_pPlayer);
	_pMap->LoadMap();

	// Initialization and setting the position of Camera
	_pCamera = new Camera(GameGlobal::GetWidth(), GameGlobal::GetHeight());
	_pCamera->SetPosition(128, 800);

	//_pCamera->SetPosition(825, 900);
	//_pCamera->SetPosition(1670, 420);
	//_pCamera->SetPosition(2245, 1175);
	//_pCamera->SetPosition(2900, 1175);
	//_pCamera->SetPosition(4735, 1175);
	//_pCamera->SetPosition(6000, 1940);
	//_pCamera->SetPosition(7560, 1940);
	_pMap->SetCamera(_pCamera);

	// Setting the position of Player
	_pPlayer->SetPosition(_pCamera->GetPosition());

	// Other
	_isboss = false;
	_curentRoom = { 0, 768, 768, 1024 };

	// NEXT ROOM
	_nextRoom = RECT();

	// Clear the list entity out
	_listEntityOut.clear();
	_list000.clear();
}

BeginScene::~BeginScene()
{
	SAFE_DELETE(_pMap);
	SAFE_DELETE(_pCamera);
	SAFE_DELETE(_pPlayer);
	SAFE_DELETE(_pAniBackground);
}

void BeginScene::Update(float dt)
{
	Sound::GetInstance()->Play("BlastHornet", true, 0);
	Sound::GetInstance()->SetVolume(90);

	// Getting Object in Camera
	_listEntityOut.clear();
	_listEntityOut.swap(_list000);
	_pMap->GetQuadTree()->GetObjectCamera(_listEntityOut, _pCamera->GetBound());

	//Run KeyBoard play
	_pPlayer->KeyBoardEventHandler(_keys, dt);

	// Check collision all Object in Camera
	CheckCollision(dt);
	CheckCameraAndWorldMap(dt);
	CheckCameraAndEnemies();

	// -------Update Object-------

	// Updating Map
	_pMap->Update(dt);

	// Updating Player
	_pPlayer->Update(dt);

	// Updating the list entity out
	for (auto& entity : _listEntityOut)
	{
		entity->Update(dt);
		if (GameCollision::IsCollision(entity->GetBound(), _pCamera->GetBound()) == true)
			_list000.push_back(entity);
	}

	// Background
	if (_pPlayer->GetPosition().x > 2600 && _pPlayer->GetPosition().x < 5632)
		_pAniBackground->SetAnimation(1, 1);
	else
		_pAniBackground->SetAnimation(0, 1);

	// Update any background
	_pAniBackground->Update(dt);
}

void BeginScene::Draw()
{
	// Drawing AniBackground
	_pAniBackground->Draw();
	
	// Drawing Map
	_pMap->Draw();

	// Drawing Player
	_pPlayer->Draw(_pCamera);

	// Drawing the list entity out
	for (auto& entity : _listEntityOut)
		entity->Draw(_pCamera);

	// Drawing Map
	_pMap->Draw1();

	// Drawing the HP of Player
	_pPlayer->DrawHP();
}

void BeginScene::OnKeyDown(int keyCode)
{
	_keys[keyCode] = true;
	_pPlayer->OnKeyDown(_keys, keyCode);
}

void BeginScene::OnKeyUp(int keyCode)
{
	_keys[keyCode] = false;
	_pPlayer->OnKeyUp(keyCode);
}

void BeginScene::CheckCameraAndWorldMap(float dt)
{
	if (_isboss == true)
	{
		if (_pPlayer->GetBound().left < _pCamera->GetBound().left)
		{
			if (_pPlayer->GetVx() < 0)
				_pPlayer->SetVx(0);
		}
		else
		{
			if (_pPlayer->GetBound().right > _curentRoom.right)
			{
				if (_pPlayer->GetVx() > 0)
					_pPlayer->SetVx(0);
			}
		}
	}
	if (!GameCollision::PointCollision(_pPlayer->GetPosition().x, _pPlayer->GetPosition().y, _curentRoom))
	{
		bool noRoom = true;
		for (auto& Room : _pMap->GetListRoom())
			if (GameCollision::PointCollision(_pPlayer->GetPosition().x, _pPlayer->GetPosition().y, Room))
			{
				noRoom = false;
				_nextRoom = Room;
				_curentRoom = Room;
				if (_pPlayer->GetPosition().x < (_curentRoom.left + (_curentRoom.right - _curentRoom.left) / 2))
				{
					if (_pCamera->GetBound().left < _curentRoom.left)
					{
						_direction = 1;
						_curentRoom.left = _pCamera->GetBound().left;
					}
				}
				else if (_pPlayer->GetPosition().x > (_curentRoom.left + (_curentRoom.right - _curentRoom.left) / 2))
				{
					if (_pCamera->GetBound().right > _curentRoom.right)
					{
						_direction = -1;
						_curentRoom.right = _pCamera->GetBound().right;
					}
				}
				break;
			}
		if (noRoom)
			_pPlayer->SetState(new DieState(_pPlayer->GetPlayerData()));
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
		_pCamera->SetPosition(_pPlayer->GetPosition());
	}

	if (_pCamera->GetBound().left < _curentRoom.left)
		_pCamera->SetPosition(_curentRoom.left + _pCamera->GetWidth() / 2, _pCamera->GetPosition().y);
	else if (_pCamera->GetBound().right > _curentRoom.right)
		_pCamera->SetPosition(_curentRoom.right - _pCamera->GetWidth() / 2, _pCamera->GetPosition().y);

	if (_pCamera->GetBound().top < _curentRoom.top)
		_pCamera->SetPosition(_pCamera->GetPosition().x, _curentRoom.top + _pCamera->GetHeight() / 2);
	else if (_pCamera->GetBound().bottom > _curentRoom.bottom)
		_pCamera->SetPosition(_pCamera->GetPosition().x, _curentRoom.bottom - _pCamera->GetHeight() / 2);
}

void BeginScene::CheckCameraAndEnemies()
{
	for (auto& entity : _listEntityOut)
	{
		if (entity->GetObjectType() == BaseObject::ENEMY)
		{
			if (_pPlayer->GetPosition().x > entity->GetPosition().x)
				entity->SetReverse(true);
			else
				entity->SetReverse(false);

			if (!GameCollision::IsCollision(_pCamera->GetBound(), entity->GetBound())
				&& !GameCollision::PointCollision(entity->GetPositionStart().x, entity->GetPositionStart().y, _pCamera->GetBound()))
			{
				entity->NewEntity();
			}
		}
	}
}

void BeginScene::CheckCollision(float dt)
{
	// Check Boss and lock Port
	_isboss = false;
	for (auto& entity : _listEntityOut)
	{
		if (entity->GetObjectType() == BaseObject::BOSS)
		{
			if (entity->GetHP() > 0)
			{
				_isboss = true;
				for (auto& obj : _listEntityOut)
				{
					if (obj->GetObjectType() == BaseObject::PORT)
					{
						if (obj->GetHP() == 0)
						{
							obj->SetHP(1);//HP = 1 Port closed
							break;
						}
					}
				}
			}
			else
			{
				for (auto& obj : _listEntityOut)
				{
					if (obj->GetObjectType() == BaseObject::PORT)
					{
						if (obj->GetHP() == 1)
						{
							obj->SetHP(0);//HP = 0 Port is ready
							break;
						}
					}
				}
			}
			break;
		}
	}

	// Player with Object
	CheckCollision(_pPlayer, dt);
	for (auto& playerBullet : (*_pPlayer->GetPlayerBullet()))
	{
		if (playerBullet->GetExplosion())
			continue;
		for (auto& entity : _listEntityOut)
			CheckCollision(entity, playerBullet, dt);
	}

	// Object with Object
	for (auto& entity : _listEntityOut)
	{
		CheckCollision(entity, dt);

		// CheckCollision Enemy and EnemyBullet
		if (entity->GetObjectType() == BaseObject::ENEMY || entity->GetObjectType() == BaseObject::BOSS)
		{
			for (auto& bullet : *entity->GetListBullet())
			{
				if (bullet->GetDie())
					continue;

				if (bullet->GetObjectType() == BaseObject::ITEM)
				{
					CheckCollision(bullet, dt);
					CheckCollision(_pPlayer, bullet, dt);
					continue;
				}

				CheckCollision(_pPlayer, bullet, dt);

				std::vector<BaseObject*> listEntityStatic;
				_pMap->GetQuadTree()->GetObjectCollide(listEntityStatic, bullet->GetBound());

				for (auto& obj : listEntityStatic)
				{
					CheckCollision(obj, bullet, dt);
				}
			}
		}
	}
}

void BeginScene::CheckCollision(BaseObject * obj, float dt)
{
	for (auto& entity : _listEntityOut)
	{
		if (obj->GetId() != entity->GetId())
			CheckCollision(obj, entity, dt);
	}

	std::vector<BaseObject*> listEntityStatic;
	_pMap->GetQuadTree()->GetObjectCollide(listEntityStatic, obj->GetBound());

	for (auto& entity : listEntityStatic)
	{
		if (obj->GetId() != entity->GetId())
		{
			if (obj->GetDie() || entity->GetDie())
				continue;

			GVec2 distance = GameCollision::Distance(obj, entity, dt);
			RECT broad = GameCollision::GetBroad(obj->GetBound(), distance);

			if (GameCollision::IsCollision(broad, entity->GetBound()))
			{
				BaseObject::eSideCollision other_with_entity;
				float collision_time = GameCollision::SweptAABB(obj->GetBound(), entity->GetBound(), distance, other_with_entity);

				if (collision_time < 1.0f)
					obj->CheckTimeCollision(collision_time, other_with_entity, entity);
			}
		}
	}
}

void BeginScene::CheckCollision(BaseObject * obj, BaseObject * other, float dt)
{
	if (obj->GetDie() || other->GetDie())
		return;

	GVec2 distance = GameCollision::Distance(obj, other, dt);
	RECT broad = GameCollision::GetBroad(obj->GetBound(), distance);

	if (GameCollision::IsCollision(broad, other->GetBound()))
	{
		if (GameCollision::IsCollision(obj->GetBound(), other->GetBound()))
		{
			obj->OnCollision(other);
			other->OnCollision(obj);
			return;
		}
		BaseObject::eSideCollision other_with_entity;
		float collision_time = GameCollision::SweptAABB(obj->GetBound(), other->GetBound(), distance, other_with_entity);

		if (collision_time < 1.0f)
		{
			obj->OnCollision(other);
			other->OnCollision(obj);
		}
	}
}