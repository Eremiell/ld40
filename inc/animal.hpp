#pragma once
#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <string>
#include "inc/species.hpp"

namespace ld40 {
	class Animal {
		public:
			Animal(Species species);
			std::string get_name() const;
			std::string get_habitat() const;
			std::size_t energy;
		private:
			Species species;
	};
}

#endif