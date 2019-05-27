#include "GameMap.h"
#include "../GameDefines/GameDefine.h"
#include "GameCollision.h"
#include "GameGlobal.h"

#include "../GameObjects/Boss/BlastHornet/BlastHornet.h"
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

	_tileMap = new Sprite(Define::WORLD_MAP_PNG, RECT(), this->GetWidth(), this->GetHeight(), D3DCOLOR_XRGB(255, 255, 255));
	_tileMap->SetWidth(GameGlobal::GetWidth() + 4);
	_tileMap->SetHeight(GameGlobal::GetHeight() + 4);

	_tileMap1 = new Sprite("Resources/Map/Stage.png", RECT(), this->GetWidth(), this->GetHeight(), D3DCOLOR_XRGB(0, 0, 0));
	_tileMap1->SetWidth(GameGlobal::GetWidth() + 4);
	_tileMap1->SetHeight(GameGlobal::GetHeight() + 4);

	RECT r;
	r.left = 0;
	r.top = 0;
	r.right = this->GetWidth();
	r.bottom = this->GetHeight();

	_pQuadTree = new QuadTree(1, r);
}

GameMap::~GameMap()
{
	delete _pTmxMap;
	delete _tileMap;
	delete _tileMap1;
	for (auto& mListBrick : _listEnemies)
		delete mListBrick;
	_listEnemies.clear();

	delete _pQuadTree;
}

