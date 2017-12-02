#pragma once
#ifndef CONTROLS_HPP
#define CONTROLS_HPP

#include <cstdint>

namespace ld40 {
	enum class Controls : std::uint8_t {
		Left = 1 << 0,
		Right = 1 << 1,
		Up = 1 << 2,
		Down = 1 << 3,
		Select = 1 << 4,
		Cancel = 1 << 5
	};
}

#endif