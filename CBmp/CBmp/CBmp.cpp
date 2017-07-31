#include "memory.h"
#include "math.h"
#include "stdint.h"
#include "stdlib.h"
#include "stdio.h"
//#include "bmp.h"
//bmp.h--
/* \file bmp.h
*  BMP image format
*
*  Author:	rjianwang
*	Date:	2016-09-06
*  Email:  rjianwang@foxmail.com
*/

#pragma once

#include <string>

typedef long			LONG;
typedef unsigned long	DWORD;
typedef int				BOOL;
typedef unsigned char   BYTE;
typedef unsigned short	WORD;
typedef BYTE			*LPBYTE;
typedef DWORD			*LPDWORD;


#pragma pack(1)
typedef struct tagRGBQUAD
{
	BYTE	rgbBlue;
	BYTE	rgbGreen;
	BYTE	rgbRed;
	BYTE	rgbReserved;
}RGBQUAD;

typedef struct  tagBITMAPFILEHEADER
{
	WORD	bfType;				// 文件类型，必须是0x424D，即字符“BM”   
	DWORD	bfSize;				// 文件大小   
	WORD	bfReserved1;		// 保留字   
	WORD	bfReserved2;		// 保留字   
	DWORD	bfOffBits;			// 从文件头到实际位图数据的偏移字节数   
}BITMAPFILEHEADER;				// 位图文件头定义 

typedef struct tagBITMAPINFOHEADER
{
	DWORD	biSize;				// 信息头大小   
	LONG	biWidth;			// 图像宽度   
	LONG	biHeight;			// 图像高度   
	WORD	biPlanes;			// 位平面数，必须为1   
	WORD	biBitCount;			// 每像素位数: 1, 2, 4, 8, 16, 24, 32
	DWORD	biCompression;		// 压缩类型   
	DWORD	biSizeImage;		// 压缩图像大小字节数   
	LONG	biXPelsPerMeter;	// 水平分辨率   
	LONG	biYPelsPerMeter;	// 垂直分辨率   
	DWORD	biClrUsed;			// 位图实际用到的色彩数   
	DWORD	biClrImportant;		// 本位图中重要的色彩数   
}BITMAPINFOHEADER;				// 位图信息头定义   
#pragma pack()

								// class BMP
								//
								// BMP is an image file format that stores bitmap digital images and retains 
								// information for each pixel of the image. The BMP format stores color data 
								// for each pixel in the image without any compression. For example, a 10x10 
								// pixel BMP image will include color data for 100 pixels. This method of 
								// storing image information allows for crisp, high-quality graphics, but 
								// also produces large file sizes. 
class BMP
{
public:
	BMP();
	BMP(const std::string &location);

	~BMP();

public:
	BYTE*	load(const std::string &location);
	void	save(const std::string &location);
private:
	void	swap(BYTE **src, DWORD width, DWORD height, WORD channel);

public:
	LONG	width();
	LONG	height();
	BYTE	depth();
	BYTE*	data();
	WORD	_channels();

public:
	DWORD	rows;
	DWORD	cols;
	WORD	channels;

private:
	BITMAPFILEHEADER	*head;
	BITMAPINFOHEADER	*info;
	RGBQUAD				*palette;   // color table
	BYTE				*pixels;	// iamge pixel data  

}; /* end for class BMP */

//--bmp.h

//bmp.cpp--
/* \file bmp.cpp
*  Bitmap file format
*
*  Author: rjianwang
*	Date:	2016-09-09
*	Email:	rjianwang@foxmail.com
*/

#include <iostream>
#include <fstream>

BMP::BMP()
{
	head = NULL;
	info = NULL;
	palette = NULL;
	pixels = NULL;

	rows = -1;
	cols = -1;
}

BMP::BMP(const std::string &location)
{
	head = NULL;
	info = NULL;
	palette = NULL;
	pixels = NULL;

	rows = -1;
	cols = -1;

	this->load(location);
}

BMP::~BMP()
{
	if (pixels != NULL)
		delete[] pixels;
	if (palette != NULL)
		delete[] palette;
	if (info != NULL)
		delete info;
	if (head != NULL)
		delete head;
}

BYTE* BMP::load(const std::string &location)
{
	// The file... We open it with it's constructor
	std::ifstream file(location.c_str(), std::ios::binary);
	if (!file)
	{
		std::cout << "Failed to open bitmap file.\n";
		return NULL;
	}

	// Allocate byte memory that will hold the two headers
	head = new BITMAPFILEHEADER;
	info = new BITMAPINFOHEADER;

	file.read((char*)head, sizeof(BITMAPFILEHEADER));
	file.read((char*)info, sizeof(BITMAPINFOHEADER));

	// Check if the file is an actual BMP file
	if (head->bfType != 0x4D42)
	{
		std::cout << "File \"" << location << "\" isn't a bitmap file\n";
		return pixels;
	}

	// Set values for rows, cols and channels 
	this->rows = (DWORD)info->biHeight;
	this->cols = (DWORD)info->biWidth;
	this->channels = this->_channels();

	// Check if the file is a true color BMP file
	// If not, read in color table
	if (info->biBitCount == 8)
	{
		palette = new RGBQUAD[256];
		file.read((char*)palette, 256 * sizeof(RGBQUAD));
	}

	// First allocate pixel memory
	unsigned long size = info->biWidth * info->biHeight * this->_channels();
	pixels = new BYTE[size];

	// Go to where image data starts, then read in image data
	file.seekg(head->bfOffBits, std::ios::beg);
	file.read((char*)pixels, size);

	// Image is loaded, however it's not in the right format.
	// .bmp files store image data in the BGR format, and we have to convert it to RGB.
	this->swap(&pixels, cols, rows, channels);

	return pixels;
}

