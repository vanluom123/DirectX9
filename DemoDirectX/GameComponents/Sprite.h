#ifndef __SPRITE__
#define __SPRITE__
#include "../GameDefines/GameDefine.h"

class Sprite
{
public:
	Sprite(const char* filePath, RECT sourceRect = RECT(), int width = 0, int height = 0,
		D3DCOLOR colorKey = NULL);
	virtual ~Sprite();

	LPDIRECT3DTEXTURE9 getTexture() const;

	virtual void draw(GVec3 Position = GVec3(), RECT SourceRect = RECT(),
		GVec2 Scale = GVec2(), GVec2 Translate = GVec2(), float Angle = 0,
		GVec2 RotationCenter = GVec2(), D3DXCOLOR transColor = D3DCOLOR_XRGB(255, 255, 255));

	void setWidth(int width);
	int getWidth() const;

	void setHeight(int height);
	int getHeight() const;

	// Get information about an image
	D3DXIMAGE_INFO getImageInfo() const;

	GVec3 getPosition() const;
	void setPosition(float x, float y);
	void setPosition(const GVec2& pos);
	void setPosition(const GVec3& pos);

	GVec2 getScale() const;
	void setScale(const GVec2& scale);

	//The translation from the position of the World to the position of the View
	GVec2 getTranslation() const;
	void setTranslation(const GVec2& translation);

	GVec2 getRotationCenter() const;
	void setRotationCenter(const GVec2& rotationCenter);

	//Rotate by radian
	float getRotation() const;
	void setRotation(float rotation);

	void setSourceRect(const RECT& rect);

	//True: Flip horizontally
	//False: Don't flip
	void setReverse(bool reverse);

	bool isAnchorPoint() const;
	void isAnchorPoint(bool val);

	GVec2 getAnchorPoint() const;
	void setAnchorPoint(const GVec2& val);
	void setAnchorPoint(float x, float y);

	// FUNCTION CHECK RECTANGLE
private:
	bool isCheckRect(const RECT& bound);

	// INFORMATION
private:
	GVec3 _position; //Position of the sprite is located in the middle of texture image
	LPDIRECT3DTEXTURE9 _texture; //Image will be saved here
	LPD3DXSPRITE _spriteHandler; //SpriteHandler: Image drawing support
	D3DXIMAGE_INFO _imageInfo; //The actual information of the image is taken
	RECT _sourceRect; //Rectangle is cut from the texture image

	int	_width, _height; //Size of texture image

	float _rotation; //The spin angle of the sprite is calculated in radians

	GVec2 _scale; // Vector custom zoom in or zoom out of texture
	GVec2 _translation; //Image is translated from the sprite + mTranslate
	D3DXMATRIX _matrix; //Matrix of the sprite support for geometry
	GVec2 _rotationCenter; // (origin vector)

	bool _isReverseX;

	bool _isAnchorPoint;
	GVec2 _anchorPoint;
};

#endif