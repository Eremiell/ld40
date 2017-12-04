#include "inc/species_catalogue.hpp"
#include <random>
#include <chrono>
#include <fstream>
#ifndef _WIN32
#include <experimental/filesystem>
#else
#include <sstream>
#endif
#include <nlohmann/json.hpp>

namespace ld40 {
	SpeciesCatalogue::SpeciesCatalogue() {
#ifndef _WIN32
		std::experimental::filesystem::path path;
		path.append(u8"res").append(u8"species.json");
#else
		std::stringstream ss;
		ss << u8"res" << '//' << u8"species.json";
		std::string path = ss.str();
#endif
		std::ifstream file(path);
		nlohmann::json json;
		file >> json;
		file.close();
		for (auto &species : json) {
			this->add_species(species.at(u8"species"));
		}
	}

	void SpeciesCatalogue::add_species(std::string species) {
		this->catalogue.emplace_back(species);
	}

	const Species* SpeciesCatalogue::get_species(std::string species) const {
		if (species == "") {
			std::mt19937_64 mt(std::chrono::high_resolution_clock::now().time_since_epoch().count());
			std::uniform_int_distribution<std::size_t> dist(0, this->catalogue.size() - 1);
			return &this->catalogue.at(dist(mt));
		}
		for (auto &sp : this->catalogue) {
			if (sp.get_name() == species) {
				return &sp;
			}
		}
		return nullptr;
	}
}