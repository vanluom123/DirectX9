#ifndef _ANIMATION_H
#define _ANIMATION_H
#include "Sprite.h"
#include <memory>


class Animation :public Sprite
{
public:
	Animation();
	Animation(const char* filePath, int totalFrame, int rows, int columns, float timePerFrame = 0.1f, D3DCOLOR colorKey = NULL);

	void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));

	void Draw(D3DXVECTOR2 trans);

	virtual void Update(float dt);

	~Animation();

protected:
	void initWithAnimation(const char* filePath, int totalFrame, int rows, int columns, float timePerFrame = 0.1f, D3DCOLOR colorKey = NULL);

	int				mRows,					//So dong cua sprite sheets
					mColumns,				//So cot cua sprite sheets
					mCurrentIndex,			//vi tri hien tai cua frame
					mCurrentRow,			//Dong hien tai cua frame
					mCurrentColumn,			//Cot hien tai cua frame
					mFrameWidth,			//Chieu dai frame
					mFrameHeight,			//Chieu cao frame
					mTotalFrame;			//Tong so frame trong sprite sheets

	float			mTimePerFrame,			//Thoi gian cho mot next frame
					mCurrentTotalTime;		//Thoi gian hien tai neu CurrentTotalTime >= TotalPerFrame

//Sprite*			mSprite;
	RECT			mRect;
};
#endif