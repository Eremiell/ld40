#include "inc/tile.hpp"

namespace ld40 {
	Tile::Tile(sf::Color colour, std::string habitat, std::optional<Animal> animal) : colour(colour), animal(animal), habitat(habitat) {}

	void Tile::set_colour(sf::Color colour) {
		this->colour = colour;
		return;
	}

	void Tile::set_animal(std::optional<Animal> animal) {
		this->animal = animal;
		return;
	}

	sf::Color Tile::get_colour() const {
		return this->colour;
	}

	std::optional<Animal> Tile::get_animal() const {
		return this->animal;
	}

	void Tile::set_habitat(std::string habitat) {
		this->habitat = habitat;
	}

	std::string Tile::get_habitat() const {
		return this->habitat;
	}
}