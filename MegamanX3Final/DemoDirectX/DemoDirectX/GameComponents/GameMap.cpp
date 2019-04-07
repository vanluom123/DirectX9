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
#include "../GameObjects/Item/EnergyHeartItem.h"

GameMap::GameMap(const char* filePath)
{
	pTmxMap = new Tmx::Map();
	pTmxMap->ParseFile(filePath);

	TileMap = new Sprite(Define::WORLD_MAP_PNG, RECT(), this->getWidth(), this->getHeight(), D3DCOLOR_XRGB(255, 255, 255));
	TileMap->setWidth(GameGlobal::getWidth() + 4);
	TileMap->setHeight(GameGlobal::getHeight() + 4);

	TileMap1 = new Sprite("Resources/Map/Stage.png", RECT(), this->getWidth(), this->getHeight(), D3DCOLOR_XRGB(0, 0, 0));
	TileMap1->setWidth(GameGlobal::getWidth() + 4);
	TileMap1->setHeight(GameGlobal::getHeight() + 4);

	RECT r;
	r.left = 0;
	r.top = 0;
	r.right = this->getWidth();
	r.bottom = this->getHeight();

	pQuadTree = new QuadTree(1, r);
}

GameMap::~GameMap()
{
	delete pTmxMap;
	delete TileMap;
	delete TileMap1;
	for (auto& mListBrick : ListEnemies)
		delete mListBrick;
	ListEnemies.clear();

	delete pQuadTree;
}

void GameMap::LoadMap()
{
	//Object static
	for (size_t i = 0; i < pTmxMap->GetNumObjectGroups(); i++)
	{
		const auto objectGroup = pTmxMap->GetObjectGroup(i);
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

				ListRoom.push_back(room);
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

					boss->SetTag(Entity::BOSS);
					boss->id = object->GetId();

					ListEnemies.push_back(boss);
					pQuadTree->insertObject(boss);
				}
			else
				if (name == "Boss2")
					for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
					{
						const auto object = objectGroup->GetObjects().at(j);

						auto* boss = new Planet(gp);
						boss->SetPositionStart(object->GetX() + object->GetWidth() / 2.0f, object->GetY() + object->GetHeight() / 2.0f);
						boss->SetPosition(boss->getPositionStart().x, boss->getPositionStart().y - object->GetHeight() + 1);

						boss->SetWidth(object->GetWidth());
						boss->SetHeight(object->GetHeight());

						boss->SetTag(Entity::BOSS);
						boss->id = object->GetId();

						ListEnemies.push_back(boss);
						pQuadTree->insertObject(boss);
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

							boss->SetTag(Entity::BOSS);
							boss->id = object->GetId();

							ListEnemies.push_back(boss);
							pQuadTree->insertObject(boss);
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

								banger->SetTag(Entity::ENEMY);
								banger->id = object->GetId();

								ListEnemies.push_back(banger);
								pQuadTree->insertObject(banger);
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

									gunner->SetTag(Entity::ENEMY);
									gunner->id = object->GetId();

									ListEnemies.push_back(gunner);
									pQuadTree->insertObject(gunner);
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

										helit->SetTag(Entity::ENEMY);
										helit->id = object->GetId();

										ListEnemies.push_back(helit);
										pQuadTree->insertObject(helit);
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

											elevator->SetTag(Entity::ELEVATOR);
											elevator->id = object->GetId();

											pQuadTree->insertObject(elevator);
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

												conveyor->SetTag(Entity::CONVEYOR);
												conveyor->id = object->GetId();

												pQuadTree->insertObject(conveyor);
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

													conveyor->SetTag(Entity::CONVEYOR);
													conveyor->id = object->GetId();

													pQuadTree->insertObject(conveyor);
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

														port->SetTag(Entity::PORT);
														port->id = object->GetId();

														pQuadTree->insertObject(port);
													}
												else
													if (name == "Thorn")
														for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
														{
															const auto object = objectGroup->GetObjects().at(j);

															auto* entity = new Entity();
															entity->SetPositionStart(object->GetX() + object->GetWidth() / 2.0f, object->GetY() + object->GetHeight() / 2.0f);
															entity->SetPosition(entity->getPositionStart());
															entity->SetWidth(object->GetWidth());
															entity->SetHeight(object->GetHeight());

															entity->SetTag(Entity::THORN);
															entity->id = object->GetId();
															pQuadTree->insertObject(entity);
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

																boxx->SetTag(Entity::BOX);
																boxx->id = object->GetId();

																pQuadTree->insertObject(boxx);
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

																	boxx->SetTag(Entity::ENEMY);
																	boxx->id = object->GetId();
																	boxx->NewEntity();
																	pQuadTree->insertObject(boxx);
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

																		item->SetTag(Entity::ITEM);
																		item->id = object->GetId();
																		pQuadTree->insertObject(item);
																	}
																else
																	if (name == "Heart")
																		for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
																		{
																			const auto object = objectGroup->GetObjects().at(j);

																			auto* item = new EnergyHeartItem();
																			item->SetPositionStart(object->GetX() + object->GetWidth() / 2.0f, object->GetY() + object->GetHeight() / 2.0f - 1);
																			item->SetPosition(item->getPositionStart());

																			item->SetTag(Entity::ITEM);
																			item->id = object->GetId();
																			pQuadTree->insertObject(item);
																		}
																	else
																		if (name == "Wall")
																			for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
																			{
																				const auto object = objectGroup->GetObjects().at(j);

																				auto* entity = new Entity();
																				entity->SetPositionStart(object->GetX() + object->GetWidth() / 2.0f, object->GetY() + object->GetHeight() / 2.0f);
																				entity->SetPosition(entity->getPositionStart());
																				entity->SetWidth(object->GetWidth());
																				entity->SetHeight(object->GetHeight());

																				entity->SetTag(Entity::STATIC);
																				entity->id = object->GetId();
																				pQuadTree->insertObject(entity);
																			}
	}
}

