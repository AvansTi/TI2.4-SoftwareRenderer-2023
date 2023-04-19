#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <iostream>
#ifdef _WIN32
#include <Windows.h>
#endif
#include "Vec2.h"
#include "Vec3.h"

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


void drawTriangle(char* imageData, const Vec2 corners[3])
{
	setPixel(imageData, corners[0].x, corners[0].y, Vec3(1, 0, 0));
	setPixel(imageData, corners[1].x, corners[1].y, Vec3(0, 1, 0));
	setPixel(imageData, corners[2].x, corners[2].y, Vec3(0, 0, 1));

}

int main()
{
	char* imageData = new char[width * height * 3];
	memset(imageData, 0, width * height * 3);

	setPixel(imageData, 10, 10, Vec3(1,0,0));

	Vec2 corners[3] = { Vec2(10,10), Vec2(200,200), Vec2(500,20) };

	drawTriangle(imageData, corners);


	stbi_write_png("out.png", width, height, 3, imageData, 0);


#ifdef _WIN32
	ShellExecute(0, 0, L"out.png", 0, 0, SW_SHOW);
#endif
}
