#include "Animation.h"


Animation::Animation(const char* filePath, int rows, int columns, int frameWidth, int frameHeight, float timePerFrame, D3DCOLOR colorKey) : Sprite(filePath, RECT(), frameWidth, frameHeight, colorKey)
{
	this->m_row = rows;
	this->m_cols = columns;

	this->m_currentRow = 0;
	this->m_currentIndex = 0;

	this->m_framePerRow = columns;

	this->m_frameWidth = frameWidth;
	this->m_frameHeight = frameHeight;

	this->m_timePerFrame = timePerFrame;

	this->m_isLoop = true;
	this->m_isPause = false;
	this->m_isShoot = false;

	// INIT CURRENT TOTAL TIME
	// INIT RECT
	m_currentTotalTime = 0;
	m_rect = RECT();
}

void Animation::SetFrame(int frameW, int frameH)
{
	this->m_frameWidth = frameW;
	this->m_frameHeight = frameH;
	this->SetWidth(frameW);
	this->SetHeight(frameH);
}

void Animation::SetAnimation(int currentRow, int framePerRow, float timePerFrame, bool loopAnimation)
{
	this->m_currentRow = currentRow;
	this->m_framePerRow = framePerRow;

	this->m_timePerFrame = timePerFrame;

	this->m_isLoop = loopAnimation;

	m_currentTotalTime = 0;
	this->m_currentIndex = 0;
	m_isPause = false;
}

void Animation::Update(float dt)
{
	m_rect.left = m_currentIndex * m_frameWidth;
	m_rect.right = m_rect.left + m_frameWidth;
	m_rect.top = (m_currentRow + m_isShoot) * m_frameHeight;
	m_rect.bottom = m_rect.top + m_frameHeight;

	this->SetSourceRect(m_rect);

	if (m_framePerRow <= 1 || m_isPause)
		return;

	m_currentTotalTime += dt;
	if (m_currentTotalTime >= m_timePerFrame)
	{
		m_currentTotalTime = 0;
		m_currentIndex++;
		if (m_currentIndex >= m_framePerRow)
		{
			if (m_isLoop)
				m_currentIndex = 0;
			else
			{
				m_currentIndex = m_framePerRow - 1;
				m_isPause = true;
			}
		}
	}
}

void Animation::Draw(GVec3 position, RECT sourceRect, GVec2 scale, GVec2 transform,
	float angle, GVec2 rotationCenter, D3DXCOLOR colorKey)
{
	Sprite::Draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);
}

void Animation::Draw(GVec2 translate)
{
	Sprite::Draw(GVec3(), RECT(), GVec2(), translate);
}