#pragma once
#ifndef STATE_HPP
#define STATE_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include "inc/texture_manager.hpp"

namespace ld40 {
	class State {
		public:
			State(sf::RenderWindow &window, TextureManager &tm);
			virtual ~State();
			virtual void integrate(std::uint8_t controls) = 0;
			virtual void render() = 0;
		protected:
			sf::RenderWindow &window;
			TextureManager &tm;
	};
}

#endif