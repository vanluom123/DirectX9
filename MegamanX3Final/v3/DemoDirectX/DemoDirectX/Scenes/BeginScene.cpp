#include "BeginScene.h"
#include "../GameDefines/GameDefine.h"
#include "../GameComponents/GameGlobal.h"
#include "../GameComponents/GameCollision.h"
#include "../GameObjects/Player/GameState/DieState/DieState.h"
#include "../GameComponents/Sound.h"

BeginScene::BeginScene()
{
	// BackGround
	m_backColor = 0x000000;

	// Initialization and setting the position of AniBackground
	m_animBackground = new Animation("Resources/Map/BackGround.png", 2, 1, 512, 256);
	m_animBackground->SetPosition(128, 128);
	m_animBackground->SetAnimation(0, 1);

	// Initialization and setting the position of Map
	m_gameMap = new GameMap(Define::WORLD_MAP);
	m_player = new Player();
	m_gameMap->SetPlayer(m_player);
	m_gameMap->LoadMap();

	// Initialization and setting the position of Camera
	m_camera = new Camera(GameGlobal::GetWidth(), GameGlobal::GetHeight());
	//m_camera->SetPosition(128, 800);

	//_pCamera->SetPosition(825, 900);
	m_camera->SetPosition(1670, 420);
	//m_camera->SetPosition(2245, 1175);
	//m_camera->SetPosition(2900, 1175);
	//m_camera->SetPosition(4735, 1175);
	//m_camera->SetPosition(6000, 1940);
	//m_camera->SetPosition(7560, 1940);
	m_gameMap->SetCamera(m_camera);

	// Setting the position of Player
	m_player->SetPosition(m_camera->GetPosition());

	// Other
	m_isBoss = false;
	m_currentRoom = { 0, 768, 768, 1024 };

	// NEXT ROOM
	m_nextRoom = RECT();

	// Clear the list entity out
	m_listEntityOut.clear();
	m_list000.clear();
}

BeginScene::~BeginScene()
{
	SAFE_DELETE(m_gameMap);
	SAFE_DELETE(m_camera);
	SAFE_DELETE(m_player);
	SAFE_DELETE(m_animBackground);
}

void BeginScene::Update(float dt)
{
	Sound::GetInstance()->Play("BlastHornet", true, 0);
	Sound::GetInstance()->SetVolume(90);

	// Getting Object in Camera
	m_listEntityOut.clear();
	m_listEntityOut.swap(m_list000);
	m_gameMap->GetQuadTree()->GetObjectCamera(m_listEntityOut, m_camera->GetBound());

	//Run KeyBoard play
	m_player->KeyBoardEventHandler(m_key, dt);

	// Check collision all Object in Camera
	CheckCollision(dt);
	CheckCameraAndWorldMap(dt);
	CheckCameraAndEnemies();

	// -------Update Object-------

	// Updating Map
	m_gameMap->Update(dt);

	// Updating Player
	m_player->Update(dt);

	// Updating the list entity out
	for (auto& entity : m_listEntityOut)
	{
		entity->Update(dt);
		if (GameCollision::IsCollision(entity->GetBound(), m_camera->GetBound()) == true)
			m_list000.push_back(entity);
	}

	// Background
	if (m_player->GetPosition().x > 2600 && m_player->GetPosition().x < 5632)
		m_animBackground->SetAnimation(1, 1);
	else
		m_animBackground->SetAnimation(0, 1);

	// Update any background
	m_animBackground->Update(dt);
}

void BeginScene::Draw()
{
	// Drawing AniBackground
	m_animBackground->Draw();
	
	// Drawing Map
	m_gameMap->Draw();

	// Drawing Player
	m_player->Draw(m_camera);

	// Drawing the list entity out
	for (auto& entity : m_listEntityOut)
		entity->Draw(m_camera);

	// Drawing Map
	m_gameMap->Draw1();

	// Drawing the HP of Player
	m_player->DrawHP();
}

void BeginScene::OnKeyDown(int keyCode)
{
	m_key[keyCode] = true;
	m_player->OnKeyDown(m_key, keyCode);
}

void BeginScene::OnKeyUp(int keyCode)
{
	m_key[keyCode] = false;
	m_player->OnKeyUp(keyCode);
}

