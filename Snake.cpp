#include "Snake.hpp"
#include <iostream>

namespace rg {

#pragma region Unit functions

	Unit::Unit(Unit* previous_unit, int X, int Y, int size) : Unit(previous_unit, X, Y) {
		grap.setRadius(size / 2);
		grap.setFillColor(sf::Color::Blue);
	}

	Unit::Unit(Unit* previous_unit, int X, int Y) {
		u1 = previous_unit;
		this->setPos({ X, Y });
	}

	void Unit::draw(sf::RenderWindow& window) {
		window.draw(grap);
	}

	void Unit::setPos(Pos pos) {
		x = pos.x;
		y = pos.y;
		grap.setPosition(x, y);
	}

	HeadUnit::HeadUnit(Unit* previous_unit, int X, int Y, int size) : Unit(previous_unit, X, Y) {
		u1 = previous_unit;
		this->setPos({ X, Y });
		m_grap.setSize(sf::Vector2f(size, size));
		m_grap.setFillColor(sf::Color::Cyan);
	}

	void HeadUnit::draw(sf::RenderWindow& window) {
		window.draw(m_grap);
	}

	void HeadUnit::setPos(Pos pos) {
		x = pos.x;
		y = pos.y;
		m_grap.setPosition(x, y);
	}

	/*Unit* Unit::next() {
		return u2;
	}*/
#pragma endregion

	Snake::Snake(int* outgame_size, int* ingame_width, int* ingame_height, int SIZE) {
		m_outgame_size = outgame_size;
		m_ingame_width = ingame_width;
		m_ingame_height = ingame_height;
		x = *m_ingame_width / 2;
		y = *m_ingame_height / 2;
		m_tail_x = x;
		m_tail_y = y;
		size = SIZE;
		head = new HeadUnit(nullptr, x, y, size);//head's prev is nullptr
		tail = head;
		now_direction = Ways::Non;
	}

	void Snake::setDirection(Ways new_direction) {
		if(static_cast<int>(new_direction) + static_cast<int>(now_direction))
			now_direction = new_direction;
	}

	bool Snake::move() {
		switch (now_direction) {
		case Ways::UP:
			y -= size;
			break;
		case Ways::DOWN:
			y += size;
			break;
		case Ways::L:
			x -= size;
			break;
		case Ways::R:
			x += size;
			break;
		}
		if (illegalPos())//edit later
			return false;
		Unit* moving = tail;
		Pos last_position = tail->getPos();
		m_tail_x = last_position.x;
		m_tail_y = last_position.y;
		while (moving->prev()) {
			moving->setPos(moving->prev()->getPos());
			moving = moving->prev();
		}
		head->setPos({ x, y });
		if (this->posInBody({ x,y }))
			return false;
		return true;
	}

	bool Snake::illegalPos() {
		return (x < *m_outgame_size || y < *m_outgame_size || x > *m_outgame_size + *m_ingame_width - size || y > *m_outgame_size + *m_ingame_height - size);
	}

	bool Snake::posInBody(Pos position) {
		Unit* testing = tail;
		while (testing->prev()) {
			if (testing->getPos() == position)
				return true;
			testing = testing->prev();
		}
		return false;
	}

	bool Snake::wait_start(sf::RenderWindow& window) {
		if (window.isOpen()) {
			this->draw(window);
			window.display();
		}
		else
			return false;
		sf::Event e;
		while (window.isOpen()) {
			while (window.pollEvent(e))
				if (e.type == sf::Event::Closed) {
					window.close();
					return false;
				}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				this->setDirection(Snake::Ways::UP);
				return true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				this->setDirection(Snake::Ways::DOWN);
				return true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				this->setDirection(Snake::Ways::R);
				return true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				this->setDirection(Snake::Ways::L);
				return true;
			}
		}
		return false;
	}

	void Snake::draw(sf::RenderWindow& window) {
		Unit* drawing = tail;
		while (drawing->prev()) {
			drawing->draw(window);
			drawing = drawing->prev();
		}
		head->draw(window);
	}

	void Snake::add() {//Debug
		tail = new Unit(tail, tail->getPos().x, tail->getPos().y - size, size);
	}

	void Snake::gainFood() {
		tail = new Unit(tail, this->getTailX_prev(), this->getTailY_prev(), size);
	}

	Unit::~Unit() {
		
	}

	Snake::~Snake() {
		
	}
}