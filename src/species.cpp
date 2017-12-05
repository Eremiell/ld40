#include "inc/species.hpp"

namespace ld40 {
	Species::Species(std::string name, std::string habitat) : name(name), habitat(habitat) {}

	std::string Species::get_name() const {
		return this->name;
	}

	std::string Species::get_habitat() const {
		return this->habitat;
	}
}