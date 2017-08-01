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

//read file--

typedef struct color
{
	int id;
	float value;
}color;

typedef struct replacecolor
{
	char filename[20];
	color colors[300];
	int count;
}replacecolor;

replacecolor replacecolor_R_g;
replacecolor replacecolor_R_b;
replacecolor replacecolor_G_r;
replacecolor replacecolor_G_b;
replacecolor replacecolor_B_r;
replacecolor replacecolor_B_g;


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

void readallcolors(char *fn, color cols[], int *cnt)
{
	char line[200];
	FILE *fp = fopen(fn, "r");
	if (fp == NULL)
	{
		printf("\n error open %s!", fn);
	}
	else
	{
		*cnt = 0;
		while (fgets(line, 1024, fp) != NULL)
		{
			if (strlen(line) < 6)
				continue;
			cols[(*cnt)++] = getcolorfromline(line);
		}
		fclose(fp);
	}
}

float chcol(int  id, color cols[], int *cnt)
{
	int i;
	for (i = 0; i < *cnt; i++)
	{
		if (cols[i].id == id)
			return cols[i].value;
	}
	return 0;
}
//--read file


//directly set color
void setPixel(uint8_t bytes[], int w, int x, int y, int r, int g, int b)
{
	int ptr = ((x + (y*w)) * 3);

	bytes[ptr] = b;
	bytes[ptr + 1] = g;
	bytes[ptr + 2] = r;
}


int main()
{
	int i, id;
	strcpy(replacecolor_R_g.filename, "R_g_hokan.txt");
	strcpy(replacecolor_R_b.filename, "R_b_hokan.txt");
	strcpy(replacecolor_G_r.filename, "G_r_hokan.txt");
	strcpy(replacecolor_G_b.filename, "G_b_hokan.txt");
	strcpy(replacecolor_B_r.filename, "B_r_hokan.txt");
	strcpy(replacecolor_B_g.filename, "B_g_hokan.txt");
	//replacecolor_R_g.count = 0;
	//replacecolor_R_b.count = 0;
	//replacecolor_G_r.count = 0;
	//replacecolor_G_b.count = 0;
	//replacecolor_B_r.count = 0;
	//replacecolor_B_g.count = 0;
	//memset(replacecolor_R_g.colors, 0, 300);
	//memset(replacecolor_R_b.colors, 0, 300);
	readallcolors(replacecolor_R_b.filename, replacecolor_R_b.colors, &replacecolor_R_b.count);
	readallcolors(replacecolor_R_g.filename, replacecolor_R_g.colors, &replacecolor_R_g.count);
	readallcolors(replacecolor_G_r.filename, replacecolor_G_r.colors, &replacecolor_G_r.count);
	readallcolors(replacecolor_G_b.filename, replacecolor_G_b.colors, &replacecolor_G_b.count);
	readallcolors(replacecolor_B_r.filename, replacecolor_B_r.colors, &replacecolor_B_r.count);
	readallcolors(replacecolor_B_g.filename, replacecolor_B_g.colors, &replacecolor_B_g.count);

	char * path = "t.bmp";
	ClImgBMP bmp; // create a image var
	bmp.LoadImage(path); // load a bmpfile

	int width = bmp.bmpInfoHeaderData.biWidth;
	int height = bmp.bmpInfoHeaderData.biHeight;;
	int ch = bmp.bmpInfoHeaderData.biBitCount;
	printf("w=%d\t h=%d\t ch=%d\n", width, height, ch / 8);

	for (int w = 0; w < width; w++)
	{
		for (int h = 0; h < height; h++)
		{
			int ptr = ((w + (h*width)) * 3);
			//bmp.imgData[ptr + 0] // 0 red  1 green 2 blue

			//replace like this way: 
			bmp.imgData[ptr + 1] = chcol(bmp.imgData[ptr + 1], replacecolor_R_g.colors, &replacecolor_R_g.count);
			bmp.imgData[ptr + 2] = chcol(bmp.imgData[ptr + 2], replacecolor_R_b.colors, &replacecolor_R_b.count);
	
			//you can replace again using some other files
			//bmp.imgData[ptr + 2] = chcol(bmp.imgData[ptr + 2], replacecolor_B_g.colors, &replacecolor_B_g.count);//
																												 //
		}
	}

	bmp.SaveImage("test.bmp"); // save to disk
	system("pause");
	return 0;
}
