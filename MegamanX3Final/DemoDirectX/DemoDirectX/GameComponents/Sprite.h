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
	void SetPosition(GVec2 pos);
	void SetPosition(GVec3 pos);

	GVec2 GetScale() const;
	void SetScale(GVec2 scale);

	//The translation from the position of the World to the position of the View
	GVec2 GetTranslation() const;
	void SetTranslation(GVec2 translation);

	GVec2 GetRotationCenter() const;
	void SetRotationCenter(GVec2 rotationCenter);

	//Rotate by radian
	float GetRotation() const;
	void SetRotation(float rotation);

	void SetSourceRect(RECT rect);

	//True: Flip horizontally
	//False: Don't flip
	void SetReverse(bool reverse);

private:
	static bool IsCheckRect(RECT SourceRect);

	GVec3							_position; //Position of the sprite is located in the middle of texture image
	LPDIRECT3DTEXTURE9				_texture; //Image will be saved here
	LPD3DXSPRITE					_spriteHandler; //SpriteHandler: Image drawing support
	D3DXIMAGE_INFO					_imageInfo; //The actual information of the image is taken
	RECT							_sourceRect; //Rectangle is cut from the texture image

	int								_width,
									_height; //Size of texture image

	float							_rotation; //The spin angle of the sprite is calculated in radians

	GVec2							_scale; // Vector custom zoom in or zoom out of texture
	GVec2							_translation; //Image is translated from the sprite + mTranslate
	D3DXMATRIX						_matrix; //Matrix of the sprite support for geometry
	GVec2							_rotationCenter; // (origin vector)

	bool							_isReverseX;
};

#endif