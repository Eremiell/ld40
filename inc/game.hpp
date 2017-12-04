#pragma once
#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include "inc/main_state.hpp"
#include "inc/texture_manager.hpp"
#include "inc/sound_manager.hpp"
#include "inc/font_renderer.hpp"

namespace ld40 {
	class Game {
		public:
			Game();
			void run();
		private:
			sf::RenderWindow window;
			TextureManager tm;
			SoundManager sm;
			FontRenderer fr;
			std::unique_ptr<State> state;
	};
}

#endif