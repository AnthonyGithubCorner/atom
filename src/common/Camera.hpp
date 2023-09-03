#ifndef SRC_COMMON_CAMERA_HPP_
#define SRC_COMMON_CAMERA_HPP_
#include "resourceManager.hpp"
// Include GLM
#include <glm/glm.hpp>
class Camera
{
public:
	static glm::mat4 camera_pos;
	static void setCamera(float x, float y);
private:
	Camera() {};
};

#endif /* SRC_COMMON_CAMERA_HPP_ */
