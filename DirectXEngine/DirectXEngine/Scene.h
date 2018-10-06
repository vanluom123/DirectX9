#ifndef _SCENE_
#define _SCENE_
#include <d3d9.h>

class Scene
{
public:
	virtual void Update(float dt) = 0;
	virtual void LoadContent();
	virtual void Draw() = 0;

/*
	virtual void KeyDown(int keyCode);
	virtual void KeyUp(int keyCode);
	virtual void MouseDown(float x, float y);*/

	D3DCOLOR GetBackColor() const;

	virtual ~Scene() = default;
protected:
	Scene();
	D3DCOLOR mBackColor;
};

#endif