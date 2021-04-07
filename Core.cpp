#include "Core.hpp"
#include "Game.hpp"
#include "Menu.hpp"

#define MENU_WITDH 600
#define MENU_HEIGHT 800

namespace rg {

	Mode Core::now_mode = Mode::MAIN_MENU;

	void Core::changeState(Mode new_mode) {
		Core::now_mode = new_mode;
	}

	Mode Core::getNowMode() {
		return Core::now_mode;
	}

	Core::Core() : m_renderManager(window) {
		window.create(sf::VideoMode(MENU_WITDH, MENU_HEIGHT), "MainMenu", sf::Style::Close | sf::Style::Titlebar);
	}

	void Core::Start() {
		Core::changeState(Mode::MAIN_MENU);
		display();
	}

	void Core::display() {
		while (window.isOpen()) {
			switch (Core::getNowMode()) {
			case Mode::MAIN_MENU: {
				Menu menu(window, m_renderManager);
				menu.initMenu();
				break;
			}
			case Mode::GAMING:
				Game g(window, m_renderManager, BaseData(m_outgame_size, m_ingame_width, m_ingame_height, m_snake_size), 0.001f);
				g.StartGame();
				return;
			}
		}
	}
}