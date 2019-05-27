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
	m_tmxMap = new Tmx::Map();
	m_tmxMap->ParseFile(filePath);

	m_tileMap = new Sprite(Define::WORLD_MAP_PNG, RECT(), this->GetWidth(), this->GetHeight(), D3DCOLOR_XRGB(255, 255, 255));
	m_tileMap->SetWidth(GameGlobal::GetWidth() + 4);
	m_tileMap->SetHeight(GameGlobal::GetHeight() + 4);

	m_tileMap1 = new Sprite("Resources/Map/Stage.png", RECT(), this->GetWidth(), this->GetHeight(), D3DCOLOR_XRGB(0, 0, 0));
	m_tileMap1->SetWidth(GameGlobal::GetWidth() + 4);
	m_tileMap1->SetHeight(GameGlobal::GetHeight() + 4);

	RECT r;
	r.left = 0;
	r.top = 0;
	r.right = this->GetWidth();
	r.bottom = this->GetHeight();

	m_quadTree = new QuadTree(1, r);
}

GameMap::~GameMap()
{
	delete m_tmxMap;
	delete m_tileMap;
	delete m_tileMap1;
	for (auto& mListBrick : m_listEnemies)
		delete mListBrick;
	m_listEnemies.clear();

	delete m_quadTree;
}

