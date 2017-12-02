#pragma once
#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics/RenderWindow.hpp>

namespace ld40 {
	class Game {
		public:
			Game();
			void run();
		private:
			sf::RenderWindow window;
	};
}

#endif