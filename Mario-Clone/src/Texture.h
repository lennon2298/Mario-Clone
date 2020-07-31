#pragma once

#include <glad/glad.h>
#include "ErrorHandling.h"

class Texture {
private:
	unsigned int m_ID;
	unsigned int m_Width, m_Height;
	unsigned int m_Internal_Format, m_Image_Format;
	unsigned int m_Wrap_S, m_Wrap_T;
	unsigned int m_Filter_Min, m_Filter_Max;

public:
	Texture();
	~Texture();
	void Generate(unsigned int width, unsigned int height, unsigned char* data);

	void Bind(unsigned int i=0) const;
	void Unbind() const;
	void SetTexWrap(unsigned int wrap_s, unsigned int wrap_t);
	void SetMinMaxFilter(unsigned int minFilter, unsigned maxFilter);

	void SetAlphaChannel();
};