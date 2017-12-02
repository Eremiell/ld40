#pragma once
#ifndef TILE_HPP
#define TILE_HPP

#include "inc/palette.hpp"

namespace ld40 {
	class Tile {
		public:
			Tile(sf::Color colour = palette::Green);
			void set_colour(sf::Color colour = palette::Green);
			sf::Color get_colour() const;
		private:
			sf::Color colour;
	};
}

#endif