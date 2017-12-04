#pragma once
#ifndef TILE_HPP
#define TILE_HPP

#include <optional>
#include <string>
#include "inc/palette.hpp"
#include "inc/species.hpp"

namespace ld40 {
	class Tile {
		public:
			Tile(sf::Color colour = Palette::Green, std::string habitat = u8"plains", std::optional<Species> species = {});
			void set_colour(sf::Color colour = Palette::Green);
			void set_species(std::optional<Species> species = {});
			sf::Color get_colour() const;
			std::optional<Species> get_species() const;
			void set_habitat(std::string habitat = u8"plains");
			std::string get_habitat() const;
		private:
			sf::Color colour;
			std::optional<Species> species;
			std::string habitat;
	};
}

#endif