#include "inc/species.hpp"

namespace ld40 {
	Species::Species(std::string name) : name(name) {}

	std::string Species::get_name() const {
		return this->name;
	}
}