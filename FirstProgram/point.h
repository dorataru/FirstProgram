#pragma once
#include <algorithm>

struct point
{
public:
	int x;
	int y;

public:
	point()
	{}

	point(int x, int y) :
		x(x),
		y(y)
	{}

	point& operator=(const point& other)
	{
		this->x = other.x;
		this->y = other.y;
		return *this;
	}

	point operator+(const point& other) const
	{
		point result(this->x + other.x, this->y + other.y);
		return std::move(result);
	}

	point operator-(const point& other) const
	{
		point result(this->x - other.x, this->y - other.y);
		return std::move(result);
	}

	bool operator==(const point& other) const
	{
		return this->x == other.x && this->y == other.y;
	}

	bool operator!=(const point& other) const
	{
		return !operator==(other);
	}
};
