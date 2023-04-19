#pragma once
class Vec2
{
public:
	union
	{
		struct
		{
			float x;
			float y;
		};
		float data[2];
	};

	Vec2(float x, float y) : x(x), y(y)
	{

	}

	Vec2 operator *(float o) const
	{
		return Vec2(x * o, y * o);
	}

	Vec2 operator *(const Vec2& other)
	{
		return Vec2(x * other.x, y * other.y);
	}
	Vec2 operator +(const Vec2& other)
	{
		return Vec2(x + other.x, y + other.y);
	}
};

