#include "Scene.h"

Scene::Scene()
{
}

Scene::Scene(GameEngine* gameEngine)
	:m_game(gameEngine)
{

}

void Scene::registerAction(int inputKey, const std::string& actionName)
{
	m_actionMap[inputKey] = actionName;
}

void Scene::doAction(const Action& action)
{
	//ignore null action
	if (action.name() == "NONE") { return; }
	sDoAction(action);
}