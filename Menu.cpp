#include "Menu.hpp"
#include "Core.hpp"

namespace rg {

	Menu::Menu(sf::RenderWindow& window, renderManager& render) {
		this->window = &window;
		this->m_renderManager = &render;
		m_text_index = -1;
	}

	void Menu::initMenu() {
		sf::String texts[] = { L"開始遊戲", L"遊戲設定", L"離開" };
		int w = 300, h = 300, next = 120;
		sf::Font font;
		font.loadFromFile("font.ttf");
		for (int i = 0; i < 3; i++)
			m_clickable_texts.push_back(new Text(texts[i], font, i, &m_text_index, w, h += next));
		for (Text* t : m_clickable_texts)
			m_renderManager->addGraphics(t);
		m_text_index = 0;

		m_renderManager->addGraphics(new Image(ImageBuilder("snake.png", 300, 200, 0.85f, 0.85f)));
		
		loop();
	}

	void Menu::loop() {
		sf::Event e;
		/*sf::Clock clock;
		float time_step = 0.1f;*/
		while (window->isOpen() && Core::getNowMode() == Mode::MAIN_MENU) {
			while(window->pollEvent(e))
				switch (e.type) {
				case sf::Event::Closed:
					window->close();
					return;
				case sf::Event::KeyPressed:
					switch (e.key.code) {
					case sf::Keyboard::Up:
						if (--m_text_index < 0)
							m_text_index = m_clickable_texts.size() - 1;
						break;
					case sf::Keyboard::Down:
						if (++m_text_index > m_clickable_texts.size() - 1)
							m_text_index = 0;
						break;
					case sf::Keyboard::Enter:
						EnterPressed();
						break;
					}
					break;
				}
			m_renderManager->Render();
		}
	}

	void Menu::EnterPressed() {
		switch (m_text_index) {
		case 0:
			Core::changeState(Mode::GAMING);
			break;
		}
	}

	Text::Text(sf::String text, sf::Font font, int id, int* text_index, float x, float y) {
		this->m_id = id;
		this->m_font = font;
		this->grap = sf::Text(text, m_font, 60);
		this->grap.setOrigin(grap.getLocalBounds().width / 2, grap.getLocalBounds().height / 2);
		this->grap.setPosition(x, y);
		/*switch (this->m_id) {
		case 0:
			this->grap.setPosition(200, 200);
			break;
		case 1:
			this->grap.setPosition(200, 250);
			break;
		}*/
		this->index = text_index;
	}

	int Text::getId() {
		return m_id;
	}

	void Text::draw(sf::RenderWindow& window) {
		updateText();
		window.draw(grap);
	}

	void Text::updateText() {
		grap.setFillColor((*this->index == m_id) ? sf::Color::Yellow : sf::Color::White);
	}

	Image::Image(ImageBuilder ib) {
		texture.loadFromFile(ib.p_location);
		sprite.setTexture(texture);
		sprite.setScale(sf::Vector2f(ib.zoom_x, ib.zoom_y));
		sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
		sprite.setPosition(ib.x, ib.y);
	}

	void Image::draw(sf::RenderWindow& window) {
		window.draw(sprite);
	}
}