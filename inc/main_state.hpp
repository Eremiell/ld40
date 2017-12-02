#pragma once
#ifndef MAIN_STATE_HPP
#define MAIN_STATE_HPP

#include "inc/state.hpp"
#include <vector>
#include <SFML/Graphics/RectangleShape.hpp>
#include "inc/tile.hpp"

namespace ld40 {
	class MainState : public State {
		public:
			MainState(sf::RenderWindow &window);
			virtual void integrate() override;
			virtual void render() override;
		private:
			sf::RectangleShape zone;
			std::vector<std::vector<Tile>> board;
	};
}

#endif