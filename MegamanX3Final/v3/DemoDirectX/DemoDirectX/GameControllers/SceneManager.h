#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

#include "../GameComponents/Scene.h"

class SceneManager
{
public:
	static SceneManager* GetInstance();
	~SceneManager();

	Scene* GetCurrentScene() const;
	void Update(float dt);
	void ReplaceScene(Scene* scene);

private:
	SceneManager();

	static SceneManager* m_instance;
	Scene* m_currentScene;
};

#endif
