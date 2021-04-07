#ifndef SNAKE_RG_MENU_H_
#define SNAKE_RG_MENU_H_

#include "WindowRender.hpp"
#include <cstring>
#include <vector>
#include <SFML/System/String.hpp>

namespace rg {
	/*enum class Text_ID {
		None = -1,
		START_GAME = 0,
		SETTINGS = 1
	};*/

	class Text : public BaseDrawable {
	public:
		explicit Text(sf::String text, sf::Font font, int code, int* text_index, float x, float y);
		~Text() = default;
		int getId();
		void draw(sf::RenderWindow& window) override;
		void updateText();
	private:
		sf::Text grap;
		sf::Font m_font;
		int m_id;
		int* index;
	};

	class Image : public BaseDrawable {
	public:
		explicit Image(std::string p_location, float x, float y, float zoom_x, float zoom_y);
		void draw(sf::RenderWindow& window) override;
	private:
		sf::Texture texture;
		sf::Sprite sprite;
	};

	class Menu {
	public:
		explicit Menu(sf::RenderWindow& window, renderManager& render);
		~Menu() = default;
		void initMenu();
		void loop();
		void EnterPressed();
	private:
		int m_text_index;
		sf::RenderWindow* window;
		renderManager* m_renderManager;
		std::vector<Text*> m_clickable_texts;
	};
}

#endif
