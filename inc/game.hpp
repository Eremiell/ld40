#pragma once
#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include "inc/main_state.hpp"

namespace ld40 {
	class Game {
		public:
			Game();
			void run();
		private:
			sf::RenderWindow window;
			std::unique_ptr<State> state;
	};
}

#endif