#include "GameMap.h"
#include "GameGlobal.h"

GameMap::GameMap(const char* filePath)
{
	LoadMap(filePath);
}

GameMap::~GameMap()
{
	if(mCamera)
	{
		delete mCamera;
		mCamera = nullptr;
	}

	if(mMap)
	{
		delete mMap;
		mMap = nullptr;
	}
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

	for (int i = 0; i < mMap->GetNumTilesets(); i++)
	{
		const Tmx::Tileset *tileSet = mMap->GetTileset(i);

		Sprite *sprite = new Sprite(tileSet->GetImage()->GetSource().c_str());

		mListTileset.insert(std::pair<int, Sprite*>(i, sprite));
	}
}

bool GameMap::isContain(RECT rect1, RECT rect2)
{
	return !(rect1.left > rect2.right || rect1.right < rect2.left || rect1.top > rect2.bottom || rect1.bottom < rect2.
		top);
}

Tmx::Map* GameMap::GetMap() const
{
	return mMap;
}

int GameMap::GetWidth() const
{
	return mMap->GetWidth() * mMap->GetTileWidth();
}

int GameMap::GetHeight() const
{
	return mMap->GetHeight() * mMap->GetTileHeight();
}

int GameMap::GetTileWidth() const
{
	return mMap->GetTileWidth();
}

int GameMap::GetTileHeight() const
{
	return mMap->GetTileHeight();
}

void GameMap::Draw()
{
	const D3DXVECTOR2 trans = D3DXVECTOR2(float(GameGlobal::GetWidth()) / 2 - mCamera->GetPosition().x,
		float(GameGlobal::GetHeight()) / 2 - mCamera->GetPosition().y);

	for (int i = 0; i < mMap->GetNumTileLayers(); i++)
	{
		const Tmx::TileLayer *layer = mMap->GetTileLayer(i);

		if (!layer->IsVisible())
			continue;

		RECT sourceRECT;

		const int tileWidth = mMap->GetTileWidth();
		const int tileHeight = mMap->GetTileHeight();

		for (int m = 0; m < layer->GetHeight(); m++)
		{
			for (int n = 0; n < layer->GetWidth(); n++)
			{
				const int tileSetIndex = layer->GetTileTilesetIndex(n, m);

				if (tileSetIndex != -1)
				{
					const Tmx::Tileset *tileSet = mMap->GetTileset(tileSetIndex);

					const int tileSetWidth = tileSet->GetImage()->GetWidth() / tileWidth;
					int tileSetHeight = tileSet->GetImage()->GetHeight() / tileHeight;

					Sprite* sprite = mListTileset[layer->GetTileTilesetIndex(n, m)];

					//tile index
					const int tileID = layer->GetTileId(n, m);

					int y = tileID / tileSetWidth;
					int x = tileID - y * tileSetWidth;

					sourceRECT.top = y * tileHeight;
					sourceRECT.bottom = sourceRECT.top + tileHeight;
					sourceRECT.left = x * tileWidth;
					sourceRECT.right = sourceRECT.left + tileWidth;

					//tru tileWidth/2 va tileHeight/2 vi Sprite ve o vi tri giua hinh anh cho nen doi hinh de cho
					//dung toa do (0,0) cua the gioi thuc la (0,0) neu khong thi se la (-tileWidth/2, -tileHeigth/2);
					const D3DXVECTOR3 position(n * tileWidth + float(tileWidth) / 2, m * tileHeight + float(tileHeight) / 2, 0);

					if (mCamera != nullptr)
					{
						RECT objRECT;
						objRECT.left = long(position.x - float(tileWidth) / 2);
						objRECT.top = long(position.y - float(tileHeight) / 2);
						objRECT.right = objRECT.left + tileWidth;
						objRECT.bottom = objRECT.top + tileHeight;

						//neu nam ngoai camera thi khong Draw
						if (!isContain(objRECT, mCamera->GetBound()))
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

void GameMap::SetCamera(Camera * camera)
{
	this->mCamera = camera;
}
