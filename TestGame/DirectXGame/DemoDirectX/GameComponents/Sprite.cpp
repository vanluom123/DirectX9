#include "Sprite.h"
#include "GameGlobal.h"
#include "../GameDefines/GameDefine.h"
#include "../MapReader/tinyxml.h"
#include <iterator>

Sprite::Sprite(LPWSTR filePath, RECT sourceRect, int width, int height, D3DCOLOR colorKey)
{
	_Width = width;
	_Height = height;

	_SpriteHandler = GameGlobal::GetCurrentSpriteHandler();
	_Position = D3DXVECTOR3(0, 0, 0);
	_Rotation = 0;
	_RotationCenter = D3DXVECTOR2(_Position.x, _Position.y);
	_Translation = D3DXVECTOR2(0, 0);
	_Scale = D3DXVECTOR2(1, 1);

	auto result = D3DXGetImageInfoFromFile(filePath, &_ImageInfo);
	if (FAILED(result))
		return;

	if (width == 0)
	{
		if (!_IsRect(sourceRect))
			_Width = _ImageInfo.Width;
		else
			_Width = sourceRect.right - sourceRect.left;
	}

	if (height == 0)
	{
		if (!_IsRect(sourceRect))
			_Height = _ImageInfo.Height;
		else
			_Height = sourceRect.bottom - sourceRect.top;
	}

	if (!_IsRect(sourceRect))
	{
		_SourceRect.left = 0;
		_SourceRect.right = _Width;
		_SourceRect.top = 0;
		_SourceRect.bottom = _Height;
	}

	LPDIRECT3DDEVICE9 device;
	_SpriteHandler->GetDevice(&device);

	result = D3DXCreateSprite(device, &_SpriteHandler);
	if (FAILED(result))
		return;

	result = D3DXCreateTextureFromFileEx(
		device,
		filePath,
		_ImageInfo.Width,
		_ImageInfo.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		colorKey,
		&_ImageInfo,
		nullptr,
		&_Texture
	);
	if (FAILED(result))
		return;
}

Sprite::Sprite(LPWSTR ImagePath, const char * XMLPath, float AnimationRate, D3DCOLOR Transcolor)
{
	_SpriteHandler = GameGlobal::GetCurrentSpriteHandler();

	auto result = D3DXGetImageInfoFromFile(ImagePath, &_ImageInfo);
	if (FAILED(result))
	{
		MessageBox(nullptr, L"Failed to get information from image file\nPlease check path image.", L"Error", MB_OK);
		return;
	}

	LPDIRECT3DDEVICE9 device;
	_SpriteHandler->GetDevice(&device);

	result = D3DXCreateTextureFromFileEx(
		device,
		ImagePath,
		_ImageInfo.Width,
		_ImageInfo.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		Transcolor,
		&_ImageInfo,
		nullptr,
		&_Texture
	);
	if (FAILED(result))
	{
		MessageBox(nullptr, L"[ERROR] Failed to create texture from file", L"Error", MB_OK);
		return;
	}

	if(!ReadXML(XMLPath))
	{
		MessageBox(nullptr, L"Read file XML failed", L"Error", MB_OK);
		PostQuitMessage(0);
	}
}

Sprite::~Sprite()
{
	SAFE_RELEASE(_Texture);
}

bool Sprite::_IsRect(const RECT rect)
{
	if (rect.left == rect.right)
		return false;

	if (rect.top == rect.bottom)
		return false;

	return true;
}

int Sprite::GetWidth() const
{
	return _Width;
}

int Sprite::GetHeight() const
{
	return _Height;
}

void Sprite::Draw(D3DXVECTOR3 Position, RECT SourceRect, D3DXVECTOR2 Scale, D3DXVECTOR2 Translate, float Angle, D3DXVECTOR2 RotationCenter, D3DXCOLOR Transcolor)
{
	D3DXVECTOR3 inPosition = _Position;
	RECT inSourceRect = _SourceRect;
	float inRotation = _Rotation;
	D3DXVECTOR2 inScale = _Scale;
	D3DXVECTOR2 inTranslation = _Translation;
	D3DXVECTOR2 inRotationCenter = _RotationCenter;
	D3DXVECTOR2 scalingCenter = D3DXVECTOR2(inPosition.x, inPosition.y);
	inRotation = Angle * (3.14159265358979323846 / 180);

	if (Position != D3DXVECTOR3())
		inPosition = Position;

	if (_IsRect(SourceRect))
		inSourceRect = SourceRect;

	if (Scale != D3DXVECTOR2())
		inScale = Scale;

	if (Translate != D3DXVECTOR2())
		inTranslation = Translate;

	if (RotationCenter != D3DXVECTOR2())
		inRotationCenter = RotationCenter;
	else
		_RotationCenter = D3DXVECTOR2(inPosition.x, inPosition.y);

	D3DXMatrixTransformation2D(
		&_Matrix,
		&scalingCenter,
		0,
		&inScale,
		&inRotationCenter,
		inRotation,
		&inTranslation
	);

	D3DXMATRIX oldMatrix;
	_SpriteHandler->GetTransform(&oldMatrix);
	_SpriteHandler->SetTransform(&_Matrix);

	D3DXVECTOR3 center = D3DXVECTOR3(_Width / 2.0f, _Height / 2.0f, 0);

	_SpriteHandler->Draw(
		_Texture,
		&inSourceRect,
		&center,
		&inPosition,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);
	_SpriteHandler->SetTransform(&oldMatrix);
}

