#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

#include "../GameComponents/Scene.h"

class SceneManager
{
public:
	static SceneManager* GetInstance();
	~SceneManager();

	Scene* GetCurrentScene() const;
	void Update(float dt) const;
	void ReplaceScene(Scene* scene);

private:
	SceneManager();

	static SceneManager* _instance;
	Scene* _currentScene;
};

#endif
