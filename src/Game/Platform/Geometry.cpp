#include "Geometry.hpp"

namespace Platform
{
	Position::Position(int x, int y) :
		x(x),
		y(y)
	{}

	Size::Size(int width, int height) :
		width(width),
		height(height)
	{}

	Rectangle::Rectangle(Position position, Size size) :
		position(position),
		size(size)
	{}

	bool doesIntersect(Rectangle rectangle, Position position)
	{
		if (position.x < rectangle.x)
			return false;
		if (position.y < rectangle.y)
			return false;
		if (position.x > rectangle.x + rectangle.width)
			return false;
		if (position.y > rectangle.y + rectangle.height)
			return false;
		return true;
	}
}