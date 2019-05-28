#ifndef __SCENE__
#define __SCENE__
#include <d3d9.h>

class Scene
{
protected:
	D3DCOLOR _backColor;

public:
	virtual ~Scene() = default;
	Scene();

	virtual void Update(float dt);
	virtual void Draw();

	virtual void OnKeyDown(int keyCode);
	virtual void OnKeyUp(int keyCode);

	virtual void onMouseDown(float x, float y);

	D3DCOLOR GetBackColor() const;
};

#endif
