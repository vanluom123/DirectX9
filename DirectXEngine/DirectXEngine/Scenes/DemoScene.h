#pragma once

#include <vector>

#include "../GameComponents/Scene.h"
#include "../GameComponents/GameMap.h"
#include "../GameComponents/Camera.h"
#include "../GameObjects/Player/Player.h"

class DemoScene : public Scene
{
protected:
	void checkCollision();
	void CheckCameraAndWorldMap();
	void DrawQuadTree(QuadTree * quadTree);

	GameMap *mMap;
	Camera *mCamera;
	Player *mPlayer;

	std::map<int, bool> keys;
	std::vector<Entity*> mCollideAble;

public:
    DemoScene();
	~DemoScene();

    void Update(float dt) override;
    void LoadContent() override;
    void Draw() override;

    void OnKeyDown(int keyCode) override;
    void OnKeyUp(int keyCode) override;
    void OnMouseDown(float x, float y) override;
};