void BeginScene::CheckCameraAndWorldMap(float dt)
{
	if (m_isBoss == true)
	{
		if (m_player->GetBound().left < m_camera->GetBound().left)
		{
			if (m_player->GetVx() < 0)
				m_player->SetVx(0);
		}
		else
		{
			if (m_player->GetBound().right > m_currentRoom.right)
			{
				if (m_player->GetVx() > 0)
					m_player->SetVx(0);
			}
		}
	}
	if (!GameCollision::PointCollision(m_player->GetPosition().x, m_player->GetPosition().y, m_currentRoom))
	{
		bool noRoom = true;
		for (auto& Room : m_gameMap->GetListRoom())
			if (GameCollision::PointCollision(m_player->GetPosition().x, m_player->GetPosition().y, Room))
			{
				noRoom = false;
				m_nextRoom = Room;
				m_currentRoom = Room;
				if (m_player->GetPosition().x < (m_currentRoom.left + (m_currentRoom.right - m_currentRoom.left) / 2))
				{
					if (m_camera->GetBound().left < m_currentRoom.left)
					{
						m_direction = 1;
						m_currentRoom.left = m_camera->GetBound().left;
					}
				}
				else if (m_player->GetPosition().x > (m_currentRoom.left + (m_currentRoom.right - m_currentRoom.left) / 2))
				{
					if (m_camera->GetBound().right > m_currentRoom.right)
					{
						m_direction = -1;
						m_currentRoom.right = m_camera->GetBound().right;
					}
				}
				break;
			}
		if (noRoom)
			m_player->SetState(new DieState(m_player->GetPlayerData()));
	}

	if (m_direction == 1)
	{
		m_currentRoom.left += 300 * dt;
		if (m_currentRoom.left >= m_nextRoom.left)
		{
			m_currentRoom.left = m_nextRoom.left;
			m_direction = 0;
		}
	}
	else if (m_direction == -1)
	{
		m_currentRoom.right -= 300 * dt;
		if (m_currentRoom.right <= m_nextRoom.right)
		{
			m_currentRoom.right = m_nextRoom.right;
			m_direction = 0;
		}
	}
	else
	{
		m_camera->SetPosition(m_player->GetPosition());
	}

	if (m_camera->GetBound().left < m_currentRoom.left)
		m_camera->SetPosition(m_currentRoom.left + m_camera->GetWidth() / 2, m_camera->GetPosition().y);
	else if (m_camera->GetBound().right > m_currentRoom.right)
		m_camera->SetPosition(m_currentRoom.right - m_camera->GetWidth() / 2, m_camera->GetPosition().y);

	if (m_camera->GetBound().top < m_currentRoom.top)
		m_camera->SetPosition(m_camera->GetPosition().x, m_currentRoom.top + m_camera->GetHeight() / 2);
	else if (m_camera->GetBound().bottom > m_currentRoom.bottom)
		m_camera->SetPosition(m_camera->GetPosition().x, m_currentRoom.bottom - m_camera->GetHeight() / 2);
}

void BeginScene::CheckCameraAndEnemies()
{
	for (auto& entity : m_listEntityOut)
	{
		if (entity->GetObjectType() == BaseObject::OBJECT_ENEMY)
		{
			if (m_player->GetPosition().x > entity->GetPosition().x)
				entity->SetReverse(true);
			else
				entity->SetReverse(false);

			if (!GameCollision::IsCollision(m_camera->GetBound(), entity->GetBound())
				&& !GameCollision::PointCollision(entity->GetPositionStart().x, entity->GetPositionStart().y, m_camera->GetBound()))
			{
				entity->NewEntity();
			}
		}
	}
}

void BeginScene::CheckCollision(float dt)
{
	// Check Boss and lock Port
	m_isBoss = false;
	for (auto& entity : m_listEntityOut)
	{
		if (entity->GetObjectType() == BaseObject::OBJECT_BOSS)
		{
			if (entity->GetHP() > 0)
			{
				m_isBoss = true;
				for (auto& obj : m_listEntityOut)
				{
					if (obj->GetObjectType() == BaseObject::OBJECT_PORT)
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
				for (auto& obj : m_listEntityOut)
				{
					if (obj->GetObjectType() == BaseObject::OBJECT_PORT)
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
	CheckCollision(m_player, dt);
	for (auto& playerBullet : (*m_player->GetPlayerBullet()))
	{
		if (playerBullet->GetExplosion())
			continue;
		for (auto& entity : m_listEntityOut)
			CheckCollision(entity, playerBullet, dt);
	}

	// Object with Object
	for (auto& entity : m_listEntityOut)
	{
		CheckCollision(entity, dt);

		// CheckCollision Enemy and EnemyBullet
		if (entity->GetObjectType() == BaseObject::OBJECT_ENEMY || entity->GetObjectType() == BaseObject::OBJECT_BOSS)
		{
			for (auto& bullet : *entity->GetListBullet())
			{
				if (bullet->GetDie())
					continue;

				if (bullet->GetObjectType() == BaseObject::OBJECT_ITEM)
				{
					CheckCollision(bullet, dt);
					CheckCollision(m_player, bullet, dt);
					continue;
				}

				CheckCollision(m_player, bullet, dt);

				std::vector<BaseObject*> listEntityStatic;
				m_gameMap->GetQuadTree()->GetObjectCollide(listEntityStatic, bullet->GetBound());

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
	for (auto& entity : m_listEntityOut)
	{
		if (obj->GetId() != entity->GetId())
			CheckCollision(obj, entity, dt);
	}

	std::vector<BaseObject*> listEntityStatic;
	m_gameMap->GetQuadTree()->GetObjectCollide(listEntityStatic, obj->GetBound());

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