#include "GameMap.h"
#include "../GameObjects/MapObjects/BrickGold.h"
#include "../GameObjects/MapObjects/BrickNormal.h"
#include "GameCollision.h"
#include "GameGlobal.h"

GameMap::GameMap(char* filePath)
{
	mCamera = new Camera(GameGlobal::GetWidth(), GameGlobal::GetHeight());
	LoadMap(filePath);
}

GameMap::~GameMap()
{
	delete mMap;

	for (auto& mListBrick : mListBricks)
	{
		delete mListBrick;
	}
	mListBricks.clear();

	for (size_t i = 0; i < mListTileSet.size(); i++)
	{
		if (mListTileSet[i])
			delete mListTileSet[i];
	}
	mListTileSet.clear();

	delete mQuadTree;
}

void GameMap::LoadMap(char* filePath)
{
	mMap = new Tmx::Map();
	mMap->ParseFile(filePath);

	RECT r;
	r.left = 0;
	r.top = 0;
	r.right = this->GetWidth();
	r.bottom = this->GetHeight();

	mQuadTree = new QuadTree(1, r);

	for (size_t i = 0; i < mMap->GetNumTilesets(); i++)
	{
		const Tmx::Tileset *tileSet = mMap->GetTileset(i);

		Sprite *sprite = new Sprite(tileSet->GetImage()->GetSource().c_str());
		mListTileSet.insert(pair<int, Sprite*>(i, sprite));
	}

	//khoi tao cac khoi Brick (vien gach)
#pragma region -BRICK AND COIN LAYER-
	for (size_t i = 0; i < GetMap()->GetNumTileLayers(); i++)
	{
		const Tmx::TileLayer *layer = mMap->GetTileLayer(i);

		if (layer->IsVisible())
			continue;

		//xac dinh layer Brick bi an di de tu do tao ra cac vien gach trong game, nhung vien gach khong phai la 1 physic static nos co the bi pha huy duoc

		if (layer->GetName() == "brick" || layer->GetName() == "coin")
		{
			for (size_t j = 0; j < mMap->GetNumTilesets(); j++)
			{
				const Tmx::Tileset *tileSet = mMap->GetTileset(j);

				int tileWidth = mMap->GetTileWidth();
				int tileHeight = mMap->GetTileHeight();

				int tileSetWidth = tileSet->GetImage()->GetWidth() / tileWidth;
				int tileSetHeight = tileSet->GetImage()->GetHeight() / tileHeight;

				for (size_t m = 0; m < layer->GetHeight(); m++)
				{
					for (size_t n = 0; n < layer->GetWidth(); n++)
					{
						if (layer->GetTileTilesetIndex(n, m) != -1)
						{
							int tileID = layer->GetTileId(n, m);

							int y = tileID / tileSetWidth;
							int x = tileID - y * tileSetWidth;

							RECT sourceRECT;
							sourceRECT.top = y * tileHeight;
							sourceRECT.bottom = sourceRECT.top + tileHeight;
							sourceRECT.left = x * tileWidth;
							sourceRECT.right = sourceRECT.left + tileWidth;

							RECT bound;
							bound.left = n * tileWidth;
							bound.top = m * tileHeight;
							bound.right = bound.left + tileWidth;
							bound.bottom = bound.top + tileHeight;

							D3DXVECTOR3 position(n * tileWidth + tileWidth / 2.0f,
								m * tileHeight + tileHeight / 2.0f, 0);

							Brick *brick = nullptr;

							if (layer->GetName() == "coin")
							{
								brick = new BrickGold(position);
								brick->Tag = Entity::EntityTypes::BrickGoldNormal;
								mListBricks.push_back(brick);
							}
							else
							{
								brick = new BrickNormal(position);
								brick->Tag = Entity::EntityTypes::Brick;
								mListBricks.push_back(brick);
							}
							if (brick)
								mQuadTree->insertEntity(brick);
						}
					}
				}
			}
		}
	}

#pragma endregion

#pragma region -OBJECTGROUP, STATIC OBJECT-

	for (size_t i = 0; i < mMap->GetNumObjectGroups(); i++)
	{
		const Tmx::ObjectGroup *objectGroup = mMap->GetObjectGroup(i);

		for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
		{
			//lay object group chu khong phai layer
			//object group se chua nhung body
			Tmx::Object *object = objectGroup->GetObjects().at(j);

			auto*entity = new Entity();
			entity->SetPosition(object->GetX() + object->GetWidth() / 2.0f,
				object->GetY() + object->GetHeight() / 2.0f);

			entity->SetWidth(object->GetWidth());
			entity->SetHeight(object->GetHeight());

			entity->Tag = Entity::EntityTypes::Static;

			mQuadTree->insertEntity(entity);
		}
	}
#pragma endregion
}

