#include "inc/state.hpp"

namespace ld40 {
	State::State(sf::RenderWindow &window, TextureManager &tm) : window(window), tm(tm) {}

	State::~State() {}
}