void GameMap::LoadMap()
{
	//Object static
	for (size_t i = 0; i < _pTmxMap->GetNumObjectGroups(); i++)
	{
		const auto objectGroup = _pTmxMap->GetObjectGroup(i);
		string name = objectGroup->GetName();

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
					boss->SetPositionStart(object->GetX() + object->GetWidth() / 2.0f, object->GetY());
					boss->SetPosition(boss->getPositionStart());

					boss->SetWidth(object->GetWidth());
					boss->SetHeight(object->GetHeight());

					boss->SetObjectType(BaseObject::BOSS);
					boss->SetId(object->GetId());

					_listEnemies.push_back(boss);
					_pQuadTree->InsertObject(boss);
				}
			else
				if (name == "Boss2")
					for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
					{
						const auto object = objectGroup->GetObjects().at(j);

						auto* boss = new Planet(_pPlayer);
						boss->SetPositionStart(object->GetX() + object->GetWidth() / 2.0f, object->GetY() + object->GetHeight() / 2.0f);
						boss->SetPosition(boss->getPositionStart().x, boss->getPositionStart().y - object->GetHeight() + 1);

						boss->SetWidth(object->GetWidth());
						boss->SetHeight(object->GetHeight());

						boss->SetObjectType(BaseObject::BOSS);
						boss->SetId(object->GetId());

						_listEnemies.push_back(boss);
						_pQuadTree->InsertObject(boss);
					}
				else
					if (name == "Boss3")
						for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
						{
							const auto object = objectGroup->GetObjects().at(j);

							auto* boss = new BlastHornet();
							boss->SetPositionStart(object->GetX() + object->GetWidth() / 2.0f, object->GetY() + object->GetHeight() / 2.0f);
							boss->SetPosition(boss->getPositionStart());

							boss->SetWidth(object->GetWidth());
							boss->SetHeight(object->GetHeight());

							boss->SetObjectType(BaseObject::BOSS);
							boss->SetId(object->GetId());

							_listEnemies.push_back(boss);
							_pQuadTree->InsertObject(boss);
						}
					else
						if (name == "Banger")
							for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
							{
								const auto object = objectGroup->GetObjects().at(j);

								auto* banger = new Banger();
								banger->SetPositionStart(object->GetX() + object->GetWidth() / 2.0f, object->GetY() + 7);
								banger->SetPosition(banger->getPositionStart());

								banger->SetWidth(object->GetWidth());
								banger->SetHeight(object->GetHeight());

								banger->SetObjectType(BaseObject::ENEMY);
								banger->SetId(object->GetId());

								_listEnemies.push_back(banger);
								_pQuadTree->InsertObject(banger);
							}
						else
							if (name == "Gunner")
								for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
								{
									const auto object = objectGroup->GetObjects().at(j);

									auto* gunner = new Gunner();
									gunner->SetPositionStart(object->GetX() + object->GetWidth() / 2.0f, object->GetY() - 1 + gunner->GetHeight() / 2.0f);
									gunner->SetPosition(gunner->getPositionStart());

									gunner->SetWidth(object->GetWidth());
									gunner->SetHeight(object->GetHeight());

									gunner->SetObjectType(BaseObject::ENEMY);
									gunner->SetId(object->GetId());

									_listEnemies.push_back(gunner);
									_pQuadTree->InsertObject(gunner);
								}
							else
								if (name == "Helit")
									for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
									{
										const auto object = objectGroup->GetObjects().at(j);

										auto* helit = new Helit();
										helit->SetPositionStart(object->GetX() + object->GetWidth() / 2.0f, object->GetY() - 1 + helit->GetHeight() / 2.0f);
										helit->SetPosition(helit->getPositionStart());

										helit->SetWidth(object->GetWidth());
										helit->SetHeight(object->GetHeight());

										helit->SetObjectType(BaseObject::ENEMY);
										helit->SetId(object->GetId());

										_listEnemies.push_back(helit);
										_pQuadTree->InsertObject(helit);
									}
								else
									if (name == "Elevator")
										for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
										{
											const auto object = objectGroup->GetObjects().at(j);

											auto* elevator = new Elevator();
											elevator->SetPositionStart(object->GetX() + object->GetWidth() / 2.0f, object->GetY() + object->GetHeight() / 2.0f + 1);
											elevator->SetPosition(elevator->getPositionStart());

											elevator->SetWidth(object->GetWidth());
											elevator->SetHeight(object->GetHeight());

											elevator->SetObjectType(BaseObject::ELEVATOR);
											elevator->SetId(object->GetId());

											_pQuadTree->InsertObject(elevator);
										}
									else
										if (name == "ConveyorR")
											for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
											{
												const auto object = objectGroup->GetObjects().at(j);

												auto* conveyor = new Conveyor(false);
												conveyor->SetPositionStart(object->GetX() + object->GetWidth() / 2.0f, object->GetY() + object->GetHeight() / 2.0f);
												conveyor->SetPosition(conveyor->getPositionStart());

												conveyor->SetWidth(object->GetWidth());
												conveyor->SetHeight(object->GetHeight());

												conveyor->SetObjectType(BaseObject::CONVEYOR);
												conveyor->SetId(object->GetId());

												_pQuadTree->InsertObject(conveyor);
											}
										else
											if (name == "ConveyorL")
												for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
												{
													const auto object = objectGroup->GetObjects().at(j);

													auto* conveyor = new Conveyor(true);
													conveyor->SetPositionStart(object->GetX() + object->GetWidth() / 2.0f, object->GetY() + object->GetHeight() / 2.0f);
													conveyor->SetPosition(conveyor->getPositionStart());

													conveyor->SetWidth(object->GetWidth());
													conveyor->SetHeight(object->GetHeight());

													conveyor->SetObjectType(BaseObject::CONVEYOR);
													conveyor->SetId(object->GetId());

													_pQuadTree->InsertObject(conveyor);
												}
											else
												if (name == "Port")
													for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
													{
														const auto object = objectGroup->GetObjects().at(j);

														auto* port = new Port();
														port->SetPositionStart(object->GetX() + object->GetWidth() / 2.0f, object->GetY() + object->GetHeight() / 2.0f);
														port->SetPosition(port->getPositionStart());

														port->SetWidth(object->GetWidth());
														port->SetHeight(object->GetHeight());

														port->SetObjectType(BaseObject::PORT);
														port->SetId(object->GetId());

														_pQuadTree->InsertObject(port);
													}
												else
													if (name == "Thorn")
														for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
														{
															const auto object = objectGroup->GetObjects().at(j);

															auto* entity = new BaseObject();
															entity->SetPositionStart(object->GetX() + object->GetWidth() / 2.0f, object->GetY() + object->GetHeight() / 2.0f);
															entity->SetPosition(entity->getPositionStart());
															entity->SetWidth(object->GetWidth());
															entity->SetHeight(object->GetHeight());

															entity->SetObjectType(BaseObject::THORN);
															entity->SetId(object->GetId());
															_pQuadTree->InsertObject(entity);
														}
													else
														if (name == "Box")
															for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
															{
																const auto object = objectGroup->GetObjects().at(j);

																auto* boxx = new Box();
																boxx->SetPositionStart(object->GetX() + object->GetWidth() / 2.0f, object->GetY() + object->GetHeight() / 2.0f);
																boxx->SetPosition(boxx->getPositionStart());

																boxx->SetWidth(object->GetWidth());
																boxx->SetHeight(object->GetHeight());

																boxx->SetObjectType(BaseObject::BOX);
																boxx->SetId(object->GetId());

																_pQuadTree->InsertObject(boxx);
															}
														else
															if (name == "Box1")
																for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
																{
																	const auto object = objectGroup->GetObjects().at(j);

																	auto* boxx = new Box(true);
																	boxx->SetPositionStart(object->GetX() + object->GetWidth() / 2.0f, object->GetY() + object->GetHeight() / 2.0f);
																	boxx->SetPosition(boxx->getPositionStart());

																	boxx->SetWidth(object->GetWidth());
																	boxx->SetHeight(object->GetHeight());

																	boxx->SetObjectType(BaseObject::ENEMY);
																	boxx->SetId(object->GetId());
																	boxx->NewEntity();
																	_pQuadTree->InsertObject(boxx);
																}
															else
																if (name == "Blood")
																	for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
																	{
																		const auto object = objectGroup->GetObjects().at(j);

																		auto* item = new BigBloodItem();
																		item->SetPositionStart(object->GetX() + object->GetWidth() / 2.0f, object->GetY() + object->GetHeight() / 2.0f - 1);
																		item->SetPosition(item->getPositionStart());

																		item->SetWidth(object->GetWidth());
																		item->SetHeight(object->GetHeight());

																		item->SetObjectType(BaseObject::ITEM);
																		item->SetId(object->GetId());
																		_pQuadTree->InsertObject(item);
																	}
																else
																	if (name == "Heart")
																		for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
																		{
																			const auto object = objectGroup->GetObjects().at(j);

																			auto* item = new EnergyItem();
																			item->SetPositionStart(object->GetX() + object->GetWidth() / 2.0f, object->GetY() + object->GetHeight() / 2.0f - 1);
																			item->SetPosition(item->getPositionStart());

																			item->SetObjectType(BaseObject::ITEM);
																			item->SetId(object->GetId());
																			_pQuadTree->InsertObject(item);
																		}
																	else
																		if (name == "Wall")
																			for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
																			{
																				const auto object = objectGroup->GetObjects().at(j);

																				auto* entity = new BaseObject();
																				entity->SetPositionStart(object->GetX() + object->GetWidth() / 2.0f, object->GetY() + object->GetHeight() / 2.0f);
																				entity->SetPosition(entity->getPositionStart());
																				entity->SetWidth(object->GetWidth());
																				entity->SetHeight(object->GetHeight());

																				entity->SetObjectType(BaseObject::STATIC);
																				entity->SetId(object->GetId());
																				_pQuadTree->InsertObject(entity);
																			}
	}
}

