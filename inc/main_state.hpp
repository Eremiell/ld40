#pragma once
#ifndef MAIN_STATE_HPP
#define MAIN_STATE_HPP

#include "inc/state.hpp"
#include <vector>
#include <cstdint>
#include <optional>
#include <array>
#include <random>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Audio/Sound.hpp>
#include "inc/tile.hpp"
#include "inc/species_catalogue.hpp"
#include "inc/animal.hpp"

namespace ld40 {
	class MainState : public State {
		public:
			MainState(sf::RenderWindow &window, TextureManager &tm, SoundManager &sm, FontRenderer &fr);
			virtual void integrate(std::uint8_t controls) override;
			virtual void render() override;
			bool is_over() const;
		private:
			sf::Vector2<std::uint8_t> size;
			sf::RectangleShape zone;
			sf::RectangleShape selector;
			sf::Vector2<std::int8_t> position;
			sf::Vector2<std::int8_t> remodel_position;
			std::uint64_t turn;
			bool over;
			bool resize;
			std::int8_t phase;
			std::mt19937_64 mt;
			std::optional<sf::Vector2<std::int8_t>> selected;
			std::optional<Species> incoming;
			std::size_t to_gate;
			std::vector<std::vector<Tile>> board;
			std::vector<sf::Vector2<std::size_t>> gates;
			sf::Sprite sprite;
			SpeciesCatalogue catalogue;
			sf::Sound sound;
			void generate_gates();
			void draw_hud();
			void draw_remodel_screen();
			const std::array<std::string, 7> habitats{u8"plains", u8"desert", u8"water", u8"arctic", u8"taiga", u8"mountains", u8"tropical"};
	};
}

#endif