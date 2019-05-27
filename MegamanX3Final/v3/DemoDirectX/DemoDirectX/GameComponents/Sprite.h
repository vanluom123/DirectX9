#ifndef __SPRITE__
#define __SPRITE__
#include "../GameDefines/GameDefine.h"

class Sprite
{
public:
	Sprite(const char* filePath, RECT sourceRect = RECT(), int width = 0, int height = 0,
		D3DCOLOR colorKey = NULL);
	virtual ~Sprite();

	LPDIRECT3DTEXTURE9 GetTexture() const;

	virtual void Draw(GVec3 Position = GVec3(), RECT SourceRect = RECT(),
		GVec2 Scale = GVec2(), GVec2 Translate = GVec2(), float Angle = 0,
		GVec2 RotationCenter = GVec2(), D3DXCOLOR transColor = D3DCOLOR_XRGB(255, 255, 255));

	void SetWidth(int width);
	int GetWidth() const;

	void SetHeight(int height);
	int GetHeight() const;

	// Get information about an image
	D3DXIMAGE_INFO GetImageInfo() const;

	GVec3 GetPosition() const;
	void SetPosition(float x, float y);
	void SetPosition(const GVec2& pos);
	void SetPosition(const GVec3& pos);

	GVec2 GetScale() const;
	void SetScale(const GVec2& scale);

	//The translation from the position of the World to the position of the View
	GVec2 GetTranslation() const;
	void SetTranslation(const GVec2& translation);

	GVec2 GetRotationCenter() const;
	void SetRotationCenter(const GVec2& rotationCenter);

	//Rotate by radian
	float GetRotation() const;
	void SetRotation(float rotation);

	void SetSourceRect(const RECT& rect);

	//True: Flip horizontally
	//False: Don't flip
	void SetReverse(bool reverse);

	bool IsAnchorPoint() const;
	void IsAnchorPoint(bool val);

	GVec2 GetAnchorPoint() const;
	void SetAnchorPoint(const GVec2& val);
	void SetAnchorPoint(float x, float y);

	// FUNCTION CHECK RECTANGLE
private:
	bool IsCheckRect(const RECT& bound);

	// INFORMATION
private:
	GVec3							m_position; //Position of the sprite is located in the middle of texture image
	LPDIRECT3DTEXTURE9				m_texture; //Image will be saved here
	LPD3DXSPRITE					m_spriteHandler; //SpriteHandler: Image drawing support
	D3DXIMAGE_INFO					m_imageInfo; //The actual information of the image is taken
	RECT							m_sourceRect; //Rectangle is cut from the texture image

	int								m_width,
									m_height; //Size of texture image

	float							m_rotation; //The spin angle of the sprite is calculated in radians

	GVec2							m_scale; // Vector custom zoom in or zoom out of texture
	GVec2							m_translation; //Image is translated from the sprite + mTranslate
	D3DXMATRIX						m_matrix; //Matrix of the sprite support for geometry
	GVec2							m_rotationCenter; // (origin vector)

	bool							m_isReverseX;

	bool m_isAnchorPoint;
	GVec2 m_anchorPoint;
};

#endif