#include "inc/main_state.hpp"
#include <cstdint>

namespace ld40 {
	MainState::MainState(sf::RenderWindow &window) : State(window), zone(sf::Vector2<float>(100.0f, 100.0f)) {
		this->board.resize(5);
		for (std::size_t i = 0; i < 5; ++i) {
			this->board.at(i).resize(5);
		}
		this->zone.setOrigin(50.0f, 50.0f);
	}

	void MainState::integrate() {
		return;
	}

	void MainState::render() {
		for (std::int8_t i = 0; i < 5; ++i) {
			for (std::int8_t j = 0; j < 5; ++j) {
				this->zone.setPosition(500.0f + (i - 2) * 110.0f, 500.0f + (j - 2) * 110.0f);
				this->zone.setFillColor(this->board.at(i).at(j).get_colour());
				this->window.draw(this->zone);
			}
		}
		return;
	}
}