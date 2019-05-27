#include "Sprite.h"
#include "GameGlobal.h"

Sprite::Sprite(const char* filePath, RECT sourceRect, int width, int height, D3DCOLOR colorKey)
{
	m_isReverseX = false;
	m_spriteHandler = GameGlobal::GetSpriteHandler();
	m_position = Gvec3Zero;
	m_rotation = 0;
	m_rotationCenter = GVec2(m_position.x, m_position.y);
	m_translation = Gvec2Zero;
	m_scale = GVec2(1.0f, 1.0f);

	// ANCHOR POINT
	m_isAnchorPoint = false;


	D3DXGetImageInfoFromFile(filePath, &m_imageInfo);

	if (width == 0)
	{
		if (!IsCheckRect(sourceRect))
			this->m_width = m_imageInfo.Width;
		else
			this->m_width = sourceRect.right - sourceRect.left;
	}
	else
		this->m_width = width;

	if (height == 0)
	{
		if (!IsCheckRect(sourceRect))
			this->m_height = m_imageInfo.Height;
		else
			this->m_height = sourceRect.bottom - sourceRect.top;
	}
	else
		this->m_height = height;

	if (!IsCheckRect(sourceRect))
	{
		this->m_sourceRect.left = 0;
		this->m_sourceRect.right = this->m_width;
		this->m_sourceRect.top = 0;
		this->m_sourceRect.bottom = this->m_height;
	}

	LPDIRECT3DDEVICE9 device;
	m_spriteHandler->GetDevice(&device);

	D3DXCreateTextureFromFileEx(
		device,
		filePath,
		m_imageInfo.Width,
		m_imageInfo.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		colorKey,
		&m_imageInfo,
		nullptr,
		&m_texture
	);
}

Sprite::~Sprite()
{
	SAFE_RELEASE(m_texture);
	SAFE_RELEASE(m_spriteHandler);
}

void Sprite::Draw(GVec3 Position, RECT SourceRect, GVec2 Scale, GVec2 Translate,
	float Angle, GVec2 RotationCenter, D3DXCOLOR transColor)
{
	GVec3 inPosition = m_position;
	RECT inSourceRect = m_sourceRect;
	float inRotation = m_rotation;
	GVec2 inScale = m_scale;
	GVec2 inTranslation = m_translation;
	GVec2 inRotationCenter = m_rotationCenter;
	GVec2 scalingCenter = GVec2(inPosition.x, inPosition.y);
	inRotation = Angle * (3.14159265358979323846 / 180);

	if (Position != GVec3())
		inPosition = Position;

	inPosition.x = int(inPosition.x);
	inPosition.y = int(inPosition.y);
	inPosition.z = int(inPosition.z);

	if (IsCheckRect(SourceRect))
		inSourceRect = SourceRect;

	if (Scale != GVec2())
		inScale = Scale;

	if (Translate != GVec2())
		inTranslation = Translate;

	if (RotationCenter != GVec2())
		inRotationCenter = RotationCenter;
	else
		m_rotationCenter = GVec2(inPosition.x, inPosition.y);

	D3DXMatrixTransformation2D(
		&m_matrix,
		&scalingCenter,
		0,
		&inScale,
		&inRotationCenter,
		inRotation,
		&inTranslation
	);

	D3DXMATRIX oldMatrix;
	m_spriteHandler->GetTransform(&oldMatrix);
	m_spriteHandler->SetTransform(&m_matrix);

	GVec3 center;
	if (m_isAnchorPoint)
	{
		if (m_anchorPoint.x != -1 && m_anchorPoint.y != -1)
			center = GVec3(m_anchorPoint.x, m_anchorPoint.y, 0.0f);
		else
			center = GVec3(m_width / 2, m_height, 0.0f);
	}
	else
		center = GVec3(m_width / 2, m_height / 2, 0.0f);


	//GVec3 center(float(_width) / 2, float(_height) / 2, 0);

	m_spriteHandler->Draw(
		m_texture,
		&inSourceRect,
		&center,
		&inPosition,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);
	m_spriteHandler->SetTransform(&oldMatrix);
}

void Sprite::SetSourceRect(const RECT& rect)
{
	m_sourceRect = rect;
}

LPDIRECT3DTEXTURE9 Sprite::GetTexture() const
{
	return m_texture;
}

GVec3 Sprite::GetPosition() const
{
	return m_position;
}

void Sprite::SetPosition(float x, float y)
{
	SetPosition(GVec2(x, y));
}

void Sprite::SetPosition(const GVec2& pos)
{
	SetPosition(GVec3(pos.x, pos.y, 0));
}

void Sprite::SetPosition(const GVec3& pos)
{
	m_position = pos;
}

GVec2 Sprite::GetScale() const
{
	return m_scale;
}

void Sprite::SetScale(const GVec2& scale)
{
	this->m_scale = scale;
}

GVec2 Sprite::GetTranslation() const
{
	return m_translation;
}

void Sprite::SetTranslation(const GVec2& translation)
{
	this->m_translation = translation;
}

GVec2 Sprite::GetRotationCenter() const
{
	return m_rotationCenter;
}

void Sprite::SetRotationCenter(const GVec2& rotationCenter)
{
	this->m_rotationCenter = rotationCenter;
}

float Sprite::GetRotation() const
{
	return m_rotation;
}

void Sprite::SetRotation(float rotation)
{
	this->m_rotation = rotation;
}

D3DXIMAGE_INFO Sprite::GetImageInfo() const
{
	return m_imageInfo;
}

void Sprite::SetReverse(bool reverse)
{
	if (m_isReverseX != reverse)
	{
		m_isReverseX = reverse;
		m_scale = GVec2(-m_scale.x, m_scale.y);
	}
}

bool Sprite::IsAnchorPoint() const
{
	return m_isAnchorPoint;
}

void Sprite::IsAnchorPoint(bool val)
{
	m_isAnchorPoint = val;
}

GVec2 Sprite::GetAnchorPoint() const
{
	return m_anchorPoint;
}

void Sprite::SetAnchorPoint(const GVec2& val)
{
	m_anchorPoint = val;
}

void Sprite::SetAnchorPoint(float x, float y)
{
	SetAnchorPoint(GVec2(x, y));
}

bool Sprite::IsCheckRect(const RECT& bound)
{
	if (bound.left == bound.right)
		return false;
	if (bound.top == bound.bottom)
		return false;
	return true;
}

int Sprite::GetWidth() const
{
	return m_width;
}

void Sprite::SetWidth(int width)
{
	this->m_width = width;
}

int Sprite::GetHeight() const
{
	return m_height;
}

void Sprite::SetHeight(int height)
{
	this->m_height = height;
}