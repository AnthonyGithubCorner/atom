/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#ifndef MODEL_RENDERER_H
#define MODEL_RENDERER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "texture.hpp"
#include "shader.hpp"
#include "../load_asset/loadAsset.hpp"


class ModelRenderer
{
public:
    // Constructor (inits shaders/shapes)
	ModelRenderer(Shader &shader, const char *modelOBJfile);
    // Destructor
    ~ModelRenderer();
    // Renders a defined quad textured with given sprite
    void DrawModel(Texture2D &texture, glm::vec2 position, glm::vec3 size = glm::vec3(1.0f, 1.0f, 1.0f), uint8_t level=0, float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));
	void changeModelData(const char *modelOBJfile);
private:
    // Render state
    Shader       shader;
    unsigned int quadVAO;
    unsigned int numElements;
    // Initializes and configures the quad's buffer and vertex attributes
    void initRenderData(const char *dialogue_path);
    std::__1::chrono::steady_clock::time_point t_start;
};

#endif
