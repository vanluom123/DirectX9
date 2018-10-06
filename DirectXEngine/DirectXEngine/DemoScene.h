#ifndef _DEMO_SCENE_
#define _DEMO_SCENE_
#include "Scene.h"
#include <vector>
#include "Sprite.h"
#include "Animation.h"

class DemoScene :public Scene
{
public:
	DemoScene();

	void Update(float dt) override;
	void LoadContent() override;
	void Draw() override;

	~DemoScene() override = default;

private:
	//std::vector<Sprite*> mSprite;
	//float mTimeCounter{};

	Animation* mGoldBlock;
};

#endif