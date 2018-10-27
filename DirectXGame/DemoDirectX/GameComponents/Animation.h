#ifndef __ANIMATION__
#define __ANIMATION__

#include <Windows.h>
#include <d3dx9.h>
#include <d3d9.h>
#include <vector>

#include "Sprite.h"

using namespace std;

class Animation : public Sprite
{
protected:
	//Use to inherit
	void InitWithAnimation(const char* filePath, int totalFrame, int rows, int columns, float timePerFrame = 0.1f, D3DCOLOR colorKey = NULL);

	int		mRows,				//Row number of the animation
			mColumns,			//Column number of the animation
			mCurrentIndex,		//The value of the current frame - start from 0 -> Total frame - 1
			mCurrentRow,		//The current row
			mCurrentColumn,		//The current column
			mFrameWidth,		//The width frame
			mFrameHeight,		//The height frame
			mTotalFrame;		//Total frame


	float	mTimePerFrame,		//Time to convert a frame
			mCurrentTotalTime;	//Total the current time to execute timePerFrame

	RECT	mRect;

public:
    //Support function get the animation with an image only row
    Animation(const char* filePath, int totalFrame, int rows, int columns, float timePerFrame = 0.1f,
		D3DCOLOR colorKey = NULL);

    Animation();

    virtual void Update(float dt);

    void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(),
		D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(),
		D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255)) override;

    void Draw(D3DXVECTOR2 transform);

    ~Animation();

};

#endif
