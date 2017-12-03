#include "inc/game.hpp"
#include <cstdint>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "inc/palette.hpp"
#include "inc/controls.hpp"

namespace ld40 {
	Game::Game() : window(sf::VideoMode(1000.0f, 1000.0f), "LD40", sf::Style::Titlebar | sf::Style::Close), tm(), state(new MainState(this->window, this->tm)) {}

	void Game::run() {
		bool running{true};
		std::uint8_t controls{0u};
		while (running) {
			controls &= 0u;
			sf::Event e;
			while (window.pollEvent(e)) {
				if (e.type == sf::Event::Closed) {
					running = false;
				}
				else if (e.type == sf::Event::KeyPressed) {
					switch (e.key.code) {
						case sf::Keyboard::Space:
							controls |= static_cast<std::uint8_t>(Controls::Select);
							break;
						case sf::Keyboard::Up:
							controls |= static_cast<std::uint8_t>(Controls::Up);
							break;
						case sf::Keyboard::Down:
							controls |= static_cast<std::uint8_t>(Controls::Down);
							break;
						case sf::Keyboard::Left:
							controls |= static_cast<std::uint8_t>(Controls::Left);
							break;
						case sf::Keyboard::Right:
							controls |= static_cast<std::uint8_t>(Controls::Right);
							break;
						default:
							break;
					}
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))) {
				running = false;
			}
			this->state->integrate(controls);
			window.clear(Palette::SlimeGreen);
			this->state->render();
			window.display();
		}

		return;
	}
}