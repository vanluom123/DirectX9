#include "GameMap.h"
#include "GameGlobal.h"
#include "BrickGold.h"
#include "BrickNormal.h"

GameMap::GameMap(const char* filePath) : mMap(NULL), mCamera(NULL)
{
	LoadMap(filePath);
}

void GameMap::Update(float dt)
{
	for (auto& mListBrick : mListBricks)
		mListBrick->Update(dt);
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

RECT GameMap::GetWorldMapBound()
{
	RECT bound;
	bound.left = bound.top = 0;
	bound.right = this->GetWidth();
	bound.bottom = this->GetHeight();
	return bound;
}

GameMap::~GameMap()
{
	delete mMap;

	for (auto& mListBrick : mListBricks)
	{
		delete mListBrick;
	}

	mListBricks.clear();

	for (size_t i = 0; i < mListTilesSet.size(); ++i)
	{
		if (mListTilesSet[i])
			delete mListTilesSet[i];
	}

	mListTilesSet.clear();
}

void GameMap::LoadMap(const char* filePath)
{
	mMap = new Tmx::Map();
	mMap->ParseFile(filePath);

	RECT r;
	r.left = 0;
	r.top = 0;
	r.right = this->GetWidth();
	r.bottom = this->GetHeight();


	for (INT i = 0; i < mMap->GetNumTilesets(); i++)
	{
		const Tmx::Tileset *tile_set = mMap->GetTileset(i);

		Sprite *sprite = new Sprite(tile_set->GetImage()->GetSource().c_str());

		mListTilesSet.insert(std::pair<int, Sprite*>(i, sprite));
	}

	// Initialize bricks
#pragma region BRICK AND COIN PLAYER
	for (int i = 0; i < mMap->GetNumTileLayers(); i++)
	{
		const Tmx::TileLayer* layer = mMap->GetTileLayer(i);

		if (layer->IsVisible())
			continue;

		// To confirm Brick Layer is hidden to free creating bricks in game, But bricks don't a "Physic static". It can be destroy  
		if (layer->GetName() == "brick" || layer->GetName() == "coin")
		{
			for (int j = 0; j < mMap->GetNumTilesets(); j++)
			{
				const Tmx::Tileset* tile_set = mMap->GetTileset(j);

				int tile_width = mMap->GetWidth();
				int tile_height = mMap->GetHeight();

				int tile_set_width = tile_set->GetImage()->GetWidth() / tile_width;
				int tile_set_height = tile_set->GetImage()->GetHeight() / tile_height;


				for (int m = 0; m < mMap->GetHeight(); m++)
				{
					for (int n = 0; n < mMap->GetWidth(); n++)
					{
						if (layer->GetTileTilesetIndex(n, m) != -1)
						{
							int tile_id = layer->GetTileId(n, m);

							int y = tile_id / tile_set_width;
							int x = tile_id - y * tile_set_width;

							RECT source_rect;
							source_rect.left = x * tile_width;
							source_rect.top = y * tile_height;
							source_rect.right = source_rect.left + tile_width;
							source_rect.bottom = source_rect.top + tile_height;

							RECT bound;
							bound.left = n * tile_width;
							bound.top = m * tile_height;
							bound.right = bound.left + tile_width;
							bound.bottom = bound.top + tile_height;

							D3DXVECTOR3 position(n*tile_width + float(tile_width) / 2, m*tile_height + float(tile_height) / 2, 0);

							Brick* bricks = NULL;
							if (layer->GetName() == "coin")	// If layer's name is "Coin". Layer's tag will be BrickGoldNormal
							{
								bricks = new BrickGold(position);
								bricks->Tag = Entity::EntityTypes::BrickGoldNormal;
								mListBricks.push_back(bricks);
							}
							else
							{
								bricks = new BrickNormal(position);
								bricks->Tag = Entity::EntityTypes::Brick;
								mListBricks.push_back(bricks);
							}
						}
					}
				}
			}
		}
	}
#pragma endregion 
}

bool GameMap::isContain(RECT rect1, RECT rect2)
{
	return !(rect1.left > rect2.right || rect1.right < rect2.left || rect1.top > rect2.bottom || rect1.bottom < rect2.
		top);
}

Tmx::Map* GameMap::GetMap()
{
	return mMap;
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

void GameMap::Draw()
{
	D3DXVECTOR2 trans = D3DXVECTOR2(float(GameGlobal::GetWidth()) / 2 - mCamera->GetPosition().x,
		float(GameGlobal::GetHeight()) / 2 - mCamera->GetPosition().y);

#pragma region DRAW TILESET
	for (int i = 0; i < mMap->GetNumTileLayers(); i++)
	{
		const Tmx::TileLayer *layer = mMap->GetTileLayer(i);

		if (!layer->IsVisible())
			continue;

		for (int j = 0; j < mMap->GetNumTilesets(); j++)
		{
			const Tmx::Tileset* tile_set = mMap->GetTileset(j);

			RECT source_rect;

			int tile_width = mMap->GetTileWidth();
			int tile_height = mMap->GetTileHeight();

			int tile_set_width = tile_set->GetImage()->GetWidth() / tile_width;
			int tile_set_height = tile_set->GetImage()->GetHeight() / tile_height;

			for (int m = 0; m < mMap->GetHeight(); m++)
			{
				for (int n = 0; n < mMap->GetWidth(); n++)
				{
					if (layer->GetTileTilesetIndex(n, m) != -1)
					{
						int tile_id = layer->GetTileId(n, m);

						int y = tile_id / tile_set_width;
						int x = tile_id - y * tile_set_width;

						
						source_rect.left = x * tile_width;
						source_rect.top = y * tile_height;
						source_rect.right = source_rect.left + tile_width;
						source_rect.bottom = source_rect.top + tile_height;

						Sprite* sprite = mListTilesSet[j];

						D3DXVECTOR3 position(n*tile_width + float(tile_width) / 2, m*tile_height + float(tile_height) / 2, 0);

						if (mCamera != NULL)
						{
							RECT objRECT;
							objRECT.left = long(position.x - float(tile_width) / 2);
							objRECT.top = long(position.y - float(tile_height) / 2);
							objRECT.right = objRECT.left + tile_width;
							objRECT.bottom = objRECT.top + tile_height;

							if (!isContain(mCamera->GetBound(), objRECT))
								continue;
						}

						sprite->SetWidth(tile_width);
						sprite->SetHeight(tile_height);
						sprite->Draw(position, source_rect, D3DXVECTOR2(), trans);
					}
				}
			}
		}
	}

#pragma endregion 

#pragma region DRAW BRICK
	for (auto& mListBrick : mListBricks)
		mListBrick->Draw(trans);
#pragma endregion 
}

void GameMap::SetCamera(Camera * camera)
{
	this->mCamera = camera;
}
