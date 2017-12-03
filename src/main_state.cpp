#include "inc/main_state.hpp"
#include <cstdint>
#include "inc/controls.hpp"
#include "inc/palette.hpp"

namespace ld40 {
	MainState::MainState(sf::RenderWindow &window, TextureManager &tm) : State(window, tm), size(5u, 5u), zone(sf::Vector2<float>(128.0f, 128.0f)), position(2u, 2u) {
		this->tm.load_sheet(u8"sprite_sheet.json");
		this->board.resize(5);
		for (std::size_t i = 0; i < 5; ++i) {
			this->board.at(i).resize(5);
		}
		this->zone.setOrigin(64.0f, 64.0f);
		this->zone.setOutlineThickness(5.0f);
		auto texture = this->tm.get_texture(this->catalogue.get_species()->get_name());
		this->sprite.setTexture(*texture.first);
		this->sprite.setTextureRect(texture.second);
		this->sprite.setOrigin(64.0f, 64.0f);
		this->sprite.setPosition(500.0f, 500.0f);
	}

	void MainState::integrate(std::uint8_t controls) {
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
			else {
				this->selected = this->position;
				//this->board.at(this->position.x).at(this->position.y).set_colour(Palette::Orange);
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
			}
		}
		this->window.draw(this->sprite);
		return;
	}
}