#include "ResourceManager.h"

std::unordered_map<std::string, Texture>    ResourceManager::m_TextureMap;
std::unordered_map<std::string, Shader>       ResourceManager::m_ShaderMap;

Shader ResourceManager::LoadShader(const std::string& vertexFile, const std::string& fragmentFile, std::string name)
{
	m_ShaderMap[name] = ParseShader(vertexFile, fragmentFile);
	return m_ShaderMap[name];
}

Shader ResourceManager::GetShader(std::string name)
{
	return m_ShaderMap[name];
}

Texture ResourceManager::LoadTexture(const std::string& texFile, bool alpha, std::string name)
{
	m_TextureMap[name] = ParseTexture(texFile, alpha);
	return m_TextureMap[name];
}

Texture ResourceManager::GetTexture(std::string name)
{
	return m_TextureMap[name];
}

void ResourceManager::Clear()
{
	for (auto iter : m_ShaderMap) {
		iter.second.DeleteShader();
	}

	for (auto iter : m_TextureMap) {
		iter.second.~Texture();
	}
}

Shader ResourceManager::ParseShader(const std::string& vertexFile, const std::string& fragmentFile)
{
	std::ifstream vertStream(vertexFile);
	std::ifstream fragStream(fragmentFile);

	std::stringstream vertShader, fragShader;
	std::string line;

	while (getline(vertStream, line)) {
		vertShader << line << "\n";
	}
	while (getline(fragStream, line)) {
		fragShader << line << "\n";
	}

	Shader shader;

	shader.Compile(vertShader.str(), fragShader.str());

	return shader;
}

Texture ResourceManager::ParseTexture(const std::string& texFile, bool alpha)
{
	Texture texture;
	if (alpha)
	{
		texture.SetAlphaChannel();
	}
	// load image
	int width, height, nrChannels;
	unsigned char* data = stbi_load(texFile.c_str(), &width, &height, &nrChannels, 0);
	// now generate texture
	texture.Generate(width, height, data);
	// and finally free image data
	stbi_image_free(data);
	return texture;
}
