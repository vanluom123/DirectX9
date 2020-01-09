#include "Sprite.h"
#include "GameGlobal.h"

Sprite::Sprite(const char* filePath, RECT sourceRect, int width, int height, D3DCOLOR colorKey)
{
	_isReverseX = false;
	_spriteHandler = GameGlobal::getInstance()->getDXSprite();
	_position = Gvec3Zero;
	_rotation = 0;
	_rotationCenter = GVec2(_position.x, _position.y);
	_translation = Gvec2Zero;
	_scale = GVec2(1.0f, 1.0f);

	// ANCHOR POINT
	_isAnchorPoint = false;


	D3DXGetImageInfoFromFile(filePath, &_imageInfo);

	if (width == 0)
	{
		if (!isCheckRect(sourceRect))
			_width = _imageInfo.Width;
		else
			_width = sourceRect.right - sourceRect.left;
	}
	else
		_width = width;

	if (height == 0)
	{
		if (!isCheckRect(sourceRect))
			_height = _imageInfo.Height;
		else
			_height = sourceRect.bottom - sourceRect.top;
	}
	else
		_height = height;

	if (!isCheckRect(sourceRect))
	{
		_sourceRect.left = 0;
		_sourceRect.right = _width;
		_sourceRect.top = 0;
		_sourceRect.bottom = _height;
	}

	LPDIRECT3DDEVICE9 device;
	_spriteHandler->GetDevice(&device);

	D3DXCreateTextureFromFileExA(
		device,
		filePath,
		_imageInfo.Width,
		_imageInfo.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		colorKey,
		&_imageInfo,
		nullptr,
		&_texture
	);
}

Sprite::~Sprite()
{
	SAFE_RELEASE(_texture);
	SAFE_RELEASE(_spriteHandler);
}

void Sprite::draw(GVec3 Position, RECT SourceRect, GVec2 Scale, GVec2 Translate,
	float Angle, GVec2 RotationCenter, D3DXCOLOR transColor)
{
	GVec3 inPosition = _position;
	RECT inSourceRect = _sourceRect;
	float inRotation = _rotation;
	GVec2 inScale = _scale;
	GVec2 inTranslation = _translation;
	GVec2 inRotationCenter = _rotationCenter;
	GVec2 scalingCenter = GVec2(inPosition.x, inPosition.y);
	inRotation = Angle * (3.14159265358979323846 / 180);

	if (Position != GVec3())
		inPosition = Position;

	inPosition.x = int(inPosition.x);
	inPosition.y = int(inPosition.y);
	inPosition.z = int(inPosition.z);

	if (isCheckRect(SourceRect))
		inSourceRect = SourceRect;

	if (Scale != GVec2())
		inScale = Scale;

	if (Translate != GVec2())
		inTranslation = Translate;

	if (RotationCenter != GVec2())
		inRotationCenter = RotationCenter;
	else
		_rotationCenter = GVec2(inPosition.x, inPosition.y);

	D3DXMatrixTransformation2D(
		&_matrix,
		&scalingCenter,
		0,
		&inScale,
		&inRotationCenter,
		inRotation,
		&inTranslation
	);

	D3DXMATRIX oldMatrix;
	_spriteHandler->GetTransform(&oldMatrix);
	_spriteHandler->SetTransform(&_matrix);

	GVec3 center;
	if (_isAnchorPoint)
	{
		if (_anchorPoint.x != -1 && _anchorPoint.y != -1)
			center = GVec3(_anchorPoint.x, _anchorPoint.y, 0.0f);
		else
			center = GVec3(_width / 2, _height, 0.0f);
	}
	else
		center = GVec3(_width / 2, _height / 2, 0.0f);

	_spriteHandler->Draw(
		_texture,
		&inSourceRect,
		&center,
		&inPosition,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);
	_spriteHandler->SetTransform(&oldMatrix);
}

void Sprite::setSourceRect(const RECT& rect)
{
	_sourceRect = rect;
}

LPDIRECT3DTEXTURE9 Sprite::getTexture() const
{
	return _texture;
}

GVec3 Sprite::getPosition() const
{
	return _position;
}

void Sprite::setPosition(float x, float y)
{
	setPosition(GVec2(x, y));
}

void Sprite::setPosition(const GVec2& pos)
{
	setPosition(GVec3(pos.x, pos.y, 0));
}

void Sprite::setPosition(const GVec3& pos)
{
	_position = pos;
}

GVec2 Sprite::getScale() const
{
	return _scale;
}

void Sprite::setScale(const GVec2& scale)
{
	_scale = scale;
}

GVec2 Sprite::getTranslation() const
{
	return _translation;
}

void Sprite::setTranslation(const GVec2& translation)
{
	_translation = translation;
}

GVec2 Sprite::getRotationCenter() const
{
	return _rotationCenter;
}

void Sprite::setRotationCenter(const GVec2& rotationCenter)
{
	_rotationCenter = rotationCenter;
}

float Sprite::getRotation() const
{
	return _rotation;
}

void Sprite::setRotation(float rotation)
{
	_rotation = rotation;
}

D3DXIMAGE_INFO Sprite::getImageInfo() const
{
	return _imageInfo;
}

void Sprite::setReverse(bool reverse)
{
	if (_isReverseX != reverse)
	{
		_isReverseX = reverse;
		_scale = GVec2(-_scale.x, _scale.y);
	}
}

bool Sprite::isAnchorPoint() const
{
	return _isAnchorPoint;
}

void Sprite::isAnchorPoint(bool val)
{
	_isAnchorPoint = val;
}

GVec2 Sprite::getAnchorPoint() const
{
	return _anchorPoint;
}

void Sprite::setAnchorPoint(const GVec2& val)
{
	_anchorPoint = val;
}

void Sprite::setAnchorPoint(float x, float y)
{
	setAnchorPoint(GVec2(x, y));
}

bool Sprite::isCheckRect(const RECT& bound)
{
	if (bound.left == bound.right)
		return false;
	if (bound.top == bound.bottom)
		return false;
	return true;
}

int Sprite::getWidth() const
{
	return _width;
}

void Sprite::setWidth(int width)
{
	_width = width;
}

int Sprite::getHeight() const
{
	return _height;
}

void Sprite::setHeight(int height)
{
	_height = height;
}