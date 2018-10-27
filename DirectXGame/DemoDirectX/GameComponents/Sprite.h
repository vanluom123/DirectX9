#ifndef __SPRITE__
#define __SPRITE__
#include <d3d9.h>
#include <d3dx9.h>

class Sprite
{
protected:
	//su dung cho ke thua
	void InitWithSprite(const char* filePath, RECT sourceRect = RECT(), int width = NULL, int height = NULL,
		D3DCOLOR colorKey = NULL);

	bool isRect(RECT rect);

	D3DXVECTOR3             mPosition;				//Position of the sprite is located in the middle of texture image
	LPDIRECT3DTEXTURE9      mTexture;				//Image will be saved here
	LPD3DXSPRITE            mSpriteHandler;			//SpriteHandler: Image drawing support
	D3DXIMAGE_INFO          mImageInfo;				//The actual information of the image is taken
	RECT                    mSourceRect;			//Rectangle is cut from the texture image

	int                     mWidth, mHeight;		//Size of texture image

	bool                    mIsFlipVertical,		//Flip vertically
							mIsFlipHorizontal;		//Flip horizontally

	float                   mRotation;				//The spin angle of the sprite is calculated in radians

	D3DXVECTOR2             mScale;					// Vector custom zoom in or zoom out of texture
	D3DXVECTOR2             mTranslation;			//Image is translated from the sprite + mTranslate
	D3DXMATRIX              mMatrix;				//Matrix of the sprite support for geometry
	D3DXVECTOR2             mRotationCenter;		// (origin vector)

public:
	explicit Sprite(const char* filePath, RECT sourceRect = RECT(), int width = 0, int height = 0,
           D3DCOLOR colorKey = NULL);

    Sprite();

	virtual ~Sprite();

    LPDIRECT3DTEXTURE9 GetTexture();

    //void Draw();
	virtual void Draw(D3DXVECTOR3 position = D3DXVECTOR3(),RECT sourceRect = RECT(),
		D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0,
		D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));

    void SetWidth(int width);
    int GetWidth();

    void SetHeight(int height);
    int GetHeight();

	// Get information about an image
    D3DXIMAGE_INFO GetImageInfo();

    D3DXVECTOR3 GetPosition();
	void SetPosition(float x, float y);
	void SetPosition(D3DXVECTOR2 pos);
    void SetPosition(D3DXVECTOR3 pos);

    D3DXVECTOR2 GetScale();
    void SetScale(D3DXVECTOR2 scale);

	//The translation from the position of the World to the position of the View
	D3DXVECTOR2 GetTranslation();
    void SetTranslation(D3DXVECTOR2 translation);

    D3DXVECTOR2 GetRotationCenter();
    void SetRotationCenter(D3DXVECTOR2 rotationCenter);

	//Rotate by radian
    float GetRotation();
    void SetRotation(float rotation);

    void SetSourceRect(RECT rect);

	//True: Flip vertically
	//False: Don't flip
    void FlipHorizontal(bool flag);
    bool IsFlipHorizontal();

	//True: Flip horizontally
	//False: Don't flip
    void FlipVertical(bool flag);
    bool IsFlipVertical();

};
#endif