#include "inc/sound_manager.hpp"
#include <fstream>
#include <nlohmann/json.hpp>

namespace ld40 {
	void SoundManager::load_sound(std::string sound) {
		auto sfx = this->sounds.emplace(sound, new sf::SoundBuffer());
		sfx.first->second->loadFromFile(this->get_full_path(sound));
		return;
	}

	void SoundManager::load_soundlist(std::string soundlist) {
		std::ifstream file(this->get_full_path(soundlist));
		nlohmann::json json;
		file >> json;
		file.close();
		for (auto &item : json) {
			auto sfx = this->sounds.emplace(item.at(u8"sound"), new sf::SoundBuffer());
			sfx.first->second->loadFromFile(this->get_full_path(item.at(u8"filename").get<std::string>()));
		}
		return;
	}

	const sf::SoundBuffer* SoundManager::get_sound(std::string sound) const {
		if (this->sounds.count(sound)) {
			return this->sounds.at(sound).get();
		}
		return nullptr;
	}

	std::experimental::filesystem::path SoundManager::get_full_path(std::string_view filename) {
		std::experimental::filesystem::path path;
		path.append(u8"res").append(u8"sfx").append(filename);
		return path;
	}
}