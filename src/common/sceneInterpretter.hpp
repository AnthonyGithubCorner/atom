#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "SDL_rect.h"
#include "modelRenderer.hpp"
#include "shader.hpp"
#include <string>
#include <map>
#include <vector>
#include "../json/json.hpp"

using json = nlohmann::json;

class sceneInterpretter
{
public:
    // Constructor (inits shaders/shapes)
	json scene_data;
	sceneInterpretter(const char *scene);
	void startScene();
	bool isModified();
    // Destructor

std::string  path_file; 
    // ~sceneInterpretter();
private:
	time_t time_last_updated = 0;
};

