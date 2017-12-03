#pragma once
#ifndef TILE_HPP
#define TILE_HPP

#include <optional>
#include "inc/palette.hpp"
#include "inc/species.hpp"

namespace ld40 {
	class Tile {
		public:
			Tile(sf::Color colour = Palette::Green, std::optional<Species> species = {});
			void set_colour(sf::Color colour = Palette::Green);
			void set_species(std::optional<Species> species = {});
			sf::Color get_colour() const;
			std::optional<Species> get_species() const;
		private:
			sf::Color colour;
			std::optional<Species> species;
	};
}

#endif