#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <iostream>
#ifdef _WIN32
#include <Windows.h>
#endif
#include "Vec2.h"
#include "Vec3.h"
#include "ObjModel.h"

const int width = 512;
const int height = 512;


void setPixel(char* imageData, int x, int y, const Vec3 &color)
{
	if (x < 0 || x >= width || y < 0 || y >= height)
		return;

	imageData[3*(x + y * width)+0] = (int)(255 * color.r);
	imageData[3*(x + y * width)+1] = (int)(255 * color.g);
	imageData[3*(x + y * width)+2] = (int)(255 * color.b);
}


Vec3 baryCentric(const Vec2& p, const Vec3 corners[3])
{
	Vec3 X(corners[2].x - corners[0].x, corners[1].x - corners[0].x, corners[0].x - p.x);
	Vec3 Y(corners[2].y - corners[0].y, corners[1].y - corners[0].y, corners[0].y - p.y);
	Vec3 U = X.cross(Y);
	return Vec3(1 - (U.x + U.y) / U.z, U.y / U.z, U.x / U.z);
}


void drawTriangle(float* zBuffer, char* imageData, const Vec3 corners[3], const Vec3 colors[3])
{
	Vec2 bbmin(	min(min(corners[0].x, corners[1].x), corners[2].x),
				min(min(corners[0].y, corners[1].y), corners[2].y));
	Vec2 bbmax(	max(max(corners[0].x, corners[1].x), corners[2].x),
				max(max(corners[0].y, corners[1].y), corners[2].y));

	if (bbmin.x < 0)
		bbmin.x = 0;
	if (bbmax.x >= width)
		bbmax.x = width - 1;
	if (bbmin.y < 0)
		bbmin.y = 0;
	if (bbmax.y >= height)
		bbmax.y = height - 1;


	for (int x = bbmin.x; x < bbmax.x; x++)
	{
		for (int y = bbmin.y; y < bbmax.y; y++)
		{
			auto barry = baryCentric(Vec2(x, y), corners);
			if (barry.x < 0 || barry.y < 0 || barry.z < 0 || barry.x > 1 || barry.y > 1 || barry.z > 1)
				continue;
			float z = corners[0].z * barry.data[0] + corners[1].z * barry.data[1] + corners[2].z * barry.data[2];

			if (z < zBuffer[x + width * y])
				continue;

			zBuffer[x + width * y] = z;

			setPixel(imageData, x, y, colors[0] * barry.data[0] + colors[1] * barry.data[1] + colors[2] * barry.data[2]);
		}
	}

}

int main()
{
	ObjModel model("benchy.obj");

	char* imageData = new char[width * height * 3];
	float* zBuffer = new float[width * height];
	memset(imageData, 0, width * height * 3);
	for (int i = 0; i < width * height; i++)
		zBuffer[i] = -9999999;

	setPixel(imageData, 10, 10, Vec3(1,0,0));

	Vec3 corners[3] = { Vec3(10,10,0), Vec3(200,500,0), Vec3(500,20,0) };
	Vec3 colors[3] = { Vec3(1,0,0), Vec3(0,1,0), Vec3(0,0,1) };


	for (const auto& face : model.faces)
	{
		corners[0] = model.positions[face.position[0]];
		corners[1] = model.positions[face.position[1]];
		corners[2] = model.positions[face.position[2]];

		corners[0] = corners[0] * Vec3(width / 2, height / 2,1) + Vec3(width / 2, height / 2,0);
		corners[1] = corners[1] * Vec3(width / 2, height / 2,1) + Vec3(width / 2, height / 2,0);
		corners[2] = corners[2] * Vec3(width / 2, height / 2,1) + Vec3(width / 2, height / 2,0);

		drawTriangle(zBuffer, imageData, corners, colors);

	}

	stbi_flip_vertically_on_write(true);
	stbi_write_png("out.png", width, height, 3, imageData, 0);


#ifdef _WIN32
	ShellExecute(0, 0, L"out.png", 0, 0, SW_SHOW);
#endif
}
