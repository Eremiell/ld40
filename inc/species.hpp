#pragma once
#ifndef SPECIES_HPP
#define SPECIES_HPP

#include <string>

namespace ld40 {
	class Species {
		public:
			Species(std::string name, std::string habitat);
			std::string get_name() const;
			std::string get_habitat() const;
		private:
			std::string name;
			std::string habitat;
	};
}

#endif