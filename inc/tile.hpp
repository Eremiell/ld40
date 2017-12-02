#pragma once
#ifndef TILE_HPP
#define TILE_HPP

#include "inc/palette.hpp"

namespace ld40 {
	class Tile {
		public:
			Tile(sf::Color colour = Palette::Green);
			void set_colour(sf::Color colour = Palette::Green);
			sf::Color get_colour() const;
		private:
			sf::Color colour;
	};
}

#endif