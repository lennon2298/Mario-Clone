#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"
#include "Texture.h"
#include "ErrorHandling.h"


class SpriteRenderer {
private:
	Shader m_Shader;
	unsigned int m_QuadVAO;

public:
	SpriteRenderer(Shader shader);
	~SpriteRenderer();

	void DrawSprite(Texture& texture, glm::vec2 position,
		glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f,
		glm::vec3 color = glm::vec3(1.0f));

private:
	void InitRenderData();
};