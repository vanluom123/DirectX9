#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__
#include "../Scenes/Scene.h"


class SceneManager
{
public:
	static SceneManager* getInstance();
	~SceneManager();

	enum eSceneType
	{
		INTRO_SCENE = 0,
		BEGIN_SCENE = 1
	};

	Scene* getCurrentScene() const;
	void update(float dt) const;
	void setScene(eSceneType sceneType);

private:
	SceneManager();

	static SceneManager* _instance;
	Scene* _currentScene;
};

#endif
