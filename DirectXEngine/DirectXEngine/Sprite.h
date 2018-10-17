#ifndef __SPRITE__
#define __SPRITE__
#include <d3d9.h>
#include <d3dx9.h>

class Sprite
{
protected:
	// Be used to inherit
	void InitWithSprite(const char* filePath, RECT sourceRect = RECT(), int width = NULL, int height = NULL, D3DCOLOR colorKey = NULL);

	static bool isRect(RECT rect);

	// Position of sprite. Image has center position
	D3DXVECTOR3             mPosition;
	// Loading image into Texture
	LPDIRECT3DTEXTURE9      mTexture;
	// SpriteHandler that will help for draw image
	LPD3DXSPRITE            mSpriteHandler;
	// Real image information is taken
	D3DXIMAGE_INFO          mImageInfo;
	// Rectangle is cut from Texture image
	RECT                    mSourceRect;
	// Size of Texture
	int                     mWidth, mHeight;
	// Flipping to vertical
	bool                    mIsFlipVertical,
		// Flipping to horizontal
		mIsFlipHorizontal;
	// Angle sprite rotation is calculated by radian
	float                   mRotation;
	// Zoom in or zoom out of Texture
	D3DXVECTOR2             mScale;
	// Image change to real position of Sprite + mTranslate
	D3DXVECTOR2             mTranslation;
	// Matrix of Sprite that is helped in geometry
	D3DXMATRIX              mMatrix;
	// Center point in image rotation
	D3DXVECTOR2             mRotationCenter;

public:
	Sprite();

	explicit Sprite(const char* filePath, RECT sourceRect = RECT(), int width = NULL, int height = NULL, D3DCOLOR colorKey = NULL);

	virtual ~Sprite();

	LPDIRECT3DTEXTURE9 GetTexture();

	void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));

	void SetWidth(int width);
	int GetWidth();

	void SetHeight(int height);
	int GetHeight();

	// Taking image information
	D3DXIMAGE_INFO GetImageInfo();

	D3DXVECTOR3 GetPosition();
	void SetPosition(D3DXVECTOR3 pos);
	void SetPosition(float x, float y);
	void SetPosition(D3DXVECTOR2 pos);

	D3DXVECTOR2 GetScale();
	void SetScale(D3DXVECTOR2 scale);

	// Translation from world position to view position
	D3DXVECTOR2 GetTranslation();
	// Translation form world position to view
	void SetTranslation(D3DXVECTOR2 translation);

	D3DXVECTOR2 GetRotationCenter();
	void SetRotationCenter(D3DXVECTOR2 rotationCenter);

	// Rotate to radian
	float GetRotation();
	void SetRotation(float rotation);

	void SetSourceRect(RECT rect);

	// True: Image will be flipped to Horizontal.
	// False: Image will be not flipped
	void FlipHorizontal(bool flag);
	bool IsFlipHorizontal();

	//// True: Image will be flipped to vertical.
	// False: Image will be not flipped
	void FlipVertical(bool flag);
	bool IsFlipVertical();

};
#endif