void GameMap::LoadMap()
{
	// Object static
	for (size_t i = 0; i < (size_t)m_tmxMap->GetNumObjectGroups(); i++)
	{
		const auto objectGroup = m_tmxMap->GetObjectGroup(i);
		string name = objectGroup->GetName();

		if (name == "Room")
			for (size_t j = 0; j < (size_t)objectGroup->GetNumObjects(); j++)
			{
				const auto object = objectGroup->GetObjects().at(j);
				RECT room;
				room.left = object->GetX();
				room.top = object->GetY();
				room.right = object->GetX() + object->GetWidth();
				room.bottom = object->GetY() + object->GetHeight();

				m_listRoom.push_back(room);
			}
		else

			if (name == "Boss1")
				for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
				{
					const auto object = objectGroup->GetObjects().at(j);

					auto* boss = new Genjibo();
					boss->SetPositionStart(object->GetX() + object->GetWidth() / 2.0f, object->GetY());
					boss->SetPosition(boss->GetPositionStart());

					boss->SetWidth(object->GetWidth());
					boss->SetHeight(object->GetHeight());

					boss->SetObjectType(BaseObject::OBJECT_BOSS);
					boss->SetId(object->GetId());

					m_listEnemies.push_back(boss);
					m_quadTree->InsertObject(boss);
				}
			else
				if (name == "Boss2")
					for (size_t j = 0; j < (size_t)objectGroup->GetNumObjects(); j++)
					{
						const auto object = objectGroup->GetObjects().at(j);

						auto* boss = new Planet(m_player);
						boss->SetPositionStart(object->GetX() + object->GetWidth() / 2.0f, object->GetY() + object->GetHeight() / 2.0f);
						boss->SetPosition(boss->GetPositionStart().x, boss->GetPositionStart().y - object->GetHeight() + 1);

						boss->SetWidth(object->GetWidth());
						boss->SetHeight(object->GetHeight());

						boss->SetObjectType(BaseObject::OBJECT_BOSS);
						boss->SetId(object->GetId());

						m_listEnemies.push_back(boss);
						m_quadTree->InsertObject(boss);
					}
				else
					if (name == "Boss3")
						for (size_t j = 0; j < (size_t)objectGroup->GetNumObjects(); j++)
						{
							const auto object = objectGroup->GetObjects().at(j);

							auto* boss = new BlastHornet();
							boss->SetPositionStart(object->GetX() + object->GetWidth() / 2.0f, object->GetY() + object->GetHeight() / 2.0f);
							boss->SetPosition(boss->GetPositionStart());

							boss->SetWidth(object->GetWidth());
							boss->SetHeight(object->GetHeight());

							boss->SetObjectType(BaseObject::OBJECT_BOSS);
							boss->SetId(object->GetId());

							m_listEnemies.push_back(boss);
							m_quadTree->InsertObject(boss);
						}
					else
						if (name == "Banger")
							for (size_t j = 0; j < (size_t)objectGroup->GetNumObjects(); j++)
							{
								const auto object = objectGroup->GetObjects().at(j);

								auto* banger = new Banger();
								banger->SetPositionStart(object->GetX() + object->GetWidth() / 2.0f, object->GetY() + 7);
								banger->SetPosition(banger->GetPositionStart());

								banger->SetWidth(object->GetWidth());
								banger->SetHeight(object->GetHeight());

								banger->SetObjectType(BaseObject::OBJECT_ENEMY);
								banger->SetId(object->GetId());

								m_listEnemies.push_back(banger);
								m_quadTree->InsertObject(banger);
							}
						else
							if (name == "Gunner")
								for (size_t j = 0; j < (size_t)objectGroup->GetNumObjects(); j++)
								{
									const auto object = objectGroup->GetObjects().at(j);

									auto* gunner = new Gunner();
									gunner->SetPositionStart(object->GetX() + object->GetWidth() / 2.0f, object->GetY() - 1 + gunner->GetHeight() / 2.0f);
									gunner->SetPosition(gunner->GetPositionStart());

									gunner->SetWidth(object->GetWidth());
									gunner->SetHeight(object->GetHeight());

									gunner->SetObjectType(BaseObject::OBJECT_ENEMY);
									gunner->SetId(object->GetId());

									m_listEnemies.push_back(gunner);
									m_quadTree->InsertObject(gunner);
								}
							else
								if (name == "Helit")
									for (size_t j = 0; j < (size_t)objectGroup->GetNumObjects(); j++)
									{
										const auto object = objectGroup->GetObjects().at(j);

										auto* helit = new Helit();
										helit->SetPositionStart(object->GetX() + object->GetWidth() / 2.0f, object->GetY() - 1 + helit->GetHeight() / 2.0f);
										helit->SetPosition(helit->GetPositionStart());

										helit->SetWidth(object->GetWidth());
										helit->SetHeight(object->GetHeight());

										helit->SetObjectType(BaseObject::OBJECT_ENEMY);
										helit->SetId(object->GetId());

										m_listEnemies.push_back(helit);
										m_quadTree->InsertObject(helit);
									}
								else
									if (name == "Elevator")
										for (size_t j = 0; j < (size_t)objectGroup->GetNumObjects(); j++)
										{
											const auto object = objectGroup->GetObjects().at(j);

											auto* elevator = new Elevator();
											elevator->SetPositionStart(object->GetX() + object->GetWidth() / 2.0f, object->GetY() + object->GetHeight() / 2.0f + 1);
											elevator->SetPosition(elevator->GetPositionStart());

											elevator->SetWidth(object->GetWidth());
											elevator->SetHeight(object->GetHeight());

											elevator->SetObjectType(BaseObject::OBJECT_ELEVATOR);
											elevator->SetId(object->GetId());

											m_quadTree->InsertObject(elevator);
										}
									else
										if (name == "ConveyorR")
											for (size_t j = 0; j < (size_t)objectGroup->GetNumObjects(); j++)
											{
												const auto object = objectGroup->GetObjects().at(j);

												auto* conveyor = new Conveyor(false);
												conveyor->SetPositionStart(object->GetX() + object->GetWidth() / 2.0f, object->GetY() + object->GetHeight() / 2.0f);
												conveyor->SetPosition(conveyor->GetPositionStart());

												conveyor->SetWidth(object->GetWidth());
												conveyor->SetHeight(object->GetHeight());

												conveyor->SetObjectType(BaseObject::OBJECT_CONVEYOR);
												conveyor->SetId(object->GetId());

												m_quadTree->InsertObject(conveyor);
											}
										else
											if (name == "ConveyorL")
												for (size_t j = 0; j < (size_t)objectGroup->GetNumObjects(); j++)
												{
													const auto object = objectGroup->GetObjects().at(j);

													auto* conveyor = new Conveyor(true);
													conveyor->SetPositionStart(object->GetX() + object->GetWidth() / 2.0f, object->GetY() + object->GetHeight() / 2.0f);
													conveyor->SetPosition(conveyor->GetPositionStart());

													conveyor->SetWidth(object->GetWidth());
													conveyor->SetHeight(object->GetHeight());

													conveyor->SetObjectType(BaseObject::OBJECT_CONVEYOR);
													conveyor->SetId(object->GetId());

													m_quadTree->InsertObject(conveyor);
												}
											else
												if (name == "Port")
													for (size_t j = 0; j < (size_t)objectGroup->GetNumObjects(); j++)
													{
														const auto object = objectGroup->GetObjects().at(j);

														auto* port = new Port();
														port->SetPositionStart(object->GetX() + object->GetWidth() / 2.0f, object->GetY() + object->GetHeight() / 2.0f);
														port->SetPosition(port->GetPositionStart());

														port->SetWidth(object->GetWidth());
														port->SetHeight(object->GetHeight());

														port->SetObjectType(BaseObject::OBJECT_PORT);
														port->SetId(object->GetId());

														m_quadTree->InsertObject(port);
													}
												else
													if (name == "Thorn")
														for (size_t j = 0; j < (size_t)objectGroup->GetNumObjects(); j++)
														{
															const auto object = objectGroup->GetObjects().at(j);

															auto* entity = new BaseObject();
															entity->SetPositionStart(object->GetX() + object->GetWidth() / 2.0f, object->GetY() + object->GetHeight() / 2.0f);
															entity->SetPosition(entity->GetPositionStart());
															entity->SetWidth(object->GetWidth());
															entity->SetHeight(object->GetHeight());

															entity->SetObjectType(BaseObject::OBJECT_THORN);
															entity->SetId(object->GetId());
															m_quadTree->InsertObject(entity);
														}
													else
														if (name == "Box")
															for (size_t j = 0; j < (size_t)objectGroup->GetNumObjects(); j++)
															{
																const auto object = objectGroup->GetObjects().at(j);

																auto* boxx = new Box();
																boxx->SetPositionStart(object->GetX() + object->GetWidth() / 2.0f, object->GetY() + object->GetHeight() / 2.0f);
																boxx->SetPosition(boxx->GetPositionStart());

																boxx->SetWidth(object->GetWidth());
																boxx->SetHeight(object->GetHeight());

																boxx->SetObjectType(BaseObject::OBJECT_BOX);
																boxx->SetId(object->GetId());

																m_quadTree->InsertObject(boxx);
															}
														else
															if (name == "Box1")
																for (size_t j = 0; j < (size_t)objectGroup->GetNumObjects(); j++)
																{
																	const auto object = objectGroup->GetObjects().at(j);

																	auto* boxx = new Box(true);
																	boxx->SetPositionStart(object->GetX() + object->GetWidth() / 2.0f, object->GetY() + object->GetHeight() / 2.0f);
																	boxx->SetPosition(boxx->GetPositionStart());

																	boxx->SetWidth(object->GetWidth());
																	boxx->SetHeight(object->GetHeight());

																	boxx->SetObjectType(BaseObject::OBJECT_ENEMY);
																	boxx->SetId(object->GetId());
																	boxx->NewEntity();
																	m_quadTree->InsertObject(boxx);
																}
															else
																if (name == "Blood")
																	for (size_t j = 0; j < (size_t)objectGroup->GetNumObjects(); j++)
																	{
																		const auto object = objectGroup->GetObjects().at(j);

																		auto* item = new BigBloodItem();
																		item->SetPositionStart(object->GetX() + object->GetWidth() / 2.0f, object->GetY() + object->GetHeight() / 2.0f - 1);
																		item->SetPosition(item->GetPositionStart());

																		item->SetWidth(object->GetWidth());
																		item->SetHeight(object->GetHeight());

																		item->SetObjectType(BaseObject::OBJECT_ITEM);
																		item->SetId(object->GetId());
																		m_quadTree->InsertObject(item);
																	}
																else
																	if (name == "Heart")
																		for (size_t j = 0; j < (size_t)objectGroup->GetNumObjects(); j++)
																		{
																			const auto object = objectGroup->GetObjects().at(j);

																			auto* item = new EnergyItem();
																			item->SetPositionStart(object->GetX() + object->GetWidth() / 2.0f, object->GetY() + object->GetHeight() / 2.0f - 1);
																			item->SetPosition(item->GetPositionStart());

																			item->SetObjectType(BaseObject::OBJECT_ITEM);
																			item->SetId(object->GetId());
																			m_quadTree->InsertObject(item);
																		}
																	else
																		if (name == "Wall")
																			for (size_t j = 0; j < (size_t)objectGroup->GetNumObjects(); j++)
																			{
																				const auto object = objectGroup->GetObjects().at(j);

																				auto* entity = new BaseObject();
																				entity->SetPositionStart(object->GetX() + object->GetWidth() / 2.0f, object->GetY() + object->GetHeight() / 2.0f);
																				entity->SetPosition(entity->GetPositionStart());
																				entity->SetWidth(object->GetWidth());
																				entity->SetHeight(object->GetHeight());

																				entity->SetObjectType(BaseObject::OBJECT_STATIC);
																				entity->SetId(object->GetId());
																				m_quadTree->InsertObject(entity);
																			}
	}
}

