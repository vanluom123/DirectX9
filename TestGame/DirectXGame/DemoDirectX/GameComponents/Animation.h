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

	int		_NumberRow,		//Row number of the animation
			_NumberColumn,	//Column number of the animation
			_CurrentIndex,	//The value of the current frame - start from 0 -> Total frame - 1
			_IndexRow,		//The current row
			_IndexColumn,		//The current column
			_FrameWidth,		//The width frame
			_FrameHeight,		//The height frame
			_TotalFrame;		//Total frame


	float	_TimePerFrame,		//Time to convert a frame
			_CurrentTotalFrame;	//Total the current time to execute timePerFrame

	RECT	_Rect;

	float	_AnimationIndex;
	float	_AnimationRate;

public:
	//Support function get the animation with an image only row
	Animation(LPWSTR ImagePath, int TotalFrame, int Rows, int Columns, float TimePerFrame = 0.1f,
		D3DCOLOR Transcolor = NULL);

	Animation(LPWSTR ImagePath, const char* XMLPath, float AnimationRate, D3DCOLOR Transcolor = D3DCOLOR_XRGB(255, 255, 255));

	Animation() = default;

	void Update(float dt);
	void Updated(float DeltaTime);

	void Draw(D3DXVECTOR3 Position = D3DXVECTOR3(), RECT SourceRect = RECT(), D3DXVECTOR2 Scale = D3DXVECTOR2(),
		D3DXVECTOR2 Translate = D3DXVECTOR2(), float Angle = 0, D3DXVECTOR2 RotationCenter = D3DXVECTOR2(),
		D3DXCOLOR Transcolor = D3DCOLOR_XRGB(255, 255, 255)) override;

	void Draw(D3DXVECTOR2 Translate);

	~Animation() = default;

	void Render(float DeltaTime, float X, float Y, float ScaleSize, float FlipX) override;
};

#endif
