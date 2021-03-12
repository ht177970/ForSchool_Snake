#ifndef SNAKE_RG_SNAKE_H_
#define SNAKE_RG_SNAKE_H_

#include "Base.h"
#include <SFML/Graphics.hpp>

namespace rg {

	const sf::Color Head_Color = sf::Color::Cyan;
	const sf::Color Body_Color = sf::Color::White;

	class Unit : BaseDrawable{
	public:
		explicit Unit(Unit* previous_unit, int X, int Y, int size);
		~Unit();
		void draw(sf::RenderWindow& window) override;
		virtual void setPos(Pos pos);
		Unit* prev() { return u1; }
		Pos getPos() { return { x,y }; }
	protected:
		int x, y;
		Unit* u1;
		explicit Unit(Unit* previous_unit, int X, int Y);
	private:
		sf::CircleShape grap;
	};

	class HeadUnit : public Unit {
	public:
		explicit HeadUnit(Unit* previous_unit, int X, int Y, int size);
		void draw(sf::RenderWindow& window) override;
		void setPos(Pos pos) override;
	private:
		sf::RectangleShape m_grap;
	};

	class Snake : BaseDrawable{
	public:
		enum class Ways { UP = 1, DOWN = -1, R = 2, L = -2, Non = 0};//R = Right, L = Left
		explicit Snake(int* outgame_size, int* ingame_width, int* ingame_height, int SIZE);
		~Snake();
		bool move();
		int getHeadX() { return x; };
		int getHeadY() { return y; };
		void setDirection(Ways way);
		void draw(sf::RenderWindow& window) override;
		void add();//debuging
		void gainFood();
		bool posInBody(int x, int y) { return posInBody({ x,y }); }
		bool posInBody(Pos position);
		bool wait_start(sf::RenderWindow& window);
	private:
		int x, y;
		int size;
		int m_tail_x, m_tail_y;
		int* m_outgame_size, * m_ingame_width, * m_ingame_height;
		Ways now_direction;
		Unit* head;
		Unit* tail;
		int getTailX_prev() { return m_tail_x; }
		int getTailY_prev() { return m_tail_y; }
		bool illegalPos();
	};
}

#endif
