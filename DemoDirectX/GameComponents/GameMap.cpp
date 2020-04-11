#include "GameMap.h"
#include "../GameDefines/GameDefine.h"
#include "GameCollision.h"
#include "GameGlobal.h"

#include "../GameObjects/Boss/BlastHornet/BlastHornet.h"
#include "../GameObjects/Boss/Genjibo/Genjibo.h"
#include "../GameObjects/Boss/CarryArm/Planet.h"
#include "../GameObjects/Boss/CarryArm/Box.h"
#include "../GameObjects/Enemies/Banger/Banger.h"
#include "../GameObjects/Enemies/Gunner/Gunner.h"
#include "../GameObjects/Enemies/Helit/Helit.h"
#include "../GameObjects/MapObjects/Elevator.h"
#include "../GameObjects/MapObjects/Conveyor.h"
#include "../GameObjects/MapObjects/Port.h"
#include "../GameObjects/Item/BigBloodItem.h"
#include "../GameObjects/Item/EnergyItem.h"
#include "QuadTree.h"

GameMap* GameMap::s_instance = nullptr;

GameMap::GameMap() : m_pTileMap(nullptr),
                     m_pTileMap1(nullptr),
                     m_pMap(nullptr),
                     m_rc()
{
}

GameMap::~GameMap()
{
	delete m_pMap;
	delete m_pTileMap;
	delete m_pTileMap1;

	for (auto e : m_lstEnemies)
		delete e;

	if (!m_lstEnemies.empty())
		m_lstEnemies.clear();
}

GameMap* GameMap::getInstance()
{
	if (!s_instance) s_instance = new GameMap;
	return s_instance;
}

void GameMap::release()
{
	delete s_instance;
	s_instance = nullptr;
}

void GameMap::initialize(const char* filePath)
{
	m_pMap = new Tmx::Map();
	m_pMap->ParseFile(filePath);

	m_pTileMap = new Sprite(Define::WORLD_MAP_PNG,
							RECT(),
							this->getWidth(),
							this->getHeight(),
							D3DCOLOR_XRGB(255, 255, 255));

	m_pTileMap->setWidth(GameGlobal::getInstance()->getWidth() + 4);
	m_pTileMap->setHeight(GameGlobal::getInstance()->getHeight() + 4);

	m_pTileMap1 = new Sprite("Resources/Map/Stage.png",
							 RECT(),
							 this->getWidth(),
							 this->getHeight(),
							 D3DCOLOR_XRGB(0, 0, 0));

	m_pTileMap1->setWidth(GameGlobal::getInstance()->getWidth() + 4);
	m_pTileMap1->setHeight(GameGlobal::getInstance()->getHeight() + 4);

	RECT r;
	r.left = 0;
	r.top = 0;
	r.right = this->getWidth();
	r.bottom = this->getHeight();

	QuadTree::getInstance()->initialize(1, r);
}

