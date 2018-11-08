#include "GameAnimation.h"

GameAnimation::GameAnimation(const char* filePath, int rows, int columns, int frameWidth, int frameHeight,
	float timePerFrame, D3DCOLOR colorKey) : Sprite(filePath, RECT(), frameWidth, frameHeight, colorKey)
{
	this->mRows = rows;
	this->mColumns = columns;
	this->mCurrentRow = 0;
	this->mCurrentIndex = 0;
	this->mframePerRow = columns;
	this->mFrameWidth = frameWidth;
	this->mFrameHeight = frameHeight;
	this->mTimePerFrame = timePerFrame;
}

void GameAnimation::setAnimation(int currentRow, int framePerRow, int currentIndex, float timePerFrame)
{
	this->mCurrentRow = currentRow;
	this->mframePerRow = framePerRow;
	this->mTimePerFrame = timePerFrame;
	mCurrentTotalTime = 0;
	this->mCurrentIndex = currentIndex;

	mRect.left = mCurrentIndex * mFrameWidth;
	mRect.right = mRect.left + mFrameWidth;
	mRect.top = mCurrentRow * mFrameHeight;
	mRect.bottom = mRect.top + mFrameHeight;

	SetSourceRect(mRect);
}

void GameAnimation::Update(float dt)
{
	if (mframePerRow <= 1 || mCurrentRow > mRows || mframePerRow > mColumns)
		return;

	mCurrentTotalTime += dt;
	if (mCurrentTotalTime >= mTimePerFrame)
	{
		mCurrentTotalTime = 0;
		mCurrentIndex++;

		if (mCurrentIndex >= mframePerRow)
		{
			mCurrentIndex = 0;
		}

		mRect.left = mCurrentIndex * mFrameWidth;
		mRect.right = mRect.left + mFrameWidth;
		mRect.top = mCurrentRow * mFrameHeight;
		mRect.bottom = mRect.top + mFrameHeight;

		SetSourceRect(mRect);
	}
}

void GameAnimation::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle,
	D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	Sprite::Draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);
}

void GameAnimation::Draw(D3DXVECTOR2 translate)
{
	Sprite::Draw(D3DXVECTOR3(), RECT(), D3DXVECTOR2(), translate);
}
