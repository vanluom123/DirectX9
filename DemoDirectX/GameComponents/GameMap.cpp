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

GameMap * GameMap::s_instance = NULL;

GameMap::~GameMap()
{
	delete _pTmxMap;
	delete _tileMap;
	delete _tileMap1;

	for (auto e : _listEnemies)
		delete e;

	if (!_listEnemies.empty())
		_listEnemies.clear();
}

GameMap * GameMap::getInstance()
{
	if (!s_instance) s_instance = new GameMap;
	return s_instance;
}

void GameMap::release()
{
	delete s_instance;
	s_instance = NULL;
}

void GameMap::initialize(const char * filePath)
{
	_pTmxMap = new Tmx::Map();
	_pTmxMap->ParseFile(filePath);

	_tileMap = new Sprite(Define::WORLD_MAP_PNG, RECT(), this->getWidth(), this->getHeight(),
						  D3DCOLOR_XRGB(255, 255, 255));
	_tileMap->setWidth(GameGlobal::getInstance()->getWidth() + 4);
	_tileMap->setHeight(GameGlobal::getInstance()->getHeight() + 4);

	_tileMap1 = new Sprite("Resources/Map/Stage.png", RECT(), this->getWidth(), this->getHeight(),
						   D3DCOLOR_XRGB(0, 0, 0));
	_tileMap1->setWidth(GameGlobal::getInstance()->getWidth() + 4);
	_tileMap1->setHeight(GameGlobal::getInstance()->getHeight() + 4);

	RECT r;
	r.left = 0;
	r.top = 0;
	r.right = this->getWidth();
	r.bottom = this->getHeight();

	QuadTree::getInstance()->initialize(1, r);
}