void GameMap::SetCamera(Camera * camera)
{
	m_camera = camera;
}

Tmx::Map* GameMap::GetMap() const
{
	return m_tmxMap;
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
	return m_tmxMap->GetWidth() * m_tmxMap->GetTileWidth();
}

int GameMap::GetHeight() const
{
	return m_tmxMap->GetHeight() * m_tmxMap->GetTileHeight();
}

int GameMap::GetTileWidth() const
{
	return m_tmxMap->GetTileWidth();
}

int GameMap::GetTileHeight() const
{
	return m_tmxMap->GetTileHeight();
}

bool GameMap::IsBoundLeft() const
{
	return (m_camera->GetBound().left == 0);
}

bool GameMap::IsBoundRight() const
{
	return (m_camera->GetBound().right == this->GetWidth());
}

bool GameMap::IsBoundTop() const
{
	return (m_camera->GetBound().top == 0);
}

bool GameMap::IsBoundBottom() const
{
	return (m_camera->GetBound().bottom == this->GetHeight());
}

void GameMap::Update(float dt)
{

}

void GameMap::Draw()
{
	GVec3 position = m_camera->GetPosition();
	m_sourceRect.top = position.y - m_tileMap->GetHeight() / 2;
	m_sourceRect.bottom = position.y + m_tileMap->GetHeight() / 2;
	m_sourceRect.left = position.x - m_tileMap->GetWidth() / 2;
	m_sourceRect.right = position.x + m_tileMap->GetWidth() / 2;

	m_tileMap->Draw(position, m_sourceRect, GVec2(), m_camera->GetTrans());
}

void GameMap::Draw1()
{
	m_tileMap1->Draw(m_camera->GetPosition(), m_sourceRect, GVec2(), m_camera->GetTrans());
}

std::vector<BaseObject*> GameMap::GetListEnemies() const
{
	return m_listEnemies;
}

std::vector<RECT> GameMap::GetListRoom() const
{
	return m_listRoom;
}

QuadTree* GameMap::GetQuadTree() const
{
	return m_quadTree;
}

void GameMap::SetPlayer(Player* player)
{
	m_player = player;
}
