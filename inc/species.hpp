#pragma once
#ifndef SPECIES_HPP
#define SPECIES_HPP

#include <string>

namespace ld40 {
	class Species {
		public:
			Species(std::string name);
			std::string get_name() const;
		private:
			std::string name;
	};
}

#endif