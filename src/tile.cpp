#include "inc/tile.hpp"

namespace ld40 {
	Tile::Tile(sf::Color colour, std::optional<Species> species) : colour(colour), species(species) {}

	void Tile::set_colour(sf::Color colour) {
		this->colour = colour;
		return;
	}

	void Tile::set_species(std::optional<Species> species) {
		this->species = species;
		return;
	}

	sf::Color Tile::get_colour() const {
		return this->colour;
	}

	std::optional<Species> Tile::get_species() const {
		return this->species;
	}
}