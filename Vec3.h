#pragma once
class Vec3
{
public:
	union
	{
		struct
		{
			float x;
			float y;
			float z;
		};
		struct
		{
			float r;
			float g;
			float b;
		};
		float data[3];
	};

	Vec3(float x, float y, float z) : x(x), y(y), z(z)
	{
	}

	//NOT cross product
	Vec3 operator * (const Vec3& other)
	{
		return Vec3(x * other.x,
					y * other.y,
					z * other.z);
	}

	//cross product
	Vec3 cross(const Vec3& other)
	{
		return Vec3(y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x);
	}

	Vec3 operator * (float v) const	
	{
		return Vec3(x * v, y * v, z * v);
	}
	Vec3 operator + (const Vec3 &o) const
	{
		return Vec3(x + o.x, y + o.y, z + o.z);
	}
};


