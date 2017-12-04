#include "inc/state.hpp"

namespace ld40 {
	State::State(sf::RenderWindow &window, TextureManager &tm, SoundManager &sm) : window(window), tm(tm), sm(sm) {}

	State::~State() {}
}