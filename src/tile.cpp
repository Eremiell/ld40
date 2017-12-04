#include "inc/tile.hpp"

namespace ld40 {
	Tile::Tile(sf::Color colour, std::string habitat, std::optional<Species> species) : colour(colour), species(species), habitat(habitat) {}

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

	void Tile::set_habitat(std::string habitat) {
		this->habitat = habitat;
	}

	std::string Tile::get_habitat() const {
		return this->habitat;
	}
}