#pragma once

#include "Vec3.h"
#include <vector>
#include <string>

class ObjModel
{
public:
	class Face
	{
	public:
		int position[3];
		int normal[3];
	};
	std::vector<Vec3> positions;
	std::vector<Vec3> normals;
	std::vector<Face> faces;

	ObjModel(const std::string &fileName);
};

