#include "ObjModel.h"
#include <fstream>
#include <iostream>
#include <sstream>

ObjModel::ObjModel(const std::string &fileName)
{
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		std::cout << "File " << fileName << " could not be opened" << std::endl;
		return;
	}
	std::string line;
	while (!file.eof())
	{
		std::getline(file, line);

		std::stringstream lineStream(line);

		std::string first;
		lineStream >> first;

		if (first == "v")
		{
			Vec3 position(0, 0, 0);
			lineStream >> position.x;
			lineStream >> position.y;
			lineStream >> position.z;
			positions.push_back(position);
		}
		if (first == "vn")
		{
			Vec3 normal(0, 0, 0);
			lineStream >> normal.x;
			lineStream >> normal.y;
			lineStream >> normal.z;
			normals.push_back(normal);
		}
		if (first == "f")
		{
			Face f;
			char junk;
			for (int i = 0; i < 3; i++)
			{
				lineStream >> f.position[i];
				lineStream >> junk;
				if (lineStream.peek() != '/')
					lineStream >> f.normal[i];
				lineStream >> junk;
				lineStream >> f.normal[i];

				//obj model is 1-indexed
				f.position[i]--;
				f.normal[i]--;
			}
			faces.push_back(f);
		}

	}

}