void GameMap::loadMap()
{
	// Object static
	for (size_t i = 0; i < _pTmxMap->GetNumObjectGroups(); i++)
	{
		const Tmx::ObjectGroup * const objectGroup = _pTmxMap->GetObjectGroup(i);
		std::string name = objectGroup->GetName();

		if (name == "Room")
			for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object * const object = objectGroup->GetObjects().at(j);
				RECT room;
				room.left = object->GetX();
				room.top = object->GetY();
				room.right = object->GetX() + object->GetWidth();
				room.bottom = object->GetY() + object->GetHeight();
				_listRoom.push_back(room);
			}
		else if (name == "Boss1")
			for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object * const obj1 = objectGroup->GetObjects().at(j);

				auto boss = new Genjibo();
				boss->setPositionStart(obj1->GetX() + obj1->GetWidth() / 2.0f, obj1->GetY());
				boss->setPosition(boss->getPositionStart());
				boss->setWidth(obj1->GetWidth());
				boss->setHeight(obj1->GetHeight());
				boss->setObjectType(Object_Type::BOSS);
				boss->setId(obj1->GetId());

				_listEnemies.push_back(boss);
				QuadTree::getInstance()->insertObject(boss);
			}
		else if (name == "Boss2")
			for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object * const obj2 = objectGroup->GetObjects().at(j);

				auto boss2 = new Planet();
				boss2->setPositionStart(obj2->GetX() + obj2->GetWidth() / 2.0f,
										obj2->GetY() + obj2->GetHeight() / 2.0f);
				boss2->setPosition(boss2->getPositionStart().x, boss2->getPositionStart().y - obj2->GetHeight() + 1);
				boss2->setWidth(obj2->GetWidth());
				boss2->setHeight(obj2->GetHeight());
				boss2->setObjectType(Object_Type::BOSS);
				boss2->setId(obj2->GetId());

				_listEnemies.push_back(boss2);
				QuadTree::getInstance()->insertObject(boss2);
			}
		else if (name == "Boss3")
			for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object * const object = objectGroup->GetObjects().at(j);

				auto boss = new BlastHornet();
				boss->setPositionStart(object->GetX() + object->GetWidth() / 2.0f,
									   object->GetY() + object->GetHeight() / 2.0f);
				boss->setPosition(boss->getPositionStart());
				boss->setWidth(object->GetWidth());
				boss->setHeight(object->GetHeight());
				boss->setObjectType(Object_Type::BOSS);
				boss->setId(object->GetId());

				_listEnemies.push_back(boss);
				QuadTree::getInstance()->insertObject(boss);
			}
		else if (name == "Banger")
			for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object * const object = objectGroup->GetObjects().at(j);

				auto banger = new Banger();
				banger->setPositionStart(object->GetX() + object->GetWidth() / 2.0f, object->GetY() + 7);
				banger->setPosition(banger->getPositionStart());
				banger->setWidth(object->GetWidth());
				banger->setHeight(object->GetHeight());
				banger->setObjectType(Object_Type::ENEMY);
				banger->setId(object->GetId());

				_listEnemies.push_back(banger);
				QuadTree::getInstance()->insertObject(banger);
			}
		else if (name == "Gunner")
			for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object * const object = objectGroup->GetObjects().at(j);

				auto gunner = new Gunner();
				gunner->setPositionStart(object->GetX() + object->GetWidth() / 2.0f,
										 object->GetY() - 1 + gunner->getHeight() / 2.0f);
				gunner->setPosition(gunner->getPositionStart());
				gunner->setWidth(object->GetWidth());
				gunner->setHeight(object->GetHeight());
				gunner->setObjectType(Object_Type::ENEMY);
				gunner->setId(object->GetId());

				_listEnemies.push_back(gunner);
				QuadTree::getInstance()->insertObject(gunner);
			}
		else if (name == "Helit")
			for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object * const object = objectGroup->GetObjects().at(j);

				auto helit = new Helit();
				helit->setPositionStart(object->GetX() + object->GetWidth() / 2.0f,
										object->GetY() - 1 + helit->getHeight() / 2.0f);
				helit->setPosition(helit->getPositionStart());
				helit->setWidth(object->GetWidth());
				helit->setHeight(object->GetHeight());
				helit->setObjectType(Object_Type::ENEMY);
				helit->setId(object->GetId());

				_listEnemies.push_back(helit);
				QuadTree::getInstance()->insertObject(helit);
			}
		else if (name == "Elevator")
			for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object * const object = objectGroup->GetObjects().at(j);

				auto elevator = new Elevator();
				elevator->setPositionStart(object->GetX() + object->GetWidth() / 2.0f,
										   object->GetY() + object->GetHeight() / 2.0f + 1);
				elevator->setPosition(elevator->getPositionStart());

				elevator->setWidth(object->GetWidth());
				elevator->setHeight(object->GetHeight());

				elevator->setObjectType(Object_Type::ELEVATOR);
				elevator->setId(object->GetId());

				QuadTree::getInstance()->insertObject(elevator);
			}
		else if (name == "ConveyorR")
			for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object * const object = objectGroup->GetObjects().at(j);

				auto conveyor = new Conveyor(false);
				conveyor->setPositionStart(object->GetX() + object->GetWidth() / 2.0f,
										   object->GetY() + object->GetHeight() / 2.0f);
				conveyor->setPosition(conveyor->getPositionStart());

				conveyor->setWidth(object->GetWidth());
				conveyor->setHeight(object->GetHeight());

				conveyor->setObjectType(Object_Type::CONVEYOR);
				conveyor->setId(object->GetId());

				QuadTree::getInstance()->insertObject(conveyor);
			}
		else if (name == "ConveyorL")
			for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object * const object = objectGroup->GetObjects().at(j);

				auto conveyor = new Conveyor(true);
				conveyor->setPositionStart(object->GetX() + object->GetWidth() / 2.0f,
										   object->GetY() + object->GetHeight() / 2.0f);
				conveyor->setPosition(conveyor->getPositionStart());

				conveyor->setWidth(object->GetWidth());
				conveyor->setHeight(object->GetHeight());

				conveyor->setObjectType(Object_Type::CONVEYOR);
				conveyor->setId(object->GetId());

				QuadTree::getInstance()->insertObject(conveyor);
			}
		else if (name == "Port")
			for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object * const object = objectGroup->GetObjects().at(j);

				auto port = new Port();
				port->setPositionStart(object->GetX() + object->GetWidth() / 2.0f,
									   object->GetY() + object->GetHeight() / 2.0f);
				port->setPosition(port->getPositionStart());

				port->setWidth(object->GetWidth());
				port->setHeight(object->GetHeight());

				port->setObjectType(Object_Type::PORT);
				port->setId(object->GetId());

				QuadTree::getInstance()->insertObject(port);
			}
		else if (name == "Thorn")
			for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object * const object = objectGroup->GetObjects().at(j);

				auto entity = new BaseObject();
				entity->setPositionStart(object->GetX() + object->GetWidth() / 2.0f,
										 object->GetY() + object->GetHeight() / 2.0f);
				entity->setPosition(entity->getPositionStart());
				entity->setWidth(object->GetWidth());
				entity->setHeight(object->GetHeight());

				entity->setObjectType(Object_Type::THORN);
				entity->setId(object->GetId());

				QuadTree::getInstance()->insertObject(entity);
			}
		else if (name == "Box")
			for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object * const object = objectGroup->GetObjects().at(j);

				auto boxx = new Box();
				boxx->setPositionStart(object->GetX() + object->GetWidth() / 2.0f,
									   object->GetY() + object->GetHeight() / 2.0f);
				boxx->setPosition(boxx->getPositionStart());

				boxx->setWidth(object->GetWidth());
				boxx->setHeight(object->GetHeight());

				boxx->setObjectType(Object_Type::BOX);
				boxx->setId(object->GetId());

				QuadTree::getInstance()->insertObject(boxx);
			}
		else if (name == "Box1")
			for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object * const object = objectGroup->GetObjects().at(j);

				auto boxx = new Box(true);
				boxx->setPositionStart(object->GetX() + object->GetWidth() / 2.0f,
									   object->GetY() + object->GetHeight() / 2.0f);
				boxx->setPosition(boxx->getPositionStart());

				boxx->setWidth(object->GetWidth());
				boxx->setHeight(object->GetHeight());

				boxx->setObjectType(Object_Type::ENEMY);
				boxx->setId(object->GetId());
				boxx->newObject();

				QuadTree::getInstance()->insertObject(boxx);
			}
		else if (name == "Blood")
			for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object * const object = objectGroup->GetObjects().at(j);

				auto item = new BigBloodItem();
				item->setPositionStart(object->GetX() + object->GetWidth() / 2.0f,
									   object->GetY() + object->GetHeight() / 2.0f - 1);
				item->setPosition(item->getPositionStart());

				item->setWidth(object->GetWidth());
				item->setHeight(object->GetHeight());

				item->setObjectType(Object_Type::ITEM);
				item->setId(object->GetId());

				QuadTree::getInstance()->insertObject(item);
			}
		else if (name == "Heart")
			for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object * const object = objectGroup->GetObjects().at(j);

				auto item = new EnergyItem();
				item->setPositionStart(object->GetX() + object->GetWidth() / 2.0f,
									   object->GetY() + object->GetHeight() / 2.0f - 1);
				item->setPosition(item->getPositionStart());

				item->setObjectType(Object_Type::ITEM);
				item->setId(object->GetId());

				QuadTree::getInstance()->insertObject(item);
			}
		else if (name == "Wall")
			for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object * const object = objectGroup->GetObjects().at(j);

				auto entity = new BaseObject();
				entity->setPositionStart(object->GetX() + object->GetWidth() / 2.0f,
										 object->GetY() + object->GetHeight() / 2.0f);
				entity->setPosition(entity->getPositionStart());
				entity->setWidth(object->GetWidth());
				entity->setHeight(object->GetHeight());

				entity->setObjectType(Object_Type::STATIC);
				entity->setId(object->GetId());

				QuadTree::getInstance()->insertObject(entity);
			}
	}
}


int GameMap::getWidth() const
{
	return _pTmxMap->GetWidth() * _pTmxMap->GetTileWidth();
}

int GameMap::getHeight() const
{
	return _pTmxMap->GetHeight() * _pTmxMap->GetTileHeight();
}

int GameMap::getTileWidth() const
{
	return _pTmxMap->GetTileWidth();
}

int GameMap::getTileHeight() const
{
	return _pTmxMap->GetTileHeight();
}

void GameMap::update(float dt)
{ }

void GameMap::draw()
{
	GVec3 position = Camera::getInstance()->getPosition();
	_srect.top = position.y - _tileMap->getHeight() / 2;
	_srect.bottom = position.y + _tileMap->getHeight() / 2;
	_srect.left = position.x - _tileMap->getWidth() / 2;
	_srect.right = position.x + _tileMap->getWidth() / 2;

	_tileMap->draw(position, _srect, GVec2(), Camera::getInstance()->getTrans());
}

void GameMap::draw1()
{
	_tileMap1->draw(Camera::getInstance()->getPosition(), _srect, GVec2(), Camera::getInstance()->getTrans());
}

std::vector<RECT> GameMap::getListRoom() const
{
	return _listRoom;
}