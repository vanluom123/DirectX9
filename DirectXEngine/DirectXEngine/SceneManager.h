#ifndef _SCENE_MANAGER_
#define _SCENE_MANAGER_
#include "Scene.h"

class SceneManager
{
	SceneManager();

	static SceneManager* mInstance;

	Scene* mCurrentScene;

public:
	static SceneManager* GetInstance();
	Scene* GetCurrentScene();
	void Update(float dt);
	void ReplaceScene(Scene* scene);

	~SceneManager();
};

#endif