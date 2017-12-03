#include "inc/main_state.hpp"
#include <cstdint>
#include <cmath>
#include <random>
#include <chrono>
#include "inc/controls.hpp"
#include "inc/palette.hpp"

namespace ld40 {
	MainState::MainState(sf::RenderWindow &window, TextureManager &tm) : State(window, tm), size(5u, 5u), zone(sf::Vector2<float>(128.0f, 128.0f)), position(2u, 2u), turn(0ull), over(false) {
		this->tm.load_sheet(u8"sprite_sheet.json");
		this->tm.load_sheet(u8"animal_icons.json");
		this->board.resize(5);
		for (std::size_t i = 0; i < 5; ++i) {
			this->board.at(i).resize(5);
		}
		this->zone.setOrigin(64.0f, 64.0f);
		this->zone.setOutlineThickness(5.0f);
		this->board.at(2).at(2).set_species(*this->catalogue.get_species());
		this->generate_gates();
	}

	void MainState::integrate(std::uint8_t controls) {
		if (!over) {
			if (controls & static_cast<std::uint8_t>(Controls::Up) && this->position.y) {
				--this->position.y;
			}
			if (controls & static_cast<std::uint8_t>(Controls::Left) && this->position.x) {
				--this->position.x;
			}
			if (controls & static_cast<std::uint8_t>(Controls::Down) && this->position.y < this->size.y - 1) {
				++this->position.y;
			}
			if (controls & static_cast<std::uint8_t>(Controls::Right) && this->position.x < this->size.x - 1) {
				++this->position.x;
			}
			if (controls & static_cast<std::uint8_t>(Controls::Select)) {
				if (this->selected.has_value() && this->position == this->selected.value()) {
					this->selected = {};
				}
				else if (this->selected.has_value() && std::abs(this->position.x - this->selected.value().x) + std::abs(this->position.y - this->selected.value().y) == 1 && !this->board.at(this->position.x).at(this->position.y).get_species().has_value()) {
					this->board.at(this->position.x).at(this->position.y).set_species(this->board.at(this->selected.value().x).at(this->selected.value().y).get_species());
					this->board.at(this->selected.value().x).at(this->selected.value().y).set_species();
					this->selected = {};
					++this->turn;
				}
				else if (this->board.at(this->position.x).at(this->position.y).get_species().has_value()) {
					this->selected = this->position;
					//this->board.at(this->position.x).at(this->position.y).set_colour(Palette::Orange);
				}
			}
			if (this->turn % 5 == 2 && !this->incoming.has_value()) {
				this->incoming = *this->catalogue.get_species();
				std::mt19937_64 mt(std::chrono::high_resolution_clock::now().time_since_epoch().count());
				std::uniform_int_distribution<std::size_t> dist(0, this->gates.size() - 1);
				this->to_gate = dist(mt);
			}
			if (!(this->turn % 5) && this->incoming.has_value()) {
				if (this->board.at(this->gates.at(this->to_gate).x).at(this->gates.at(this->to_gate).y).get_species().has_value()) {
					over = true;
				}
				else {
					this->board.at(this->gates.at(this->to_gate).x).at(this->gates.at(this->to_gate).y).set_species(this->incoming.value());
					this->incoming = {};
				}
			}
		}
		return;
	}

	void MainState::render() {
		for (std::int8_t i = 0; i < 5; ++i) {
			for (std::int8_t j = 0; j < 5; ++j) {
				this->zone.setPosition(500.0f + (i - 2) * 138.0f, 500.0f + (j - 2) * 138.0f);
				this->zone.setFillColor(this->board.at(i).at(j).get_colour());
				this->zone.setOutlineColor(sf::Color::Transparent);
				if (this->position.x == i && this->position.y == j) {
					this->zone.setOutlineColor(Palette::White);
				}
				if (this->selected.has_value() && this->selected.value().x == i && this->selected.value().y == j) {
					this->zone.setOutlineColor(Palette::Red);
				}
				this->window.draw(this->zone);
				if (this->board.at(i).at(j).get_species().has_value()) {
					auto texture = this->tm.get_texture(this->board.at(i).at(j).get_species().value().get_name());
					this->sprite.setTexture(*texture.first);
					this->sprite.setTextureRect(texture.second);
					this->sprite.setScale(1.0f, 1.0f);
					this->sprite.setOrigin(64.0f, 64.0f);
					this->sprite.setPosition(500.0f + (i - 2) * 138.0f, 500.0f + (j - 2) * 138.0f);
					this->window.draw(this->sprite);
				}
			}
		}
		if (this->incoming.has_value()) {
			auto texture = this->tm.get_texture(this->incoming.value().get_name() + u8"_icon");
			this->sprite.setTexture(*texture.first);
			this->sprite.setTextureRect(texture.second);
			this->sprite.setOrigin(8.0f, 8.0f);
			this->sprite.setScale(2.0f, 2.0f);
			if (!this->gates.at(this->to_gate).x) {
				this->sprite.setPosition(500.0f + -3 * 138.0f, 500.0f + (this->gates.at(this->to_gate).y - 2) * 138.0f);
			}
			else if (!this->gates.at(this->to_gate).y) {
				this->sprite.setPosition(500.0f + (this->gates.at(this->to_gate).x - 2) * 138.0f, 500.0f + -3 * 138.0f);
			}
			else if (this->gates.at(this->to_gate).x == static_cast<std::size_t>(this->size.x - 1)) {
				this->sprite.setPosition(500.0f + 3 * 138.0f, 500.0f + (this->gates.at(this->to_gate).y - 2) * 138.0f);
			}
			else {
				this->sprite.setPosition(500.0f + (this->gates.at(this->to_gate).x - 2) * 138.0f, 500.0f + 3 * 138.0f);
			}
			this->window.draw(this->sprite);
		}
		return;
	}

	void MainState::generate_gates() {
		this->gates.clear();
		for (std::uint8_t i = 1; i < this->size.x - 1; ++i) {
			if ((i - 1) % 3 == 1) {
				this->gates.emplace_back(i, 0);
			}
		}
		for (std::uint8_t i = 1; i < this->size.y - 1; ++i) {
			if ((i - 1) % 3 == 1) {
				this->gates.emplace_back(this->size.x - 1, i);
			}
		}
		for (std::size_t i = this->size.x - 2; i; --i) {
			if ((this->size.x - i - 2) % 3 == 1) {
				this->gates.emplace_back(i, this->size.y - 1);
			}
		}
		for (std::size_t i = this->size.y - 2; i; --i) {
			if ((this->size.y - i - 2) % 3 == 1) {
				this->gates.emplace_back(0, i);
			}
		}
		return;
	}
}