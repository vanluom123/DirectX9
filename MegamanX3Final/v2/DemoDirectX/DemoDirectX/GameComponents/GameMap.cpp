#include "GameMap.h"
#include "../GameDefines/GameDefine.h"
#include "GameCollision.h"
#include "GameGlobal.h"

#include "../GameObjects/Boss/BlastHornet/Blast.h"
#include "../GameObjects/Boss/Genjibo-Shurikein/Genjibo.h"
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

GameMap::GameMap(const char* filePath)
{
	_pTmxMap = new Tmx::Map();
	_pTmxMap->ParseFile(filePath);

	_tileMap = new Sprite(Define::WORLD_MAP_PNG, RECT(), this->getWidth(), this->getHeight(), D3DCOLOR_XRGB(255, 255, 255));
	_tileMap->setWidth(GameGlobal::getWidth() + 4);
	_tileMap->setHeight(GameGlobal::getHeight() + 4);

	_tileMap1 = new Sprite("Resources/Map/Stage.png", RECT(), this->getWidth(), this->getHeight(), D3DCOLOR_XRGB(0, 0, 0));
	_tileMap1->setWidth(GameGlobal::getWidth() + 4);
	_tileMap1->setHeight(GameGlobal::getHeight() + 4);

	RECT r;
	r.left = 0;
	r.top = 0;
	r.right = this->getWidth();
	r.bottom = this->getHeight();

	_quadTree = new QuadTree(1, r);
}

GameMap::~GameMap()
{
	delete _pTmxMap;
	delete _tileMap;
	delete _tileMap1;
	for (auto& mListBrick : _listEnemies)
		delete mListBrick;
	_listEnemies.clear();

	delete _quadTree;
}

