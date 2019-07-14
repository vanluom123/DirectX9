#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__
#include "../Scenes/Scene.h"


class SceneManager
{
public:
	static SceneManager* getInstance();
	~SceneManager();

	Scene* getCurrentScene() const;
	void update(float dt) const;
	void replaceScene(Scene* new_scene);

private:
	SceneManager();

	static SceneManager* _instance;
	Scene* _currentScene;
};

#endif