void GameMap::loadMap()
{
	BaseObject* obj = nullptr;

	// Static object
	for (auto objectGroup : m_pMap->GetObjectGroups())
	{
		if (!objectGroup->IsVisible())
			continue;
		for (auto object : objectGroup->GetObjects())
		{
			if (!object->IsVisible())
				continue;
			std::string name = objectGroup->GetName();
			if (name == "Room")
			{
				RECT room;
				room.left = object->GetX();
				room.top = object->GetY();
				room.right = object->GetX() + object->GetWidth();
				room.bottom = object->GetY() + object->GetHeight();
				m_lstRoom.push_back(room);
			}
			else if (name == "Boss1")
			{
				obj = new Genjibo();
				obj->setPositionStart(object->GetX() + object->GetWidth() / 2.0f, object->GetY());
				obj->setPosition(obj->getPositionStart());
				obj->setWidth(object->GetWidth());
				obj->setHeight(object->GetHeight());
				obj->setObjectType(Object_Type::BOSS);
				obj->setId(object->GetId());
				m_lstEnemies.push_back(obj);
				QuadTree::getInstance()->insertObject(obj);
			}
			else if (name == "Boss2")
			{
				obj = new Planet();
				obj->setPositionStart(object->GetX() + object->GetWidth() / 2.0f,
									  object->GetY() + object->GetHeight() / 2.0f);
				obj->setPosition(obj->getPositionStart().x, obj->getPositionStart().y - object->GetHeight() + 1);
				obj->setWidth(object->GetWidth());
				obj->setHeight(object->GetHeight());
				obj->setObjectType(Object_Type::BOSS);
				obj->setId(object->GetId());
				m_lstEnemies.push_back(obj);
				QuadTree::getInstance()->insertObject(obj);
			}
			else if (name == "Boss3")
			{
				obj = new BlastHornet();
				obj->setPositionStart(object->GetX() + object->GetWidth() / 2.0f,
									  object->GetY() + object->GetHeight() / 2.0f);
				obj->setPosition(obj->getPositionStart());
				obj->setWidth(object->GetWidth());
				obj->setHeight(object->GetHeight());
				obj->setObjectType(Object_Type::BOSS);
				obj->setId(object->GetId());
				m_lstEnemies.push_back(obj);
				QuadTree::getInstance()->insertObject(obj);
			}
			else if (name == "Banger")
			{
				obj = new Banger();
				obj->setPositionStart(object->GetX() + object->GetWidth() / 2.0f, object->GetY() + 7);
				obj->setPosition(obj->getPositionStart());
				obj->setWidth(object->GetWidth());
				obj->setHeight(object->GetHeight());
				obj->setObjectType(Object_Type::ENEMY);
				obj->setId(object->GetId());

				m_lstEnemies.push_back(obj);
				QuadTree::getInstance()->insertObject(obj);
			}
			else if (name == "Gunner")
			{
				obj = new Gunner();
				obj->setPositionStart(object->GetX() + object->GetWidth() / 2.0f,
									  object->GetY() - 1 + obj->getHeight() / 2.0f);
				obj->setPosition(obj->getPositionStart());
				obj->setWidth(object->GetWidth());
				obj->setHeight(object->GetHeight());
				obj->setObjectType(Object_Type::ENEMY);
				obj->setId(object->GetId());
				m_lstEnemies.push_back(obj);
				QuadTree::getInstance()->insertObject(obj);
			}
			else if (name == "Helit")
			{
				obj = new Helit();
				obj->setPositionStart(object->GetX() + object->GetWidth() / 2.0f,
									  object->GetY() - 1 + obj->getHeight() / 2.0f);
				obj->setPosition(obj->getPositionStart());
				obj->setWidth(object->GetWidth());
				obj->setHeight(object->GetHeight());
				obj->setObjectType(Object_Type::ENEMY);
				obj->setId(object->GetId());
				m_lstEnemies.push_back(obj);
				QuadTree::getInstance()->insertObject(obj);
			}
			else if (name == "Elevator")
			{
				obj = new Elevator();
				obj->setPositionStart(object->GetX() + object->GetWidth() / 2.0f,
									  object->GetY() + object->GetHeight() / 2.0f + 1);
				obj->setPosition(obj->getPositionStart());
				obj->setWidth(object->GetWidth());
				obj->setHeight(object->GetHeight());
				obj->setObjectType(Object_Type::ELEVATOR);
				obj->setId(object->GetId());
				QuadTree::getInstance()->insertObject(obj);
			}
			else if (name == "ConveyorR")
			{
				obj = new Conveyor(false);
				obj->setPositionStart(object->GetX() + object->GetWidth() / 2.0f,
									  object->GetY() + object->GetHeight() / 2.0f);
				obj->setPosition(obj->getPositionStart());
				obj->setWidth(object->GetWidth());
				obj->setHeight(object->GetHeight());
				obj->setObjectType(Object_Type::CONVEYOR);
				obj->setId(object->GetId());
				QuadTree::getInstance()->insertObject(obj);
			}
			else if (name == "ConveyorL")
			{
				obj = new Conveyor(true);
				obj->setPositionStart(object->GetX() + object->GetWidth() / 2.0f,
									  object->GetY() + object->GetHeight() / 2.0f);
				obj->setPosition(obj->getPositionStart());
				obj->setWidth(object->GetWidth());
				obj->setHeight(object->GetHeight());
				obj->setObjectType(Object_Type::CONVEYOR);
				obj->setId(object->GetId());
				QuadTree::getInstance()->insertObject(obj);
			}
			else if (name == "Port")
			{
				obj = new Port();
				obj->setPositionStart(object->GetX() + object->GetWidth() / 2.0f,
									  object->GetY() + object->GetHeight() / 2.0f);
				obj->setPosition(obj->getPositionStart());
				obj->setWidth(object->GetWidth());
				obj->setHeight(object->GetHeight());
				obj->setObjectType(Object_Type::PORT);
				obj->setId(object->GetId());
				QuadTree::getInstance()->insertObject(obj);
			}
			else if (name == "Thorn")
			{
				obj = new BaseObject();
				obj->setPositionStart(object->GetX() + object->GetWidth() / 2.0f,
									  object->GetY() + object->GetHeight() / 2.0f);
				obj->setPosition(obj->getPositionStart());
				obj->setWidth(object->GetWidth());
				obj->setHeight(object->GetHeight());
				obj->setObjectType(Object_Type::THORN);
				obj->setId(object->GetId());
				QuadTree::getInstance()->insertObject(obj);
			}
			else if (name == "Box")
			{
				obj = new Box();
				obj->setPositionStart(object->GetX() + object->GetWidth() / 2.0f,
									  object->GetY() + object->GetHeight() / 2.0f);
				obj->setPosition(obj->getPositionStart());
				obj->setWidth(object->GetWidth());
				obj->setHeight(object->GetHeight());
				obj->setObjectType(Object_Type::BOX);
				obj->setId(object->GetId());
				QuadTree::getInstance()->insertObject(obj);
			}
			else if (name == "Box1")
			{
				obj = new Box(true);
				obj->setPositionStart(object->GetX() + object->GetWidth() / 2.0f,
									  object->GetY() + object->GetHeight() / 2.0f);
				obj->setPosition(obj->getPositionStart());
				obj->setWidth(object->GetWidth());
				obj->setHeight(object->GetHeight());
				obj->setObjectType(Object_Type::ENEMY);
				obj->setId(object->GetId());
				obj->newObject();
				QuadTree::getInstance()->insertObject(obj);
			}
			else if (name == "Blood")
			{
				obj = new BigBloodItem();
				obj->setPositionStart(object->GetX() + object->GetWidth() / 2.0f,
									  object->GetY() + object->GetHeight() / 2.0f - 1);
				obj->setPosition(obj->getPositionStart());
				obj->setWidth(object->GetWidth());
				obj->setHeight(object->GetHeight());
				obj->setObjectType(Object_Type::ITEM);
				obj->setId(object->GetId());
				QuadTree::getInstance()->insertObject(obj);
			}
			else if (name == "Heart")
			{
				obj = new EnergyItem();
				obj->setPositionStart(object->GetX() + object->GetWidth() / 2.0f,
									  object->GetY() + object->GetHeight() / 2.0f - 1);
				obj->setPosition(obj->getPositionStart());
				obj->setObjectType(Object_Type::ITEM);
				obj->setId(object->GetId());
				QuadTree::getInstance()->insertObject(obj);
			}
			else if (name == "Wall")
			{
				obj = new BaseObject();
				obj->setPositionStart(object->GetX() + object->GetWidth() / 2.0f,
									  object->GetY() + object->GetHeight() / 2.0f);
				obj->setPosition(obj->getPositionStart());
				obj->setWidth(object->GetWidth());
				obj->setHeight(object->GetHeight());
				obj->setObjectType(Object_Type::STATIC);
				obj->setId(object->GetId());
				QuadTree::getInstance()->insertObject(obj);
			}
		}
	}
}


int GameMap::getWidth() const
{
	return m_pMap->GetWidth() * m_pMap->GetTileWidth();
}

int GameMap::getHeight() const
{
	return m_pMap->GetHeight() * m_pMap->GetTileHeight();
}

int GameMap::getTileWidth() const
{
	return m_pMap->GetTileWidth();
}

int GameMap::getTileHeight() const
{
	return m_pMap->GetTileHeight();
}

void GameMap::update(float dt)
{}

void GameMap::draw()
{
	GVec3 position = Camera::getInstance()->getPosition();
	m_rc.left = position.x - m_pTileMap->getWidth() / 2;
	m_rc.top = position.y - m_pTileMap->getHeight() / 2;
	m_rc.right = position.x + m_pTileMap->getWidth() / 2;
	m_rc.bottom = position.y + m_pTileMap->getHeight() / 2;

	m_pTileMap->draw(position,
					 m_rc,
					 GVec2(),
					 Camera::getInstance()->getTrans());
}

void GameMap::draw1()
{
	m_pTileMap1->draw(Camera::getInstance()->getPosition(),
					  m_rc,
					  GVec2(),
					  Camera::getInstance()->getTrans());
}

std::vector<RECT> GameMap::getListRoom() const
{
	return m_lstRoom;
}