#include "Animation.h"


Animation::Animation()
{}

Animation::Animation(const char* filePath, int totalFrame, int rows, int columns, float timePerFrame, D3DCOLOR colorKey)
{
	initWithAnimation(filePath, totalFrame, rows, columns, timePerFrame, colorKey);
}

void Animation::initWithAnimation(const char* filePath, int totalFrame, int rows, int columns, float timePerFrame,
	D3DCOLOR colorKey)
{
	this->InitWithSprite(filePath);
	mRows = rows;
	mColumns = columns;
	mTotalFrame = totalFrame;
	mTimePerFrame = timePerFrame;
	mCurrentRow = 0;
	mCurrentColumn = 0;

	//width - height luc nay la cua spritesheet
	mFrameWidth = this->GetWidth() / mColumns;
	mFrameHeight = this->GetHeight() / mRows;

	//set lai cho size cua sprite bang dung size cua frame de tranh bi lech vi tri
	this->SetHeight(mFrameHeight);
	this->SetWidth(mFrameWidth);

	mRect.left = 0;
	mRect.right = mFrameWidth;
	mRect.top = 0;
	mRect.bottom = mFrameHeight;
	this->SetSourceRect(mRect);
}

void Animation::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DCOLOR colorKey)
{
	Sprite::Draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);
}

void Animation::Draw(D3DXVECTOR2 trans)
{
	Sprite::Draw(D3DXVECTOR3(), RECT(), D3DXVECTOR2(), trans);
}

void Animation::Update(float dt)
{
	if (mTotalFrame <= 1)
		return;

	if (mCurrentTotalTime >= mTimePerFrame)
	{
		mCurrentTotalTime = 0;
		mCurrentIndex++;
		mCurrentColumn++;

		if (mCurrentIndex >= mTotalFrame)
		{
			mCurrentColumn = 0;
			mCurrentIndex = 0;
			mCurrentRow = 0;
		}

		if (mCurrentColumn >= mColumns)
		{
			mCurrentColumn = 0;
			mCurrentRow++;

			if (mCurrentRow >= mRows)
				mCurrentRow = 0;
		}

		mRect.left = mCurrentColumn * mFrameWidth;
		mRect.right = mRect.left + mFrameWidth;
		mRect.top = mCurrentRow * mFrameHeight;
		mRect.bottom = mRect.top + mFrameHeight;
		this->SetSourceRect(mRect);
	}
	else
		mCurrentTotalTime += dt;
}

Animation::~Animation()
{}
