/*
 * animatedGameObject.hpp
 *
 *  Created on: Jul. 5, 2023
 *      Author: anthony
 */

#ifndef SRC_COMMON_ANIMATEDGAMEOBJECT_HPP_
#define SRC_COMMON_ANIMATEDGAMEOBJECT_HPP_

#include "gameObject.hpp"

class animatedGameObject: public gameObject
{
public:
	animatedGameObject(ModelRenderer *modelRender, std::string name, SDL_FRect initRect = {0.3f,0.3f,0.1f,0.1f}, int Level = 0, float IntoScreenStretch = -1.0f) : gameObject(modelRender, name, initRect, Level, IntoScreenStretch) {}
	void playAnimation(std::string name);
	void stopAnimation(std::string name);
	virtual ~animatedGameObject();
};

#endif /* SRC_COMMON_ANIMATEDGAMEOBJECT_HPP_ */
