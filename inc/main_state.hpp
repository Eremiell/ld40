#pragma once
#ifndef MAIN_STATE_HPP
#define MAIN_STATE_HPP

#include "inc/state.hpp"
#include <vector>
#include <cstdint>
#include <optional>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include "inc/tile.hpp"

namespace ld40 {
	class MainState : public State {
		public:
			MainState(sf::RenderWindow &window);
			virtual void integrate(std::uint8_t controls) override;
			virtual void render() override;
		private:
			sf::Vector2<std::uint8_t> size;
			sf::RectangleShape zone;
			sf::Vector2<std::uint8_t> position;
			std::optional<sf::Vector2<std::uint8_t>> selected;
			std::vector<std::vector<Tile>> board;
	};
}

#endif