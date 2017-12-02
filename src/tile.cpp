#include "inc/tile.hpp"

namespace ld40 {
	Tile::Tile(sf::Color colour) : colour(colour) {}

	void Tile::set_colour(sf::Color colour) {
		this->colour = colour;
		return;
	}

	sf::Color Tile::get_colour() const {
		return this->colour;
	}
}