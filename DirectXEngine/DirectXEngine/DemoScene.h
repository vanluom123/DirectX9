#ifndef _DEMO_SCENE_
#define _DEMO_SCENE_
#include "Scene.h"
#include "GameMap.h"
#include "Player.h"

class DemoScene :public Scene
{
public:
	DemoScene();

	void Update(float dt) override;
	void LoadContent() override;
	void Draw() override;

	void KeyDown(int keyCode) override;
	void KeyUp(int keyCode) override;
	void MouseDown(float x, float y) override;

	~DemoScene();

private:
	//std::vector<Sprite*> mSprite;
	//float mTimeCounter{};
	//Animation* mGoldBlock;
	GameMap* mMap;
	Camera* mCamera;
	Player* mPlayer;
	std::map<int, bool> keys;
};

#endif