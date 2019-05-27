#include "Animation.h"


Animation::Animation(const char* filePath, int rows, int columns, int frameWidth, int frameHeight, float timePerFrame, D3DCOLOR colorKey) : Sprite(filePath, RECT(), frameWidth, frameHeight, colorKey)
{
	this->_row = rows;
	this->_cols = columns;

	this->_currentRow = 0;
	this->_currentIndex = 0;

	this->_framePerRow = columns;

	this->_frameWidth = frameWidth;
	this->_frameHeight = frameHeight;

	this->_timePerFrame = timePerFrame;

	this->_isLoop = true;
	this->_isPause = false;
	this->_isShoot = false;
}

void Animation::SetFrame(int frameW, int frameH)
{
	this->_frameWidth = frameW;
	this->_frameHeight = frameH;
	this->SetWidth(frameW);
	this->SetHeight(frameH);
}

void Animation::SetAnimation(int currentRow, int framePerRow, float timePerFrame, bool loopAnimation)
{
	this->_currentRow = currentRow;
	this->_framePerRow = framePerRow;

	this->_timePerFrame = timePerFrame;

	this->_isLoop = loopAnimation;

	_currentTotalTime = 0;
	this->_currentIndex = 0;
	_isPause = false;
}

void Animation::Update(float dt)
{
	_rect.left = _currentIndex * _frameWidth;
	_rect.right = _rect.left + _frameWidth;
	_rect.top = (_currentRow + _isShoot) * _frameHeight;
	_rect.bottom = _rect.top + _frameHeight;

	SetSourceRect(_rect);

	if (_framePerRow <= 1 || _isPause)
		return;

	_currentTotalTime += dt;
	if (_currentTotalTime >= _timePerFrame)
	{
		_currentTotalTime = 0;
		if (++_currentIndex >= _framePerRow)
		{
			if (_isLoop)
				_currentIndex = 0;
			else
			{
				_currentIndex = _framePerRow - 1;
				_isPause = true;
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