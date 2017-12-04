#pragma once
#ifndef SOUND_MANAGER_HPP
#define SOUND_MANAGER_HPP

#include <string>
#include <string_view>
#include <unordered_map>
#include <memory>
#ifndef _WIN32
#include <experimental/filesystem>
#endif
#include <SFML/Audio/SoundBuffer.hpp>

namespace ld40 {
	class SoundManager {
		public:
			void load_sound(std::string sound);
			void load_soundlist(std::string soundlist);
			const sf::SoundBuffer* get_sound(std::string sound) const;
		private:
			std::unordered_map<std::string, std::unique_ptr<sf::SoundBuffer>> sounds;
#ifndef _WIN32
			std::experimental::filesystem::path get_full_path(std::string_view filename);
#else
			std::string get_full_path(std::string_view filename);
#endif
	};
}

#endif