/**
 * \brief 
 * \param DeltaTime: Thời gian chuyển đổi giữa 2 frame 
 * \param X: Tọa độ trục hoành
 * \param Y: Tọa độ trục tung
 * \param ScaleSize: Tỉ lệ phóng đại
 * \param FlipX: Lật theo trục Ox, -1 là lật
 */
void Sprite::Render(float DeltaTime, float X, float Y, float ScaleSize, float FlipX)
{
	D3DXMATRIX combined;
	D3DXMATRIX scale;
	D3DXMATRIX translate;

	//Initialize the combined matrix
	D3DXMatrixIdentity(&combined);

	//Set location
	D3DXVECTOR3 position(X, Y, 0);

	//Scale the sprite
	D3DXMatrixScaling(&scale, FlipX * ScaleSize, ScaleSize, ScaleSize);
	combined *= scale;

	//Translate the sprite
	D3DXMatrixTranslation(&translate, X, Y, 0.0f);
	combined *= translate;

	_SpriteHandler->SetTransform(&combined);

	auto l_front = _ListTile.begin();
	std::advance(l_front, _IndexTile);

	RECT srect;
	srect.left = l_front->GetLocationTile().left;
	srect.top = l_front->GetLocationTile().top;
	srect.right = srect.left + l_front->GetLocationTile().right;
	srect.bottom = srect.top + l_front->GetLocationTile().bottom;

	auto center = D3DXVECTOR3((float)(srect.right - srect.left) / 2, (float)srect.bottom, 0);

	_SpriteHandler->Draw(_Texture, &srect, &center, nullptr, D3DCOLOR_XRGB(255, 255, 225));
}

bool Sprite::ReadXML(const char* XMLPath)
{
	TiXmlDocument doc(XMLPath);

	if (!doc.LoadFile())
	{
		MessageBox(NULL, L"Failed to read file XML\nPlease check path file XML", L"Error", MB_OK);
		return false;
	}

	// get info root
	TiXmlElement* root = doc.RootElement();
	TiXmlElement* tile = nullptr;

	//// loop to get element name, x, y, width, height
	for (tile = root->FirstChildElement(); tile != NULL; tile = tile->NextSiblingElement())
	{
		int x, y, w, h;
		const char* nameTileTemp;
		CTile TileTemp;

		// get value from file xml
		nameTileTemp = tile->Attribute("n");
		tile->QueryIntAttribute("x", &x);
		tile->QueryIntAttribute("y", &y);
		tile->QueryIntAttribute("w", &w);
		tile->QueryIntAttribute("h", &h);

		TileTemp.SetTile(nameTileTemp, x, y, w, h);

		// add into ListTile
		_ListTile.push_back(TileTemp);
	};

	return true;
}

void Sprite::SetSourceRect(RECT rect)
{
	_SourceRect = rect;
}

LPDIRECT3DTEXTURE9 Sprite::GetTexture() const
{
	return _Texture;
}

D3DXVECTOR3 Sprite::GetPosition() const
{
	return _Position;
}

void Sprite::SetPosition(float x, float y)
{
	SetPosition(D3DXVECTOR2(x, y));
}

void Sprite::SetPosition(D3DXVECTOR2 pos)
{
	SetPosition(D3DXVECTOR3(pos.x, pos.y, 0));
}

void Sprite::SetPosition(D3DXVECTOR3 pos)
{
	_Position = pos;
}

D3DXVECTOR2 Sprite::GetScale() const
{
	return _Scale;
}

void Sprite::SetScale(D3DXVECTOR2 scale)
{
	_Scale = scale;
}

D3DXVECTOR2 Sprite::GetTranslation() const
{
	return _Translation;
}

void Sprite::SetTranslation(D3DXVECTOR2 translation)
{
	_Translation = translation;
}

D3DXVECTOR2 Sprite::GetRotationCenter() const
{
	return _RotationCenter;
}

void Sprite::SetRotationCenter(D3DXVECTOR2 rotationCenter)
{
	_RotationCenter = rotationCenter;
}

float Sprite::GetRotation() const
{
	return _Rotation;
}

void Sprite::SetRotation(float rotation)
{
	_Rotation = rotation;
}

D3DXIMAGE_INFO Sprite::GetImageInfo() const
{
	return _ImageInfo;
}

void Sprite::FlipHorizontal(bool flag)
{
	if (_FlipHorizontal != flag)
	{
		_FlipHorizontal = flag;
		_Scale = D3DXVECTOR2(_Scale.x, -_Scale.y);
	}

}

void Sprite::FlipVertical(bool flag)
{
	if (_FlipVertical != flag)
	{
		_FlipVertical = flag;
		_Scale = D3DXVECTOR2(-_Scale.x, _Scale.y);
	}
}

bool Sprite::IsFlipHorizontal() const
{
	return _FlipHorizontal;
}

bool Sprite::IsFlipVertical() const
{
	return _FlipVertical;
}

void CTile::SetTile(const char* Name, int X, int Y, int Width, int Height)
{
	_NameTile = Name;
	_RectTile.left = X;
	_RectTile.top = Y;
	_RectTile.right = Width;
	_RectTile.bottom = Height;
}

CTile CTile::GetTile() const
{
	CTile temp{};
	temp._RectTile = _RectTile;
	temp._NameTile = _NameTile;
	return temp;
}

RECT CTile::GetLocationTile() const
{
	auto rect = RECT();
	rect.left = _RectTile.left;
	rect.right = _RectTile.right;
	rect.top = _RectTile.top;
	rect.bottom = _RectTile.bottom;
	return rect;
}

void Sprite::SetWidth(int width)
{
	_Width = width;
}

void Sprite::SetHeight(int height)
{
	_Height = height;
}