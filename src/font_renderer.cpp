#include "inc/font_renderer.hpp"

namespace ld40 {
	FontRenderer::FontRenderer(sf::RenderWindow &window, TextureManager &tm) : window(window), tm(tm) {
		this->tm.load_sheet(u8"font.json");
		this->tm.load_sheet(u8"hud_icons.json");
		this->letter.setTexture(*this->tm.get_texture(u8"a").first);
		this->icon.setTexture(*this->tm.get_texture(u8"tick").first);
	}

	void FontRenderer::render(std::string text, sf::Vector2<float> position) {
		static const float letter_width{16.0f};
		this->window.setView(this->window.getDefaultView());
		for (auto &chr : text) {
			if (chr != ' ') {
				this->letter.setTextureRect(this->tm.get_texture(std::string{chr}).second);
				this->letter.setPosition(position);
				this->window.draw(this->letter);
			}
			position.x += letter_width;
		}
		return;
	}

	void FontRenderer::render_box(std::string text, sf::Vector2<float> position) {
		static const float letter_width{16.0f};
		this->window.setView(this->window.getDefaultView());
		this->icon.setTextureRect(this->tm.get_texture(u8"msgbox_NW").second);
		this->icon.setPosition(position.x - letter_width, position.y - letter_width);
		this->window.draw(this->icon);
		this->icon.setTextureRect(this->tm.get_texture(u8"msgbox_W").second);
		this->icon.setPosition(position.x - letter_width, position.y);
		this->window.draw(this->icon);
		this->icon.setTextureRect(this->tm.get_texture(u8"msgbox_SW").second);
		this->icon.setPosition(position.x - letter_width, position.y + letter_width);
		this->window.draw(this->icon);
		for (std::size_t i = 0; i < text.size(); ++i) {
			this->icon.setTextureRect(this->tm.get_texture(u8"msgbox_N").second);
			this->icon.setPosition(position.x + i * letter_width, position.y - letter_width);
			this->window.draw(this->icon);
			this->icon.setTextureRect(this->tm.get_texture(u8"msgbox_centre").second);
			this->icon.setPosition(position.x + i * letter_width, position.y);
			this->window.draw(this->icon);
			this->icon.setTextureRect(this->tm.get_texture(u8"msgbox_S").second);
			this->icon.setPosition(position.x + i * letter_width, position.y + letter_width);
			this->window.draw(this->icon);
		}
		this->icon.setTextureRect(this->tm.get_texture(u8"msgbox_NE").second);
		this->icon.setPosition(position.x + text.size() * letter_width, position.y - letter_width);
		this->window.draw(this->icon);
		this->icon.setTextureRect(this->tm.get_texture(u8"msgbox_E").second);
		this->icon.setPosition(position.x + text.size() * letter_width, position.y);
		this->window.draw(this->icon);
		this->icon.setTextureRect(this->tm.get_texture(u8"msgbox_SE").second);
		this->icon.setPosition(position.x + text.size() * letter_width, position.y + letter_width);
		this->window.draw(this->icon);
		this->render(text, position);
		return;
	}
}