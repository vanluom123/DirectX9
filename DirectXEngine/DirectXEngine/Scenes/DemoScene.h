#pragma once

#include <math.h>
#include <vector>
#include <d3dx9.h>
#include <d3d9.h>

#include "../GameComponents/Scene.h"
#include "../GameComponents/Sprite.h"
#include "../GameComponents/Animation.h"
#include "../GameComponents/GameMap.h"
#include "../GameComponents/Camera.h"
#include "../GameComponents/GameDebugDraw.h"
#include "../GameObjects/Player/Player.h"

class DemoScene : public Scene
{
protected:
	void checkCollision();
	void CheckCameraAndWorldMap();
	void DrawQuadtree(QuadTree *quadtree);
	void DrawCollidable();

	GameMap *mMap;
	Camera *mCamera;
	Player *mPlayer;

	std::map<int, bool> keys;
	std::vector<Entity*> mCollidable;

	GameDebugDraw *mDebugDraw;

public:
    DemoScene();

    void Update(float dt);
    void LoadContent();
    void Draw();

    void OnKeyDown(int keyCode);
    void OnKeyUp(int keyCode);
    void OnMouseDown(float x, float y);

};

