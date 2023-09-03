/*******************************************************************
 ** This code is part of Breakout.
 **
 ** Breakout is free software: you can redistribute it and/or modify
 ** it under the terms of the CC BY 4.0 license as published by
 ** Creative Commons, either version 4 of the License, or (at your
 ** option) any later version.
 ******************************************************************/
#include "modelRenderer.hpp"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <SDL.h>

typedef struct
{
	GLfloat x, y, z;
	GLfloat u, v;
} Vertex;

ModelRenderer::ModelRenderer(Shader &shader, const char *modelOBJfile)
{
    this->shader = shader;
    this->initRenderData(modelOBJfile);
    t_start = std::chrono::high_resolution_clock::now();
}

ModelRenderer::~ModelRenderer()
{
	glDeleteVertexArrays(1, &this->quadVAO);
}

void ModelRenderer::DrawModel(Texture2D &texture, glm::vec2 position,
		glm::vec3 size, uint8_t level, float rotate, glm::vec3 color)
{

//    	glEnable(GL_DEPTH_TEST);
	// prepare transformations
	    this->shader.Use();


	    // Calculate transformation
	      auto t_now = std::chrono::high_resolution_clock::now();
	      float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();
	      glm::mat4 model = glm::mat4(1.0f);
	      model = glm::translate(model, glm::vec3(position, (float)level));  // first translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)




//	      // model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate y axis
//	      model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate y axis
	      	     model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.5f*size.z)); // move origin of rotation to center of quad

	      model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 1.0f, 0.0f)); // then rotate z axis
     	   model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, -0.5f*size.z)); // move origin back
	      model = glm::scale(model, size); // last scale
//	      model = glm::scale(model, glm::vec3(1.0f, -1.0f, 1.0f)); // flip upside down
//	      model = glm::rotate(
//	     	      model,
//	     	      time*glm::radians(100.0f),
//	     	      glm::vec3(0.0f, 1.0f, 0.0f)
//	     	      );





	      // model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // move origin of rotation to center of quad
	      // model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
	      // model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // move origin back

	      // model = glm::scale(model, glm::vec3(size, 1.0f)); // last scale


	      // glm::mat4 view = glm::lookAt(
	      // glm::vec3(1.2f, 1.2f, 1.2f),
	      // glm::vec3(0.0f, 0.0f, 0.0f),
	      // glm::vec3(0.0f, 0.0f, 1.0f)
	      // );


	      // this->shader.SetMatrix4("view", view);

//	    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // move origin of rotation to center of quad
//	    // model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate y axis
//	    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 1.0f, 0.0f)); //  rotate z axis
//	    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // move origin back

	    this->shader.SetMatrix4("model", model);

	    // render textured quad
	    this->shader.SetVector3f("spriteColor", color);

	glActiveTexture(GL_TEXTURE0);

    texture.Bind();

    glBindVertexArray(this->quadVAO);
//    glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLES, 0, numElements);
glDepthMask(GL_TRUE);



//        glDepthMask(GL_TRUE);

    // Draw a rectangle from the 2 triangles using 6 indices
//


}

void ModelRenderer::initRenderData(const char *dialogue_path)
{
	std::ifstream file(dialogue_path);
	if (file.fail())
	{
		SDL_Log("file not found");
		return;
	}
	std::string line;
	std::vector<std::string> _lines;
	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> uvs;
	Vertex objVertices[20000];
	size_t pos = -1;
	GLfloat x, y, z;
	GLfloat u, v;
	GLuint currentHighestVertex = 0;
	numElements = 0;
	std::string command;
	std::string faceInput = "";
	uint itobjVertices = 0;
	uint itobjFaces = 0;
	while (std::getline(file, line))
	{
		std::istringstream iss(line);
		iss >> command;

		if (command == "v")
		{
			iss >> x >> y >> z;
			positions.push_back(glm::vec3(x, y, z));
		}
		else if (command == "vt")
		{
			iss >> u >> v;
			uvs.push_back(glm::vec2(u, v));
		}
		else if (command == "f")
		{
			for (int i = 0; i < 3; i++)
			{
				iss >> faceInput;
				auto faceIndex = faceInput.substr(0, faceInput.find('/'));
				auto uvIndex = faceInput.substr(faceInput.find('/') + 1, faceInput.size() - faceInput.find('/'));
				GLuint curFaceIndex = std::atoi(uvIndex.c_str()) - 1;
				glm::vec3 curPos = positions[std::atoi(faceIndex.c_str()) - 1];
				glm::vec2 curUV = uvs[curFaceIndex];
				Vertex temp = {curPos.x, curPos.y, curPos.z, curUV.x, 1 - curUV.y };

				objVertices[itobjVertices] = temp;
				itobjVertices++;
			}
		}
	}
	file.close();

	unsigned int VBO;

	glGenVertexArrays(1, &this->quadVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, (itobjVertices) * sizeof(Vertex),
			objVertices, GL_STATIC_DRAW);

	glBindVertexArray(this->quadVAO);

	GLint posAttrib = glGetAttribLocation(this->shader.ID, "vertex");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat),
			(void*) 0);

	GLint uvAttrib = glGetAttribLocation(this->shader.ID, "UV");
	glEnableVertexAttribArray(uvAttrib);
	glVertexAttribPointer(uvAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat),
			(void*) (3 * sizeof(GLfloat)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0);

	numElements = (itobjVertices);
}