void GameMap::loadMap()
{
	// Object static
	for (size_t i = 0; i < _pTmxMap->GetNumObjectGroups(); i++)
	{
		const auto objectGroup = _pTmxMap->GetObjectGroup(i);
		std::string name = objectGroup->GetName();

		if (name == "Room")
			for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
			{
				const auto object = objectGroup->GetObjects().at(j);
				RECT room;
				room.left = object->GetX();
				room.top = object->GetY();
				room.right = object->GetX() + object->GetWidth();
				room.bottom = object->GetY() + object->GetHeight();

				_listRoom.push_back(room);
			}
		else

			if (name == "Boss1")
				for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
				{
					const auto object = objectGroup->GetObjects().at(j);

					auto* boss = new Genjibo();
					boss->setPositionStart(object->GetX() + object->GetWidth() / 2.0f, object->GetY());
					boss->setPosition(boss->getPositionStart());

					boss->setWidth(object->GetWidth());
					boss->setHeight(object->GetHeight());

					boss->setObjectType(BaseObject::BOSS);
					boss->setId(object->GetId());

					_listEnemies.push_back(boss);
					_quadTree->insertObject(boss);
				}
			else
				if (name == "Boss2")
					for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
					{
						const auto object = objectGroup->GetObjects().at(j);

						auto boss = new Planet(_player);
						boss->setPositionStart(object->GetX() + object->GetWidth() / 2.0f, object->GetY() + object->GetHeight() / 2.0f);
						boss->setPosition(boss->getPositionStart().x, boss->getPositionStart().y - object->GetHeight() + 1);

						boss->setWidth(object->GetWidth());
						boss->setHeight(object->GetHeight());

						boss->setObjectType(BaseObject::BOSS);
						boss->setId(object->GetId());

						_listEnemies.push_back(boss);
						_quadTree->insertObject(boss);
					}
				else
					if (name == "Boss3")
						for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
						{
							const auto object = objectGroup->GetObjects().at(j);

							auto* boss = new Blast();
							boss->setPositionStart(object->GetX() + object->GetWidth() / 2.0f, object->GetY() + object->GetHeight() / 2.0f);
							boss->setPosition(boss->getPositionStart());

							boss->setWidth(object->GetWidth());
							boss->setHeight(object->GetHeight());

							boss->setObjectType(BaseObject::BOSS);
							boss->setId(object->GetId());

							_listEnemies.push_back(boss);
							_quadTree->insertObject(boss);
						}
					else
						if (name == "Banger")
							for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
							{
								const auto object = objectGroup->GetObjects().at(j);

								auto* banger = new Banger();
								banger->setPositionStart(object->GetX() + object->GetWidth() / 2.0f, object->GetY() + 7);
								banger->setPosition(banger->getPositionStart());

								banger->setWidth(object->GetWidth());
								banger->setHeight(object->GetHeight());

								banger->setObjectType(BaseObject::ENEMY);
								banger->setId(object->GetId());

								_listEnemies.push_back(banger);
								_quadTree->insertObject(banger);
							}
						else
							if (name == "Gunner")
								for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
								{
									const auto object = objectGroup->GetObjects().at(j);

									auto* gunner = new Gunner();
									gunner->setPositionStart(object->GetX() + object->GetWidth() / 2.0f, object->GetY() - 1 + gunner->getHeight() / 2.0f);
									gunner->setPosition(gunner->getPositionStart());

									gunner->setWidth(object->GetWidth());
									gunner->setHeight(object->GetHeight());

									gunner->setObjectType(BaseObject::ENEMY);
									gunner->setId(object->GetId());

									_listEnemies.push_back(gunner);
									_quadTree->insertObject(gunner);
								}
							else
								if (name == "Helit")
									for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
									{
										const auto object = objectGroup->GetObjects().at(j);

										auto* helit = new Helit();
										helit->setPositionStart(object->GetX() + object->GetWidth() / 2.0f, object->GetY() - 1 + helit->getHeight() / 2.0f);
										helit->setPosition(helit->getPositionStart());

										helit->setWidth(object->GetWidth());
										helit->setHeight(object->GetHeight());

										helit->setObjectType(BaseObject::ENEMY);
										helit->setId(object->GetId());

										_listEnemies.push_back(helit);
										_quadTree->insertObject(helit);
									}
								else
									if (name == "Elevator")
										for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
										{
											const auto object = objectGroup->GetObjects().at(j);

											auto* elevator = new Elevator();
											elevator->setPositionStart(object->GetX() + object->GetWidth() / 2.0f, object->GetY() + object->GetHeight() / 2.0f + 1);
											elevator->setPosition(elevator->getPositionStart());

											elevator->setWidth(object->GetWidth());
											elevator->setHeight(object->GetHeight());

											elevator->setObjectType(BaseObject::ELEVATOR);
											elevator->setId(object->GetId());

											_quadTree->insertObject(elevator);
										}
									else
										if (name == "ConveyorR")
											for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
											{
												const auto object = objectGroup->GetObjects().at(j);

												auto* conveyor = new Conveyor(false);
												conveyor->setPositionStart(object->GetX() + object->GetWidth() / 2.0f, object->GetY() + object->GetHeight() / 2.0f);
												conveyor->setPosition(conveyor->getPositionStart());

												conveyor->setWidth(object->GetWidth());
												conveyor->setHeight(object->GetHeight());

												conveyor->setObjectType(BaseObject::CONVEYOR);
												conveyor->setId(object->GetId());

												_quadTree->insertObject(conveyor);
											}
										else
											if (name == "ConveyorL")
												for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
												{
													const auto object = objectGroup->GetObjects().at(j);

													auto* conveyor = new Conveyor(true);
													conveyor->setPositionStart(object->GetX() + object->GetWidth() / 2.0f, object->GetY() + object->GetHeight() / 2.0f);
													conveyor->setPosition(conveyor->getPositionStart());

													conveyor->setWidth(object->GetWidth());
													conveyor->setHeight(object->GetHeight());

													conveyor->setObjectType(BaseObject::CONVEYOR);
													conveyor->setId(object->GetId());

													_quadTree->insertObject(conveyor);
												}
											else
												if (name == "Port")
													for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
													{
														const auto object = objectGroup->GetObjects().at(j);

														auto* port = new Port();
														port->setPositionStart(object->GetX() + object->GetWidth() / 2.0f, object->GetY() + object->GetHeight() / 2.0f);
														port->setPosition(port->getPositionStart());

														port->setWidth(object->GetWidth());
														port->setHeight(object->GetHeight());

														port->setObjectType(BaseObject::PORT);
														port->setId(object->GetId());

														_quadTree->insertObject(port);
													}
												else
													if (name == "Thorn")
														for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
														{
															const auto object = objectGroup->GetObjects().at(j);

															auto* entity = new BaseObject();
															entity->setPositionStart(object->GetX() + object->GetWidth() / 2.0f, object->GetY() + object->GetHeight() / 2.0f);
															entity->setPosition(entity->getPositionStart());
															entity->setWidth(object->GetWidth());
															entity->setHeight(object->GetHeight());

															entity->setObjectType(BaseObject::THORN);
															entity->setId(object->GetId());
															_quadTree->insertObject(entity);
														}
													else
														if (name == "Box")
															for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
															{
																const auto object = objectGroup->GetObjects().at(j);

																auto* boxx = new Box();
																boxx->setPositionStart(object->GetX() + object->GetWidth() / 2.0f, object->GetY() + object->GetHeight() / 2.0f);
																boxx->setPosition(boxx->getPositionStart());

																boxx->setWidth(object->GetWidth());
																boxx->setHeight(object->GetHeight());

																boxx->setObjectType(BaseObject::BOX);
																boxx->setId(object->GetId());

																_quadTree->insertObject(boxx);
															}
														else
															if (name == "Box1")
																for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
																{
																	const auto object = objectGroup->GetObjects().at(j);

																	auto* boxx = new Box(true);
																	boxx->setPositionStart(object->GetX() + object->GetWidth() / 2.0f, object->GetY() + object->GetHeight() / 2.0f);
																	boxx->setPosition(boxx->getPositionStart());

																	boxx->setWidth(object->GetWidth());
																	boxx->setHeight(object->GetHeight());

																	boxx->setObjectType(BaseObject::ENEMY);
																	boxx->setId(object->GetId());
																	boxx->newObject();
																	_quadTree->insertObject(boxx);
																}
															else
																if (name == "Blood")
																	for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
																	{
																		const auto object = objectGroup->GetObjects().at(j);

																		auto* item = new BigBloodItem();
																		item->setPositionStart(object->GetX() + object->GetWidth() / 2.0f, object->GetY() + object->GetHeight() / 2.0f - 1);
																		item->setPosition(item->getPositionStart());

																		item->setWidth(object->GetWidth());
																		item->setHeight(object->GetHeight());

																		item->setObjectType(BaseObject::ITEM);
																		item->setId(object->GetId());
																		_quadTree->insertObject(item);
																	}
																else
																	if (name == "Heart")
																		for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
																		{
																			const auto object = objectGroup->GetObjects().at(j);

																			auto* item = new EnergyItem();
																			item->setPositionStart(object->GetX() + object->GetWidth() / 2.0f, object->GetY() + object->GetHeight() / 2.0f - 1);
																			item->setPosition(item->getPositionStart());

																			item->setObjectType(BaseObject::ITEM);
																			item->setId(object->GetId());
																			_quadTree->insertObject(item);
																		}
																	else
																		if (name == "Wall")
																			for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
																			{
																				const auto object = objectGroup->GetObjects().at(j);

																				auto* entity = new BaseObject();
																				entity->setPositionStart(object->GetX() + object->GetWidth() / 2.0f, object->GetY() + object->GetHeight() / 2.0f);
																				entity->setPosition(entity->getPositionStart());
																				entity->setWidth(object->GetWidth());
																				entity->setHeight(object->GetHeight());

																				entity->setObjectType(BaseObject::STATIC);
																				entity->setId(object->GetId());
																				_quadTree->insertObject(entity);
																			}
	}
}

