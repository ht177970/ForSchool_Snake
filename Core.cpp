#include "Core.hpp"
#include "Game.hpp"
#include "Menu.hpp"

#define MENU_WITDH 600
#define MENU_HEIGHT 800

namespace rg {

	//global
	Mode Core::now_mode = Mode::MAIN_MENU;

	void Core::changeState(Mode new_mode) {
		Core::now_mode = new_mode;
	}

	Mode Core::getNowMode() {
		return Core::now_mode;
	}



	//Core
	Core::Core() : m_renderManager(window) {
		window.create(sf::VideoMode(MENU_WITDH, MENU_HEIGHT), "MainMenu", sf::Style::Close | sf::Style::Titlebar);
		window.setFramerateLimit(60);
		this->m_lastgame_score = 0;
		this->m_highest_score = 0;
	}

	void Core::Run() {
		Core::changeState(Mode::MAIN_MENU);
		display();
	}

	void Core::display() {
		while (window.isOpen()) {
			switch (Core::getNowMode()) {
			case Mode::MAIN_MENU: {
				MainMenu menu(window, m_renderManager);
				menu.initMenu();
				break;
			}
			case Mode::GAMING: {
				Core::changeState(Mode::NONE);
				Game g(window, m_renderManager, BaseData(m_outgame_size, m_ingame_width, m_ingame_height, m_snake_size), 0.001f);
				g.StartGame();
				m_lastgame_score = g.getScore();
				if (m_lastgame_score > m_highest_score)
					m_highest_score = m_lastgame_score;
				break;
			}
			case Mode::GAMEOVER:
				GameOverMenu gom(window, m_renderManager);
				gom.initMenu(this->m_lastgame_score, this->m_highest_score);
				break;
			}
		}
	}
}