void GameMap::SetCamera(Camera* camera)
{
	mCamera = camera;
}

Tmx::Map* GameMap::GetMap()
{
	return mMap;
}

RECT GameMap::GetWorldMapBound()
{
	RECT bound;
	bound.left = bound.top = 0;
	bound.right = GetWidth();
	bound.bottom = GetHeight();

	return bound;
}

int GameMap::GetWidth()
{
	return mMap->GetWidth() * mMap->GetTileWidth();
}

int GameMap::GetHeight()
{
	return mMap->GetHeight() * mMap->GetTileHeight();
}

int GameMap::GetTileWidth()
{
	return mMap->GetTileWidth();
}

int GameMap::GetTileHeight()
{
	return mMap->GetTileHeight();
}

bool GameMap::IsBoundLeft()
{
	return (mCamera->GetBound().left == 0);
}

bool GameMap::IsBoundRight()
{
	return (mCamera->GetBound().right == this->GetWidth());
}

bool GameMap::IsBoundTop()
{
	return (mCamera->GetBound().top == 0);
}

bool GameMap::IsBoundBottom()
{
	return (mCamera->GetBound().bottom == this->GetHeight());
}

void GameMap::Update(float dt)
{
	for (auto& mListBrick : mListBricks)
	{
		mListBrick->Update(dt);
	}
}

void GameMap::Draw()
{
	D3DXVECTOR2 trans = D3DXVECTOR2(GameGlobal::GetWidth() / 2.0f - mCamera->GetPosition().x,
		GameGlobal::GetHeight() / 2.0f - mCamera->GetPosition().y);

#pragma region DRAW TILESET
	for (size_t i = 0; i < mMap->GetNumTileLayers(); i++)
	{
		const Tmx::TileLayer *layer = mMap->GetTileLayer(i);

		if (!layer->IsVisible())
			continue;

		for (size_t j = 0; j < mMap->GetNumTilesets(); j++)
		{
			const Tmx::Tileset *tileSet = mMap->GetTileset(j);

			RECT sourceRECT;

			int tileWidth = mMap->GetTileWidth();
			int tileHeight = mMap->GetTileHeight();

			int tileSetWidth = tileSet->GetImage()->GetWidth() / tileWidth;
			int tileSetHeight = tileSet->GetImage()->GetHeight() / tileHeight;

			for (size_t m = 0; m < layer->GetHeight(); m++)
			{
				for (size_t n = 0; n < layer->GetWidth(); n++)
				{
					if (layer->GetTileTilesetIndex(n, m) != -1)
					{
						int tileID = layer->GetTileId(n, m);

						int y = tileID / tileSetWidth;
						int x = tileID - y * tileSetWidth;

						sourceRECT.top = y * tileHeight;
						sourceRECT.bottom = sourceRECT.top + tileHeight;
						sourceRECT.left = x * tileWidth;
						sourceRECT.right = sourceRECT.left + tileWidth;

						Sprite* sprite = mListTileSet[j];

						D3DXVECTOR3 position(n * tileWidth + tileWidth / 2.0f, m * tileHeight + tileHeight / 2.0f, 0);

						if (mCamera != NULL)
						{
							RECT objRECT;
							objRECT.left = position.x - tileWidth / 2.0f;
							objRECT.top = position.y - tileHeight / 2.0f;
							objRECT.right = objRECT.left + tileWidth;
							objRECT.bottom = objRECT.top + tileHeight;

							if (!GameCollision::RectAndRect(mCamera->GetBound(), objRECT).IsCollided)
								continue;
						}

						sprite->SetWidth(tileWidth);
						sprite->SetHeight(tileHeight);

						sprite->Draw(position, sourceRECT, D3DXVECTOR2(), trans);
					}
				}
			}
		}
	}
#pragma endregion

#pragma region DRAW BRICK

	for (auto& mListBrick : mListBricks)
	{
		mListBrick->Draw(trans);
	}

#pragma endregion
}

std::map<int, Sprite*> GameMap::getListTileSet()
{
	return mListTileSet;
}

std::vector<Brick*> GameMap::GetListBrick()
{
	return mListBricks;
}

QuadTree * GameMap::GetQuadTree()
{
	return mQuadTree;
}
