#pragma once
#ifndef SPECIES_CATALOGUE_HPP
#define SPECIES_CATALOGUE_HPP

#include <vector>
#include "inc/species.hpp"

namespace ld40 {
	class SpeciesCatalogue {
		public:
			SpeciesCatalogue();
			void add_species(std::string species, std::string habitat);
			const Species* get_species(std::string species = "") const;
		private:
			std::vector<Species> catalogue;
	};
}

#endif