#include "inc/game.hpp"
#include <cstdint>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Clock.hpp>
#include "inc/palette.hpp"

namespace ld40 {
	Game::Game() : window(sf::VideoMode(1000.0f, 1000.0f), "LD40", sf::Style::Titlebar | sf::Style::Close), state(new MainState(this->window)) {}

	void Game::run() {
		bool running{true};
		const float dt = 1.0f / 60.0f;
		float accumulator{0.0f};
		sf::Clock stopwatch;
		while (running) {
			sf::Event e;
			while (window.pollEvent(e)) {
				if (e.type == sf::Event::Closed) {
					running = false;
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))) {
				running = false;
			}
			accumulator += stopwatch.restart().asSeconds();
			while (accumulator > dt) {
				//integrate
				accumulator -= dt;
			}
			window.clear(palette::SlimeGreen);
			this->state->render();
			window.display();
		}

		return;
	}
}