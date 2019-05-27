#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <Windows.h>
#include <vector>
#include "Sprite.h"

class Animation : public Sprite
{
public:
	// ham ho tro lay animation voi anh co duy nhat 1 hang
	Animation(const char* filePath, int rows, int columns, int frameWidth, int frameHeight,
		float timePerFrame = 0.1f, D3DCOLOR colorKey = NULL);

	void Update(float dt);
	void Draw(GVec3 position = GVec3(), RECT sourceRect = RECT(),
		GVec2 scale = GVec2(), GVec2 transform = GVec2(), float angle = 0,
		GVec2 rotationCenter = GVec2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255)) override;
	void Draw(GVec2 translate);

	// SUB-FUNCTION
public:
	int GetCurrentRow() const { return m_currentRow; }
	int GetCurrentColumn() const { return m_currentIndex; }
	void SetShoot(bool shoot) { this->m_isShoot = shoot; }
	void SetPause(bool pause) { this->m_isPause = pause; }
	bool GetPause() const { return this->m_isPause; }
	void SetLoop(bool isLoop) { this->m_isLoop = isLoop; }

	void SetFrame(int frameW, int frameH);
	void SetAnimation(int currentRow, int framePerRow, float timePerFrame = 0.1f, bool isLoop = true);

private:

	int				m_row,				//so hang cua animation
					m_cols,
					m_framePerRow,		//so cot cua animation
					m_currentIndex,		//gia tri frame hien tai - bat dau tu 0 -> tong so frame - 1
					m_currentRow,			// hang hien tai
					m_frameWidth,			// chieu rong cua 1 frame 
					m_frameHeight;		// chieu dai cua 1 frame

	bool			m_isLoop,
					m_isShoot,
					m_isPause;

	float			m_timePerFrame,		//thoi gian luan chuyen 1 frame
					m_currentTotalTime;	//tong thoi gian hien tai de thuc hien timeperframe

	RECT			m_rect;
};
#endif