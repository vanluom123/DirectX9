#ifndef _SCENE_MANAGER_
#define _SCENE_MANAGER_
#include "Scene.h"

class SceneManager
{
public:
	static SceneManager* GetInstance();
	Scene* GetCurrentScene();
	void Update(float dt);
	void ReplaceScene(Scene* scene);

	~SceneManager();
private:
	SceneManager();

	static SceneManager* mInstance;

	Scene* mCurrentScene;
};

#endif