void GameMap::SetCamera(Camera * camera)
{
	_pCamera = camera;
}

Tmx::Map* GameMap::GetMap() const
{
	return _pTmxMap;
}

RECT GameMap::GetWorldMapBound() const
{
	RECT bound;
	bound.left = bound.top = 0;
	bound.right = GetWidth();
	bound.bottom = GetHeight();

	return bound;
}

int GameMap::GetWidth() const
{
	return _pTmxMap->GetWidth()* _pTmxMap->GetTileWidth();
}

int GameMap::GetHeight() const
{
	return _pTmxMap->GetHeight()* _pTmxMap->GetTileHeight();
}

int GameMap::GetTileWidth() const
{
	return _pTmxMap->GetTileWidth();
}

int GameMap::GetTileHeight() const
{
	return _pTmxMap->GetTileHeight();
}

bool GameMap::IsBoundLeft() const
{
	return (_pCamera->GetBound().left == 0);
}

bool GameMap::IsBoundRight() const
{
	return (_pCamera->GetBound().right == this->GetWidth());
}

bool GameMap::IsBoundTop() const
{
	return (_pCamera->GetBound().top == 0);
}

bool GameMap::IsBoundBottom() const
{
	return (_pCamera->GetBound().bottom == this->GetHeight());
}

void GameMap::Update(float dt)
{

}

void GameMap::Draw()
{
	GVec3 position = _pCamera->GetPosition();
	_sourceRect.top = position.y - _tileMap->GetHeight() / 2;
	_sourceRect.bottom = position.y + _tileMap->GetHeight() / 2;
	_sourceRect.left = position.x - _tileMap->GetWidth() / 2;
	_sourceRect.right = position.x + _tileMap->GetWidth() / 2;

	_tileMap->Draw(position, _sourceRect, GVec2(), _pCamera->GetTrans());
}

void GameMap::Draw1()
{
	_tileMap1->Draw(_pCamera->GetPosition(), _sourceRect, GVec2(), _pCamera->GetTrans());
}

std::vector<BaseObject*> GameMap::GetListEnemies() const
{
	return _listEnemies;
}

std::vector<RECT> GameMap::GetListRoom() const
{
	return _listRoom;
}

QuadTree* GameMap::GetQuadTree() const
{
	return _pQuadTree;
}

void GameMap::SetPlayer(Player* player)
{
	_pPlayer = player;
}
