#ifndef __SCENE_MANAGER__
#define __SCENE_MANAGER__

#include "../GameComponents/Scene.h"

class SceneManager
{
	static SceneManager     *mInstance;
	Scene                   *mCurrentScene;

public:
    static SceneManager *GetInstance();

	SceneManager();
    ~SceneManager();

    Scene* GetCurrentScene();
    void Update(float dt);
    void ReplaceScene(Scene *scene);
};

#endif