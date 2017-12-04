#include "inc/state.hpp"

namespace ld40 {
	State::State(sf::RenderWindow &window, TextureManager &tm, SoundManager &sm, FontRenderer &fr) : window(window), tm(tm), sm(sm), fr(fr) {}

	State::~State() {}
}