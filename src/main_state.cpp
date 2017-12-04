#include "inc/main_state.hpp"
#include <cstdint>
#include <cmath>
#include <random>
#include <chrono>
#include "inc/controls.hpp"
#include "inc/palette.hpp"

#include <iostream>

namespace ld40 {
	MainState::MainState(sf::RenderWindow &window, TextureManager &tm, SoundManager &sm) : State(window, tm, sm), size(5u, 5u), zone(sf::Vector2<float>(128.0f, 128.0f)), selector(sf::Vector2<float>(118.0f, 118.0f)), position(2u, 2u), turn(0ull), over(false), resize(false) {
		this->tm.load_sheet(u8"sprite_sheet.json");
		this->tm.load_sheet(u8"animal_icons.json");
		this->tm.load_sheet(u8"game_tiles.json");
		this->board.resize(this->size.x);
		for (std::size_t i = 0; i < this->size.x; ++i) {
			this->board.at(i).resize(this->size.y);
		}
		this->zone.setOrigin(64.0f, 64.0f);
		this->selector.setFillColor(sf::Color::Transparent);
		this->selector.setOrigin(59.0f, 59.0f);
		this->selector.setOutlineThickness(5.0f);
		this->board.at((this->size.x - 1) / 2).at((this->size.y - 1) / 2).set_species(*this->catalogue.get_species());
		this->generate_gates();
		this->sm.load_soundlist(u8"soundlist.json");
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
					this->sound.setBuffer(*this->sm.get_sound(this->board.at(this->position.x).at(this->position.y).get_species().value().get_name()));
					this->sound.play();
				}
				else if (this->selected.has_value() && std::abs(this->position.x - this->selected.value().x) + std::abs(this->position.y - this->selected.value().y) == 1 && !this->board.at(this->position.x).at(this->position.y).get_species().has_value()) {
					this->board.at(this->position.x).at(this->position.y).set_species(this->board.at(this->selected.value().x).at(this->selected.value().y).get_species());
					this->board.at(this->selected.value().x).at(this->selected.value().y).set_species();
					this->selected = {};
					this->sound.setBuffer(*this->sm.get_sound(this->board.at(this->position.x).at(this->position.y).get_species().value().get_name()));
					this->sound.play();
					++this->turn;
				}
				else if (this->board.at(this->position.x).at(this->position.y).get_species().has_value()) {
					this->selected = this->position;
					this->sound.setBuffer(*this->sm.get_sound(this->board.at(this->position.x).at(this->position.y).get_species().value().get_name()));
					this->sound.play();
					//this->board.at(this->position.x).at(this->position.y).set_colour(Palette::Orange);
				}
			}
			if (this->turn % 5 == 2 && !this->incoming.has_value()) {
				this->incoming = *this->catalogue.get_species();
				std::mt19937_64 mt(std::chrono::high_resolution_clock::now().time_since_epoch().count());
				std::uniform_int_distribution<std::size_t> dist(0, this->gates.size() - 1);
				this->to_gate = dist(mt);
				this->sound.setBuffer(*this->sm.get_sound(this->incoming.value().get_name()));
				this->sound.play();
			}
			if (!(this->turn % 5) && this->incoming.has_value()) {
				this->sound.setBuffer(*this->sm.get_sound(this->incoming.value().get_name()));
				this->sound.play();
				if (this->board.at(this->gates.at(this->to_gate).x).at(this->gates.at(this->to_gate).y).get_species().has_value()) {
					over = true;
				}
				else {
					this->board.at(this->gates.at(this->to_gate).x).at(this->gates.at(this->to_gate).y).set_species(this->incoming.value());
					this->incoming = {};
				}
				this->resize = true;
			}
			if (this->turn && this->resize && !(this->turn % 20)) {
				std::uint8_t direction = this->turn % 80 / 20;
				switch (direction) {
					case 0:
						for (auto &row : this->board) {
							row.emplace(row.begin());
						}
						++this->size.y;
						break;
					case 1:
						{
							auto &row = this->board.emplace_back();
							row.resize(++this->size.x);
						}
						break;
					case 2:
						for (auto &row : this->board) {
							row.emplace_back();
						}
						++this->size.y;
						break;
					case 3:
						{
							auto row = this->board.emplace(this->board.begin());
							row->resize(++this->size.x);
						}
						break;
				}
				this->generate_gates();
				this->resize = false;
			}
		}
		return;
	}

	void MainState::render() {
		auto view = this->window.getDefaultView();
		view.setCenter(500.0f, 500.f);
		std::size_t view_size = std::max(this->size.x, this->size.y) + 1;
		float ratio = 128.0f / (900.0f / view_size);
		view.zoom(ratio);
		this->window.setView(view);
		for (std::int8_t i = 0; i < this->size.x; ++i) {
			for (std::int8_t j = 0; j < this->size.y; ++j) {
				this->zone.setPosition(500.0f + (i - ((this->size.x - 1) / 2.0f)) * 128.0f, 500.0f + (j - ((this->size.y - 1) / 2.0f)) * 128.0f);
				this->zone.setFillColor(this->board.at(i).at(j).get_colour());
				//this->zone.setOutlineColor(sf::Color::Transparent);
				this->window.draw(this->zone);
				if (this->position.x == i && this->position.y == j) {
					this->selector.setOutlineColor(Palette::White);
					this->selector.setPosition(500.0f + (i - ((this->size.x - 1) / 2.0f)) * 128.0f, 500.0f + (j - ((this->size.y - 1) / 2.0f)) * 128.0f);
					this->window.draw(this->selector);
				}
				if (this->selected.has_value() && this->selected.value().x == i && this->selected.value().y == j) {
					this->selector.setOutlineColor(Palette::Red);
					this->selector.setPosition(500.0f + (i - ((this->size.x - 1) / 2.0f)) * 128.0f, 500.0f + (j - ((this->size.y - 1) / 2.0f)) * 128.0f);
					this->window.draw(this->selector);
				}
				if (this->board.at(i).at(j).get_species().has_value()) {
					auto texture = this->tm.get_texture(this->board.at(i).at(j).get_species().value().get_name());
					this->sprite.setTexture(*texture.first);
					this->sprite.setTextureRect(texture.second);
					this->sprite.setScale(1.0f, 1.0f);
					this->sprite.setOrigin(64.0f, 64.0f);
					this->sprite.setRotation(0.0f);
					this->sprite.setPosition(500.0f + (i - ((this->size.x - 1) / 2.0f)) * 128.0f, 500.0f + (j - ((this->size.y - 1) / 2.0f)) * 128.0f);
					this->window.draw(this->sprite);
				}
			}
		}
		for (std::int8_t i = 0; i < this->size.x; ++i) {
			auto texture = this->tm.get_texture(u8"wall_EW");
			for (auto &gate : this->gates) {
				if (static_cast<int>(gate.x) == i && !gate.y) {
					texture = this->tm.get_texture(u8"gate_EW");
					break;
				}
			}
			this->sprite.setTexture(*texture.first);
			this->sprite.setTextureRect(texture.second);
			this->sprite.setScale(1.0f, 1.0f);
			this->sprite.setOrigin(64.0f, 64.0f);
			this->sprite.setRotation(0.0f);
			this->sprite.setPosition(500.0f + (i - ((this->size.x - 1) / 2.0f)) * 128.0f, 500.0f - (((this->size.y - 1) / 2.0f) + 1) * 128.0f);
			this->window.draw(this->sprite);
		}
		for (std::int8_t i = 0; i < this->size.x; ++i) {
			auto texture = this->tm.get_texture(u8"wall_EW");
			for (auto &gate : this->gates) {
				if (static_cast<int>(gate.x) == i && gate.y == this->size.y - 1u) {
					texture = this->tm.get_texture(u8"gate_EW");
					break;
				}
			}
			this->sprite.setTexture(*texture.first);
			this->sprite.setTextureRect(texture.second);
			this->sprite.setScale(1.0f, 1.0f);
			this->sprite.setOrigin(64.0f, 64.0f);
			this->sprite.setRotation(180.0f);
			this->sprite.setPosition(500.0f + (i - ((this->size.x - 1) / 2.0f)) * 128.0f, 500.0f + (((this->size.y - 1) / 2.0f) + 1) * 128.0f);
			this->window.draw(this->sprite);
		}
		for (std::int8_t i = 0; i < this->size.y; ++i) {
			auto texture = this->tm.get_texture(u8"wall_NS");
			for (auto &gate : this->gates) {
				if (static_cast<int>(gate.y) == i && !gate.x) {
					texture = this->tm.get_texture(u8"gate_NS");
					break;
				}
			}
			this->sprite.setTexture(*texture.first);
			this->sprite.setTextureRect(texture.second);
			this->sprite.setScale(1.0f, 1.0f);
			this->sprite.setOrigin(64.0f, 64.0f);
			this->sprite.setRotation(180.0f);
			this->sprite.setPosition(500.0f - (((this->size.x - 1) / 2.0f) + 1) * 128.0f, 500.0f + (i - ((this->size.y - 1) / 2.0f)) * 128.0f);
			this->window.draw(this->sprite);
		}
		for (std::int8_t i = 0; i < this->size.y; ++i) {
			auto texture = this->tm.get_texture(u8"wall_NS");
			for (auto &gate : this->gates) {
				if (static_cast<int>(gate.y) == i && gate.x == this->size.x - 1u) {
					texture = this->tm.get_texture(u8"gate_NS");
					break;
				}
			}
			this->sprite.setTexture(*texture.first);
			this->sprite.setTextureRect(texture.second);
			this->sprite.setScale(1.0f, 1.0f);
			this->sprite.setOrigin(64.0f, 64.0f);
			this->sprite.setRotation(0.0f);
			this->sprite.setPosition(500.0f + (((this->size.x - 1) / 2.0f) + 1) * 128.0f, 500.0f + (i - ((this->size.y - 1) / 2.0f)) * 128.0f);
			this->window.draw(this->sprite);
		}
		auto texture = this->tm.get_texture(u8"corner_NE");
		this->sprite.setTexture(*texture.first);
		this->sprite.setTextureRect(texture.second);
		this->sprite.setScale(1.0f, 1.0f);
		this->sprite.setOrigin(64.0f, 64.0f);
		this->sprite.setRotation(0.0f);
		this->sprite.setPosition(500.0f + (((this->size.x - 1) / 2.0f) + 1) * 128.0f, 500.0f - (((this->size.y - 1) / 2.0f) + 1) * 128.0f);
		this->window.draw(this->sprite);
		this->sprite.setRotation(90.0f);
		this->sprite.setPosition(500.0f + (((this->size.x - 1) / 2.0f) + 1) * 128.0f, 500.0f + (((this->size.y - 1) / 2.0f) + 1) * 128.0f);
		this->window.draw(this->sprite);
		this->sprite.setRotation(180.0f);
		this->sprite.setPosition(500.0f - (((this->size.x - 1) / 2.0f) + 1) * 128.0f, 500.0f + (((this->size.y - 1) / 2.0f) + 1) * 128.0f);
		this->window.draw(this->sprite);
		this->sprite.setRotation(270.0f);
		this->sprite.setPosition(500.0f - (((this->size.x - 1) / 2.0f) + 1) * 128.0f, 500.0f - (((this->size.y - 1) / 2.0f) + 1) * 128.0f);
		this->window.draw(this->sprite);
		if (this->incoming.has_value()) {
			auto texture = this->tm.get_texture(this->incoming.value().get_name() + u8"_icon");
			this->sprite.setTexture(*texture.first);
			this->sprite.setTextureRect(texture.second);
			this->sprite.setOrigin(8.0f, 8.0f);
			this->sprite.setRotation(0.0f);
			this->sprite.setScale(2.0f, 2.0f);
			if (!this->gates.at(this->to_gate).x) {
				this->sprite.setPosition(500.0f - (((this->size.x - 1) / 2.0f) + 1) * 128.0f, 500.0f + (this->gates.at(this->to_gate).y - ((this->size.y - 1) / 2.0f)) * 128.0f);
			}
			else if (!this->gates.at(this->to_gate).y) {
				this->sprite.setPosition(500.0f + (this->gates.at(this->to_gate).x - ((this->size.x - 1) / 2.0f)) * 128.0f, 500.0f - (((this->size.y - 1) / 2.0f) + 1) * 128.0f);
			}
			else if (this->gates.at(this->to_gate).x == static_cast<std::size_t>(this->size.x - 1)) {
				this->sprite.setPosition(500.0f + (((this->size.x - 1) / 2.0f) + 1) * 128.0f, 500.0f + (this->gates.at(this->to_gate).y - ((this->size.y - 1) / 2.0f)) * 128.0f);
			}
			else {
				this->sprite.setPosition(500.0f + (this->gates.at(this->to_gate).x - ((this->size.x - 1) / 2.0f)) * 128.0f, 500.0f + (((this->size.y - 1) / 2.0f) + 1) * 128.0f);
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