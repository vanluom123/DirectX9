#ifndef _SCENE_MANAGER_
#define _SCENE_MANAGER_
#include "Scene.h"

class SceneManager
{
public:
	static SceneManager* GetInstance();
	Scene* GetCurrentScene() const;
	void Update(float dt) const;
	void ReplaceScene(Scene* scene);

	~SceneManager();
private:
	SceneManager() = default;

	static SceneManager* mInstance;

	Scene* mCurrentScene{};
};

#endif