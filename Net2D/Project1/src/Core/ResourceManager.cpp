#include "ResourceManager.h"

ResourceManager& ResourceManager::get_instance()
{
	static ResourceManager instance;

	return instance;
}

Shader* ResourceManager::load_shaders(const std::string name, const char* vertexPath, const char* fragmentPath)
{
	auto shader = std::make_unique<Shader>(vertexPath, fragmentPath);
	auto it = shader_storage.find(name);
	if (it != shader_storage.end())
	{
		std::cout << "Shader already exists" << std::endl;
		return nullptr;
	}
	shader_storage[name] = std::move(shader);
	return shader_storage[name].get();
}

Shader* ResourceManager::get_shaders(const std::string name)
{
	auto it = shader_storage.find(name);
	return it != shader_storage.end() ? it->second.get() : nullptr;
}

void ResourceManager::load_textures(const std::string name, const char* file_path)
{
	auto texture = std::make_unique<Texture>(file_path);
	auto it = texture_storage.find(name);
	if (it != texture_storage.end()) return;
	texture_storage[name] = std::move(texture);
}

Texture* ResourceManager::get_texture(const char* name)
{
	auto it = texture_storage.find(name);
	return it != texture_storage.end() ? it->second.get() : nullptr;
}
Texture* ResourceManager::get_texture(const std::string name)
{
	auto it = texture_storage.find(name);
	return it != texture_storage.end() ? it->second.get() : nullptr;
}
