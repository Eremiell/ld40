#pragma once
#ifndef FONT_RENDERER_HPP
#define FONT_RENDERER_HPP

#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "inc/texture_manager.hpp"

namespace ld40 {
	class FontRenderer {
		public:
			FontRenderer(sf::RenderWindow &window, TextureManager &tm);
			void render(std::string text, sf::Vector2<float> position);
		private:
			sf::RenderWindow &window;
			TextureManager &tm;
			sf::Sprite letter;
	};
}

#endif