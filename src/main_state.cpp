#include "inc/main_state.hpp"
#include <cstdint>
#include "inc/controls.hpp"
#include "inc/palette.hpp"

namespace ld40 {
	MainState::MainState(sf::RenderWindow &window) : State(window), size(5u, 5u), zone(sf::Vector2<float>(100.0f, 100.0f)), position(2u, 2u) {
		this->board.resize(5);
		for (std::size_t i = 0; i < 5; ++i) {
			this->board.at(i).resize(5);
		}
		this->zone.setOrigin(50.0f, 50.0f);
		this->zone.setOutlineThickness(5.0f);
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
			this->board.at(this->position.x).at(this->position.y).set_colour(Palette::Orange);
		}
		return;
	}

	void MainState::render() {
		for (std::int8_t i = 0; i < 5; ++i) {
			for (std::int8_t j = 0; j < 5; ++j) {
				this->zone.setPosition(500.0f + (i - 2) * 110.0f, 500.0f + (j - 2) * 110.0f);
				this->zone.setFillColor(this->board.at(i).at(j).get_colour());
				this->zone.setOutlineColor(sf::Color::Transparent);
				if (this->position.x == i && this->position.y == j) {
					this->zone.setOutlineColor(Palette::White);
				}
				this->window.draw(this->zone);
			}
		}
		return;
	}
}