void GameMap::setViewport(Camera * camera)
{
	_viewport = camera;
}

Tmx::Map* GameMap::getMap() const
{
	return _pTmxMap;
}

RECT GameMap::getWorldMapBound() const
{
	RECT bound;
	bound.left = bound.top = 0;
	bound.right = getWidth();
	bound.bottom = getHeight();
	return bound;
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

bool GameMap::isBoundLeft() const
{
	return (_viewport->getBound().left == 0);
}

bool GameMap::isBoundRight() const
{
	return (_viewport->getBound().right == this->getWidth());
}

bool GameMap::isBoundTop() const
{
	return (_viewport->getBound().top == 0);
}

bool GameMap::isBoundBottom() const
{
	return (_viewport->getBound().bottom == this->getHeight());
}

void GameMap::update(float dt)
{

}

void GameMap::draw()
{
	GVec3 position = _viewport->getPosition();
	_srect.top = position.y - _tileMap->getHeight() / 2;
	_srect.bottom = position.y + _tileMap->getHeight() / 2;
	_srect.left = position.x - _tileMap->getWidth() / 2;
	_srect.right = position.x + _tileMap->getWidth() / 2;

	_tileMap->draw(position, _srect, GVec2(), _viewport->getTrans());
}

void GameMap::draw1()
{
	_tileMap1->draw(_viewport->getPosition(), _srect, GVec2(), _viewport->getTrans());
}

std::vector<BaseObject*> GameMap::getListEnemies() const
{
	return _listEnemies;
}

std::vector<RECT> GameMap::getListRoom() const
{
	return _listRoom;
}

QuadTree* GameMap::getQuadTree() const
{
	return _quadTree;
}

void GameMap::setPlayer(Player* player)
{
	_player = player;
}
