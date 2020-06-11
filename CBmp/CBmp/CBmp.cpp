#include "memory.h"
#include "math.h"
#include "stdint.h"
#include "stdlib.h"
#include "stdio.h"
#include <vector>
#include <stdint.h>//

#pragma pack(1) // For MSVC,disable struct Pack,or short will take 32bit mem as int32_t
typedef struct
{
	uint16_t bfType;
	uint32_t bfSize;
	uint16_t bfReserved1;
	uint16_t bfReserved2;
	uint32_t bfOffBits;
} ClBitMapFileHeader;

typedef struct
{
	uint32_t biSize;
	int32_t biWidth;
	int32_t biHeight;
	uint16_t biPlanes;
	uint16_t biBitCount;
	uint32_t biCompression;
	uint32_t biSizeImage;
	int32_t biXPelsPerMeter;
	int32_t biYPelsPerMeter;
	uint32_t biClrUsed;
	uint32_t biClrImportant;
} ClBitMapInfoHeader;

typedef struct
{
	uint8_t rgbBlue;
	uint8_t rgbGreen;
	uint8_t rgbRed;
	uint8_t rgbReserved;
} ClrgbMap;

class ClImgBMP
{
public:
	ClBitMapFileHeader bmpFileHeaderData;
	ClBitMapInfoHeader bmpInfoHeaderData;
	ClrgbMap colorMap[256];
	std::vector<uint8_t> imgData;

	inline bool LoadImage(const char* path);
	inline bool SaveImage(const char* path);
};
#pragma pack()// reset to default


bool ClImgBMP::LoadImage(const char* path)
{
	FILE* pFile;
	pFile = fopen(path, "rb");
	if (!pFile)
	{
		return 0;
	}
	fread(&bmpFileHeaderData, sizeof(ClBitMapFileHeader), 1, pFile);
	if (bmpFileHeaderData.bfType == 0x4D42) // Check is it an RGB file
	{
		// Get Channel num of a pixel
		int channels = 0;
		fread(&bmpInfoHeaderData, sizeof(ClBitMapInfoHeader), 1, pFile);
		if (bmpInfoHeaderData.biBitCount == 8)// grayscale format
		{

			channels = 1;
			fread(&colorMap, sizeof(ClrgbMap), 256, pFile);
		}
		else if (bmpInfoHeaderData.biBitCount == 24)// RGB format
		{
			channels = 3;
		}
		// Get offset of every scanline,length(scanline)=length(pixel)+offset
		int offset = 0;
		int linelength = bmpInfoHeaderData.biWidth * channels;
		offset = linelength % 4;
		if (offset > 0)
		{
			offset = 4 - offset;
		}
		// Read Pixel
		uint8_t pixVal;
		for (int i = 0; i < bmpInfoHeaderData.biHeight; i++)
		{
			for (int j = 0; j < linelength; j++)
			{
				fread(&pixVal, sizeof(uint8_t), 1, pFile);
				imgData.push_back(pixVal);
			}
			for (int k = 0; k < offset; k++)
			{
				fread(&pixVal, sizeof(uint8_t), 1, pFile);
			}
		}
	}
	else
	{
		return false;
	}
	fclose(pFile);
	return true;
}

bool ClImgBMP::SaveImage(const char* path)
{
	FILE* pFile;
	pFile = fopen(path, "wb");
	if (!pFile)
	{
		return 0;
	}
	// Processing
	fwrite(&bmpFileHeaderData, sizeof(ClBitMapFileHeader), 1, pFile);
	fwrite(&bmpInfoHeaderData, sizeof(ClBitMapInfoHeader), 1, pFile);
	// Get Channel num of a pixel
	int channels = 0;
	if (bmpInfoHeaderData.biBitCount == 8)
	{
		channels = 1;
		fwrite(&colorMap, sizeof(ClrgbMap), 256, pFile);
	}
	else if (bmpInfoHeaderData.biBitCount == 24)
	{
		channels = 3;
	}
	// Get offset of every scanline,length(scanline)=length(pixel)+offset
	int offset = 0;
	int linelength = bmpInfoHeaderData.biWidth * channels;
	offset = (channels * bmpInfoHeaderData.biWidth) % 4;
	if (offset > 0)
	{
		offset = 4 - offset;
	}
	// Write Pixel
	uint8_t pixVal;
	std::vector<uint8_t>::iterator iter = imgData.begin();
	//auto iter = imgData.begin();
	for (int i = 0; i < bmpInfoHeaderData.biHeight; i++)
	{
		for (int j = 0; j < linelength; j++)
		{
			pixVal = *iter;
			fwrite(&pixVal, sizeof(uint8_t), 1, pFile);
			iter += 1;
		}
		pixVal = 0;
		for (int k = 0; k < offset; k++)
		{
			fwrite(&pixVal, sizeof(uint8_t), 1, pFile);
		}
	}
	fclose(pFile);
	return true;
}






//directly set color
void setPixel(uint8_t bytes[], int w, int x, int y, int r, int g, int b)
{
	int ptr = ((x + (y * w)) * 3);

	bytes[ptr] = b;
	bytes[ptr + 1] = g;
	bytes[ptr + 2] = r;
}


int main()
{
	int i, id;


	char* path = "in.bmp";
	ClImgBMP bmp; // create a image var
	bmp.LoadImage(path); // load a bmpfile

	int width = bmp.bmpInfoHeaderData.biWidth;
	int height = bmp.bmpInfoHeaderData.biHeight;;
	int ch = bmp.bmpInfoHeaderData.biBitCount;
	printf("w=%d\t h=%d\t ch=%d\n", width, height, ch / 8);

	for (int w = 0; w < width; w++)
	{
		for (int h = 0; h < height / 2; h++)
		{
			int ptr = ((w + (h * width)) * 3);
			bmp.imgData[ptr] = 255 - bmp.imgData[ptr];
			bmp.imgData[ptr + 1] = 255 - bmp.imgData[ptr + 1];
			bmp.imgData[ptr + 2] = 255 - bmp.imgData[ptr + 2];
		}
	}
	bmp.SaveImage("out.bmp");
	system("pause");
	return 0;
}
