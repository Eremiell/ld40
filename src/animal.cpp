#include "inc/animal.hpp"

namespace ld40 {
	Animal::Animal(Species species) : energy(3u), species(species) {}

	std::string Animal::get_name() const {
		return this->species.get_name();
	}

	std::string Animal::get_habitat() const {
		return this->species.get_habitat();
	}
}