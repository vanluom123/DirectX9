#pragma once

#include <d3d9.h>
#include <vector>
#include <d3dx9.h>

class InfoSprite
{
	float _Width, _Height, _FrameWidth, _FrameHeight;
	int _Frame;

	struct InfoFrame
	{
		float x;
		float y;
		float w;
		float h;
		float pX;
		float pY;
		float sX;
		float sY;
	};

	InfoFrame* _InfoFrame;
	std::vector<InfoFrame*> _Info;

public:
	explicit InfoSprite(const char* FilePath);
	~InfoSprite() = default;

	float GetWidth() const;
	float GetHeight() const;
	float GetFrameWidth() const;
	float GetFrameHeight() const;

	void ReadXML(const char* FilePath);
	RECT GetRect(int Index) const;
	D3DXVECTOR2 GetOrigin(int Index) const;
};
