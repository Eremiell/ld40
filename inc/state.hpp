#pragma once
#ifndef STATE_HPP
#define STATE_HPP

#include <SFML/Graphics/RenderWindow.hpp>

namespace ld40 {
	class State {
		public:
			State(sf::RenderWindow &window);
			virtual ~State();
			virtual void integrate() = 0;
			virtual void render() = 0;
		protected:
			sf::RenderWindow &window;
	};
}

#endif