void GameMap::setCamera(Camera * camera)
{
	pCamera = camera;
}

Tmx::Map* GameMap::getMap() const
{
	return pTmxMap;
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
	return pTmxMap->GetWidth()* pTmxMap->GetTileWidth();
}

int GameMap::getHeight() const
{
	return pTmxMap->GetHeight()* pTmxMap->GetTileHeight();
}

int GameMap::getTileWidth() const
{
	return pTmxMap->GetTileWidth();
}

int GameMap::getTileHeight() const
{
	return pTmxMap->GetTileHeight();
}

bool GameMap::IsBoundLeft() const
{
	return (pCamera->getBound().left == 0);
}

bool GameMap::IsBoundRight() const
{
	return (pCamera->getBound().right == this->getWidth());
}

bool GameMap::IsBoundTop() const
{
	return (pCamera->getBound().top == 0);
}

bool GameMap::IsBoundBottom() const
{
	return (pCamera->getBound().bottom == this->getHeight());
}

void GameMap::update(float dt)
{

}

void GameMap::draw()
{
	D3DXVECTOR3 position = pCamera->getPosition();
	sourceRECT.top = position.y - TileMap->getHeight() / 2;
	sourceRECT.bottom = position.y + TileMap->getHeight() / 2;
	sourceRECT.left = position.x - TileMap->getWidth() / 2;
	sourceRECT.right = position.x + TileMap->getWidth() / 2;

	TileMap->draw(position, sourceRECT, D3DXVECTOR2(), pCamera->getTrans());
}

void GameMap::draw1()
{
	TileMap1->draw(pCamera->getPosition(), sourceRECT, D3DXVECTOR2(), pCamera->getTrans());
}

std::vector<Entity*> GameMap::getListListEnemies() const
{
	return ListEnemies;
}

std::vector<RECT> GameMap::getListRoom() const
{
	return ListRoom;
}

QuadTree* GameMap::getQuadTree() const
{
	return pQuadTree;
}
