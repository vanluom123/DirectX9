#include "Animation.h"


Animation::Animation(const char* filePath, int totalFrame, int rows, int columns, float timePerFrame, D3DCOLOR colorKey)
{
	initWithAnimation(filePath, totalFrame, rows, columns, timePerFrame, colorKey);
}

void Animation::initWithAnimation(const char* filePath, int totalFrame, int rows, int columns, float timePerFrame,
	D3DCOLOR colorKey)
{
	mSprite = new Sprite(filePath);
	mRows = rows;
	mColumns = columns;
	mTotalFrame = totalFrame;
	mTimePerFrame = timePerFrame;
	mCurrentRow = 0;
	mCurrentColumn = 0;

	//width - height luc nay la cua spritesheet
	mFrameWidth = mSprite->GetWidth() / mColumns;
	mFrameHeight = mSprite->GetHeight() / mRows;

	//set lai cho size cua sprite bang dung size cua frame de tranh bi lech vi tri
	mSprite->SetHeight(mFrameHeight);
	mSprite->SetWidth(mFrameWidth);

	mRect.left = 0;
	mRect.right = mFrameWidth;
	mRect.top = 0;
	mRect.bottom = mFrameHeight;
	mSprite->SetSourceRect(mRect);
}

void Animation::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DCOLOR colorKey) const
{
	mSprite->Draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);
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
		mSprite->SetSourceRect(mRect);
	}
	else
		mCurrentTotalTime += dt;
}

void Animation::SetPosition(D3DXVECTOR3 pos)
{
	mSprite->SetPosition(pos);
}

void Animation::SetPosition(float x, float y)
{
	SetPosition(D3DXVECTOR3(x, y, 0));
}

void Animation::SetPosition(D3DXVECTOR2 pos)
{
	SetPosition(D3DXVECTOR2(pos));
}

D3DXVECTOR2 Animation::GetScale() const
{
	return mSprite->GetScale();
}

void Animation::SetScale(D3DXVECTOR2 scale) const
{
	mSprite->SetScale(scale);
}

float Animation::GetRotation() const
{
	return mSprite->GetRotation();
}

void Animation::SetRotation(float rotation) const
{
	mSprite->SetRotation(rotation);
}

D3DXVECTOR2 Animation::GetRotationCenter() const
{
	return mSprite->GetRotationCenter();
}

void Animation::SetRotationCenter(D3DXVECTOR2 rotationCenter) const
{
	mSprite->SetRotationCenter(rotationCenter);
}

void Animation::SetFlipHorizontal(bool flag) const
{
	mSprite->FlipHorizontal(flag);
}

void Animation::SetFlipVertical(bool flag) const
{
	mSprite->FlipVertical(flag);
}

D3DXVECTOR2 Animation::GetTranslation() const
{
	return mSprite->GetTranslation();
}

void Animation::SetTranslation(D3DXVECTOR2 translation) const
{
	mSprite->SetTranslation(translation);
}

Animation::~Animation()
{
	if (mSprite)
	{
		delete mSprite;
		mSprite = NULL;
	}
}
