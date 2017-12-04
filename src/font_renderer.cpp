#include "inc/font_renderer.hpp"

namespace ld40 {
	FontRenderer::FontRenderer(sf::RenderWindow &window, TextureManager &tm) : window(window), tm(tm) {
		this->tm.load_sheet(u8"font.json");
		this->letter.setTexture(*this->tm.get_texture("a").first);
	}

	void FontRenderer::render(std::string text, sf::Vector2<float> position) {
		static const float letter_width{16.0f};
		this->window.setView(this->window.getDefaultView());
		for (auto &chr : text) {
			this->letter.setTextureRect(this->tm.get_texture(std::string{chr}).second);
			this->letter.setPosition(position);
			this->window.draw(this->letter);
			position.x += letter_width;
		}
		return;
	}
}