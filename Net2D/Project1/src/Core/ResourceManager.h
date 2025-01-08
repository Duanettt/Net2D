#pragma once
#include <unordered_map>
#include <memory>
#include <string>
#include "../GL/Shader.h"
#include "../GL/Texture.h"

class ResourceManager
{
public:
	static ResourceManager& get_instance();
	Shader* load_shaders(const std::string name, const char* vertexPath, const char* fragmentPath);
	Shader* get_shaders(const std::string name);
	void load_textures(const std::string name, const char* file_path);
	Texture* get_texture(const std::string name);
	Texture* get_texture(const char* name);
	ResourceManager(ResourceManager const&) = delete;
	void operator=(ResourceManager const&) = delete;

private:
	ResourceManager()
	{

	}
	std::unordered_map<std::string, std::unique_ptr<Shader>> shader_storage;
	std::unordered_map < std::string, std::unique_ptr<Texture>> texture_storage;
};

