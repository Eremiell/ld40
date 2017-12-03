#include "inc/texture_manager.hpp"
#include <fstream>
#include <nlohmann/json.hpp>

namespace ld40 {
	void TextureManager::load_sheet(std::string sheet) {
		std::ifstream file(this->get_full_path(sheet));
		nlohmann::json json;
		file >> json;
		file.close();
		auto sheet_texture = this->sheets.emplace(json.at(u8"filename"), new sf::Texture());
		sheet_texture.first->second->loadFromFile(this->get_full_path(json.at(u8"filename").get<std::string>()));
		int size = json.at(u8"size");
		for (auto &texture : json.at(u8"textures")) {
			this->textures.emplace(texture.at(u8"species"), std::make_pair<const sf::Texture*, sf::Rect<int>>(sheet_texture.first->second.get(), sf::Rect<int>(texture.at(u8"x"), texture.at(u8"y"), size, size)));
		}
		return;
	}

	std::pair<const sf::Texture*, sf::Rect<int>> TextureManager::get_texture(std::string texture) const {
		if (this->textures.count(texture)) {
			return this->textures.at(texture);
		}
		return std::make_pair<const sf::Texture*, sf::Rect<int>>(nullptr, sf::Rect<int>());
	}

	std::experimental::filesystem::path TextureManager::get_full_path(std::string_view filename) {
		std::experimental::filesystem::path path;
		path.append(u8"res").append(u8"img").append(filename);
		return path;
	}
}