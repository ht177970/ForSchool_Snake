#ifndef SNAKE_RG_BASE_H_
#define SNAKE_RG_BASE_H_

#include <SFML/Graphics.hpp>

namespace rg {
	class BaseDrawable {
	public:
		virtual ~BaseDrawable() = default;
		//virtual void Update() = 0;
		virtual void draw(sf::RenderWindow& window) = 0;
	};
	struct Pos {
		int x, y;
		bool operator==(Pos other) {
			return (x == other.x && y == other.y);
		}
	};
}

#endif