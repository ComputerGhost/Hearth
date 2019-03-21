#pragma once

namespace Platform
{
	struct Position
	{
		int x;
		int y;

		Position() = default;
		Position(int x, int y);
	};

	struct Size
	{
		int width;
		int height;

		Size() = default;
		Size(int width, int height);
	};

	struct Rectangle
	{
		union {
			struct {
				int x;
				int y;
			};
			Position position;
		};
		union {
			struct {
				int width;
				int height;
			};
			Size size;
		};

		Rectangle() = default;
		Rectangle(Position position, Size size);
	};

	bool doesIntersect(Rectangle rectangle, Position position);
}