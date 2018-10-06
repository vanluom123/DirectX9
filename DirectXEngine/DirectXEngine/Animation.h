#ifndef _ANIMATION_H
#define _ANIMATION_H
#include "Sprite.h"
#include <memory>


class Animation
{
public:
	Animation(const char* filePath, int totalFrame, int rows, int columns, float timePerFrame = 0.1f, D3DCOLOR colorKey = NULL);
	
	void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255)) const;

	virtual void Update(float dt);

	virtual void SetPosition(D3DXVECTOR3 pos);
	virtual void SetPosition(float x, float y);
	virtual void SetPosition(D3DXVECTOR2 pos);

	D3DXVECTOR2 GetScale() const;
	void SetScale(D3DXVECTOR2 scale) const;

	float GetRotation() const;
	void SetRotation(float rotation) const;

	D3DXVECTOR2 GetRotationCenter() const;
	void SetRotationCenter(D3DXVECTOR2 rotationCenter) const;

	void SetFlipHorizontal(bool flag) const;
	void SetFlipVertical(bool flag) const;

	D3DXVECTOR2	 GetTranslation() const;
	void SetTranslation(D3DXVECTOR2 translation) const;

	~Animation();

protected:
	void initWithAnimation(const char* filePath, int totalFrame, int rows, int columns, float timePerFrame = 0.1f, D3DCOLOR colorKey = NULL);

	int				mRows, //So dong cua sprite sheets
					mColumns, //So cot cua sprite sheets
					mCurrentIndex, //vi tri hien tai cua frame
					mCurrentRow, //Dong hien tai cua frame
					mCurrentColumn,	//Cot hien tai cua frame
					mFrameWidth,	//Chieu dai frame
					mFrameHeight,	//Chieu cao frame
					mTotalFrame;	//Tong so frame trong sprite sheets

	float			mTimePerFrame,	//Thoi gian cho mot next frame
					mCurrentTotalTime;	//Thoi gian hien tai neu CurrentTotalTime >= TotalPerFrame

	Sprite*			mSprite;
	RECT			mRect;
};

#endif