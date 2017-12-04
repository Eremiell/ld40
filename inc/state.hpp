#pragma once
#ifndef STATE_HPP
#define STATE_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include "inc/texture_manager.hpp"
#include "inc/sound_manager.hpp"

namespace ld40 {
	class State {
		public:
			State(sf::RenderWindow &window, TextureManager &tm, SoundManager &sm);
			virtual ~State();
			virtual void integrate(std::uint8_t controls) = 0;
			virtual void render() = 0;
		protected:
			sf::RenderWindow &window;
			TextureManager &tm;
			SoundManager &sm;
	};
}

#endif