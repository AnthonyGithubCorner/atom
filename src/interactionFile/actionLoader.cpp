#include "actionLoader.hpp"
#include "stateManager.hpp"
#include "../common/resourceManager.hpp"
#include "../UI/dialogue/dialogue.hpp"


std::map<std::string, void(*)(gameObject*, std::string)> actionLoader::actions;
std::map<std::string, bool(*)(gameObject*, std::string)> actionLoader::conds;




void setRotate(gameObject* object, std::string rotate)
{
	object->rotation = (std::stof(rotate));
}


void changeRotate(gameObject* object, std::string rotate)
{
	object->rotation += (std::stof(rotate));
}


//void setRotateY(gameObject* object, std::string rotate)
//{
//	object->rotation.y = (std::stof(rotate));
//}
//

//void changeRotateY(gameObject* object, std::string rotate)
//{
//	object->rotation.y += (std::stof(rotate));
//}

void changeLine(gameObject* object, std::string line)
{
	_change_line(std::stoi(line));
}

void setRotateX(gameObject* object, std::string rotate)
{
	// object->rotation.x = (object->rotation + std::stof(rotate));
}

void setX(gameObject* object, std::string floatX)
{
	object->setX(std::stof(floatX));
}

void setY(gameObject* object, std::string floatY)
{
	object->setY(std::stof(floatY));
}

void changeX(gameObject* object, std::string floatX)
{
	object->setX(std::stof(floatX) + object->renderRect.x);
}

void changeY(gameObject* object, std::string floatY)
{
	object->setY(std::stof(floatY) + object->renderRect.y);
}

void selectAnim(gameObject* object, std::string anim_name)
{
	object->selectAnim(anim_name);
}

void nextFrame(gameObject* object, std::string unused)
{
	object->nextFrame();
}

// void setAfterDelay(gameObject* object, std::string params)
//{
//	std::string delay;
//	std::string state;
//	std::istringstream iss(params);
//	iss >> delay >> state;
//	if(!delayTimerStarted[state].started)
//	{
//		delayTimerStarted[state].started = true;
//		delayTimerStarted[state].startTime = SDL_GetTicks64();
//	}
//	else
//	{
//		if(SDL_GetTicks64() - delayTimerStarted[state].startTime >= std::stoi(delay))
//		{
//			stateManager::setState(state);
//			delayTimerStarted[state].started = false;
//		}
//	}
//}

void toggleInLinearTime(gameObject* object, std::string floatX)
{
	object->setX(std::stof(floatX));
}

void disableActions(gameObject* object, std::string obj_name)
{
	ResourceManager::getGameObject(obj_name)->enableActions = false;
}

void enableActions(gameObject* object, std::string obj_name)
{
	ResourceManager::getGameObject(obj_name)->enableActions = true;
}

void disableRender(gameObject* object, std::string obj_name)
{
	ResourceManager::getGameObject(obj_name)->enableRender = false;
}

void enableRender(gameObject* object, std::string obj_name)
{
	ResourceManager::getGameObject(obj_name)->enableRender = true;
}

void renderDialogue(gameObject* object, std::string dialogueName)
{
	render_dialogue(ResourceManager::SCREEN_HEIGHT, ResourceManager::SCREEN_WIDTH, dialogueName, "andaleInfo", "andaleInfoPurple", "andaleInfoRed");
}

void printTriggerRect(gameObject* object, std::string objTriggerName)
{
    gameObject* trigger = ResourceManager::getGameObject(objTriggerName);
	SDL_Log("X trigger: %s", std::to_string(trigger->triggerRect.x).c_str());
	SDL_Log("X Object: %s", std::to_string(object->renderRect.x).c_str());
}

void playSoundEffect(gameObject* object, std::string musicName)
{
	ResourceManager::getSound(musicName)->play();
}

void playMusic(gameObject* object, std::string musicName)
{
	ResourceManager::getMusic(musicName)->play();
}


bool checkTrigger(gameObject* object, std::string objTriggerName)
{
	//The sides of the tile
	    float left1, right1, top1, bottom1;
	    float left2, right2, top2, bottom2;

	    //Calculate the dimensions of Object
	    left1 = object->renderRect.x;
	    right1 = object->renderRect.x + object->renderRect.w;
	    top1 = object->renderRect.y;
	    bottom1 = object->renderRect.y + object->renderRect.h;

	    //Calculate the dimensions of Trigger
	    gameObject* trigger = ResourceManager::getGameObject(objTriggerName);
	    left2 = trigger->triggerRect.x;
	    right2 = trigger->triggerRect.x + trigger->triggerRect.w;
	    top2 = trigger->renderRect.y;
	    bottom2 = trigger->triggerRect.y + trigger->triggerRect.h;

	    //If current object is not in trigger
	    if( (left2 <= right1 &&  right2 >= left1) && (bottom2 >= top1 && bottom1 >= top2) )
	    {
	        return true;
	    }

	// Than it must be in trigger
	return false;
}
bool checkActionEnable(gameObject* object, std::string obj_name)
{
	return ResourceManager::getGameObject(obj_name)->enableRender;
}

void switchScene(gameObject* object, std::string sceneName)
{
	ResourceManager::switch_scene(ResourceManager::GetSceneInterpretter(sceneName));
}

void actionLoader::registerAllActions()
{
//	registerFunc("changeRotate", changeRotate);
//	registerFunc("changeRotate", changeRotate);
//	registerFunc("changeRotate", changeRotate);
//	registerFunc("changeRotate", changeRotate);
//	registerFunc("changeRotate", changeRotate);
	registerFunc("switchScene", switchScene);
	registerFunc("playMusic", playMusic);
	registerFunc("playSoundEffect", playSoundEffect);
	registerFunc("changeLine", changeLine);
	// registerFunc("changeRotate", changeRotate);
//	registerFunc("setRotateY", setRotateY);
//	registerFunc("changeRotateY", changeRotateY);
	registerFunc("setRotate", setRotate);
	registerFunc("changeRotate", changeRotate);
	registerFunc("printTriggerRect", printTriggerRect);
	registerFunc("renderDialogue", renderDialogue);
	registerFunc("enableRender", enableRender);
	registerFunc("disableRender", disableRender);
	registerFunc("enableActions", enableActions);
	registerFunc("disableActions", disableActions);
	registerFunc("nextFrame", nextFrame);
	registerFunc("selectAnim", selectAnim);
	registerFunc("changeX", changeX);
	registerFunc("changeY", changeY);
	registerFunc("setX", setX);
	registerFunc("setY", setY);
//	registerFunc("setAfterDelay", setAfterDelay);

	registerCond("checkActionEnable", checkActionEnable);
	registerCond("checkTrigger", checkTrigger);



}

void actionLoader::registerFunc(std::string name, void(*func)(gameObject*, std::string))
{
	actions[name] = func;
}

void actionLoader::registerCond(std::string name, bool(*func)(gameObject*, std::string))
{
	conds[name] = func;
}
