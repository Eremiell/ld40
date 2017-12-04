#pragma once
#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#include <unordered_map>
#include <string>
#include <memory>
#include <utility>
#include <string_view>
#ifndef _WIN32
#include <experimental/filesystem>
#endif
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>

namespace ld40 {
	class TextureManager {
		public:
			void load_sheet(std::string sheet);
			std::pair<const sf::Texture*, sf::Rect<int>> get_texture(std::string texture) const;
		private:
			std::unordered_map<std::string, std::unique_ptr<sf::Texture>> sheets;
			std::unordered_map<std::string, std::pair<const sf::Texture*, sf::Rect<int>>> textures;
#ifndef _WIN32
			std::experimental::filesystem::path get_full_path(std::string_view filename);
#else
			std::string get_full_path(std::string_view filename);
#endif
	};
}

#endif