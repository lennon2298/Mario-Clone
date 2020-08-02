#pragma once

#include <glad/glad.h>
#include "debugbreak.h"

#define ASSERT(x) if (!(x)) debug_break();

#define GLCall(x) GLClearError();\
		x;\
		ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const char* func, const char* file, int line);