void BMP::save(const std::string &location)
{
	std::ofstream file(location.c_str());
	if (!file)
	{
		std::cout << "Failed to open or create bitmap file." << std::endl;
		return;
	}

	if (head == NULL || info == NULL || pixels == NULL)
	{
		std::cout << "Failed to save bitmap file." << std::endl;
		return;
	}

	file.write((char*)head, sizeof(BITMAPFILEHEADER));
	file.write((char*)info, sizeof(BITMAPINFOHEADER));

	if (info->biBitCount < 24)
		file.write((char*)palette, sizeof(RGBQUAD) * 256);

	this->swap(&pixels, cols, rows, channels);
	file.write((char*)pixels, this->rows * this->cols * this->channels);
	this->swap(&pixels, cols, rows, channels);
}

void BMP::swap(BYTE **src, unsigned long width, unsigned long height, WORD channel)
{
	BYTE temp;
	for (unsigned long w = 0; w < width * channel; w++)
	{
		for (unsigned long i = 0, j = height - 1; i <= j; i++, j--)
		{
			temp = (*src)[i * width * channel + w];
			(*src)[i * width * channel + w] = (*src)[j * width * channel + w];
			(*src)[j * width * channel + w] = temp;
		}
	}
}

LONG BMP::width()
{
	//assert(info != NULL);

	return info->biWidth;
}

LONG BMP::height()
{
	//assert(info != NULL);

	return info->biHeight;
}

BYTE BMP::depth()
{
	//assert(info != NULL);

	if (info->biBitCount <= 8)
		return info->biBitCount;
	else
		return 8;
}

BYTE* BMP::data()
{
	return pixels;
}

WORD BMP::_channels()
{
	//assert(info != NULL);

	switch (info->biBitCount)
	{
	case 1:
	case 2:
	case 4:
	case 8:
		return 1;
	case 16:
		return 2;
	case 24:
		return 3;
	case 32:
		return 4;
	}
}

//--bmp.cpp



//read file--
#define FILE_g "R_g_hokan.txt"
#define FILE_b "R_b_hokan.txt"
typedef struct color
{
	int id;
	float value;
}color;

color allcolorsg[300];
int allcolorsgcount = 0;
color allcolorsb[300];
int allcolorsbcount = 0;


color getcolorfromline(char *line)
{
	char *part;
	int index = 0;
	color b;
	part = strtok(line, " \t\n");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			b.id = atoi(part);
			break;
		case 2:
			b.value = atof(part);
			break;
		default:
			break;
		}
		part = strtok(NULL, " \t\n");
	}
	return b;
}

void readallcolorsg()
{
	char line[200];
	FILE *fp = fopen(FILE_g, "r");
	if (fp == NULL)
	{
		printf("\n error open g!");
	}
	else
	{
		allcolorsgcount = 0;

		while (fgets(line, 1024, fp) != NULL)
		{
			if (strlen(line) < 6)
				continue;
			allcolorsg[allcolorsgcount++] = getcolorfromline(line);
		}
	}
}

void readallcolorsb()
{
	char line[200];
	FILE *fp = fopen(FILE_b, "r");
	if (fp == NULL)
	{
		printf("\n error open b!");
	}
	else
	{
		allcolorsbcount = 0;

		while (fgets(line, 1024, fp) != NULL)
		{
			if (strlen(line) < 6)
				continue;
			allcolorsb[allcolorsbcount++] = getcolorfromline(line);
		}
	}
}

float getcolorgidexbyno(int  id)
{
	int i;
	for (i = 0; i < allcolorsgcount; i++)
	{
		if (allcolorsg[i].id == id)
			return allcolorsg[i].value;
	}
	return 0;
}

float getcolorbidexbyno(int  id)
{
	int i;
	for (i = 0; i < allcolorsbcount; i++)
	{
		if (allcolorsb[i].id == id)
			return allcolorsb[i].value;
	}
	return 0;
}
//--read file


//directly set color
void setPixel(BYTE bytes[], int w, int x, int y, int r, int g, int b)
{
	int ptr = ((x + (y*w)) * 3);

	bytes[ptr] = b;
	bytes[ptr + 1] = g;
	bytes[ptr + 2] = r;
}


int main()
{
	int i, id;
	readallcolorsg();
	readallcolorsb();

	BMP bmp;

	bmp.load("t.bmp");//input, width must > height
	int width = bmp.width();
	int height = bmp.height();
	int ch = bmp.channels;
	printf("w=%d\t h=%d\t ch=%d\n", width, height, ch);

	BYTE* bytes = bmp.data();


	for (int w = 0; w < width; w++)
	{
		for (int h = 0; h < height; h++)
		{
			int ptr = ((w + (h*width)) * 3);

			//bytes[ptr] = b;//red
			bytes[ptr + 1] = getcolorgidexbyno(bytes[ptr + 1]);//green
			bytes[ptr + 2] = getcolorbidexbyno(bytes[ptr + 2]);//blue
		}
	}

	bmp.save("test.bmp");
	system("pause");
	return 0;
}
