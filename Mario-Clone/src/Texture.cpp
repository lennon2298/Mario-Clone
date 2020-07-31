#include <iostream>
#include "Texture.h"

Texture::Texture()
	: m_Width(0), m_Height(0), m_Internal_Format(GL_RGB), m_Image_Format(GL_RGB), m_Wrap_S(GL_REPEAT), m_Wrap_T(GL_REPEAT), m_Filter_Min(GL_LINEAR), m_Filter_Max(GL_LINEAR)
{
	GLCall(glGenTextures(1, &m_ID));
}

Texture::~Texture()
{
}

void Texture::Generate(unsigned int width, unsigned int height, unsigned char* data)
{
	m_Width = width;
	m_Height = height;
	GLCall(glBindTexture(GL_TEXTURE_2D, m_ID));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_Wrap_S));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_Wrap_T));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_Filter_Min));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_Filter_Max));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, m_Internal_Format, m_Width, m_Height, 0, m_Image_Format, GL_UNSIGNED_BYTE, data));

	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void Texture::Bind(unsigned int i) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + i));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_ID));
}

void Texture::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void Texture::SetTexWrap(unsigned int wrap_s, unsigned int wrap_t)
{
	m_Wrap_S = wrap_s;
	m_Wrap_T = wrap_t;
}

void Texture::SetMinMaxFilter(unsigned int minFilter, unsigned maxFilter)
{
	m_Filter_Min = minFilter;
	m_Filter_Max = maxFilter;
}

void Texture::SetAlphaChannel()
{
	m_Internal_Format = GL_RGBA;
	m_Image_Format = GL_RGBA;
}
