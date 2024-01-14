/*
 * Camera.cpp
 *
 *  Created on: Jul. 5, 2023
 *      Author: anthony
 */

#include "Camera.hpp"

glm::mat4 Camera::camera_pos = glm::mat4(1);
glm::vec3 Camera::camera_rot = glm::vec3(0);

void Camera::setCamera(float x, float y){
	camera_pos = glm::translate(camera_pos, glm::vec3(x,y,0.0f));


    for (auto shader : ResourceManager::Shaders){
//    	    shader.second.SetMatrix4("projection", proj);
    		shader.second.SetMatrix4("view", camera_pos);
    }

}

