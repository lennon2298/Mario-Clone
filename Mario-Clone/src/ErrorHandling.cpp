#include "ErrorHandling.h"

#include <iostream>

void GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* func, const char* file, int line) {
	while (GLenum error = glGetError()) {
		std::cout << "OpenGL Error :" << error << " " << func << " " << file << "Found at line " << line << std::endl;
	}
	return -1;
}