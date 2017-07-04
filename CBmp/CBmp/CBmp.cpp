#include "memory.h"
#include "math.h"
#include "stdint.h"
#include "stdlib.h"
#include "stdio.h"

unsigned char *bitmapImage;
int w = 1024;
int h = 768;
#pragma pack(1)   // 1 bytes对齐
struct RGB
{
	uint8_t r, g, b;
};

#define BI_RGB        0L

typedef   struct {
	uint16_t Signature;
	uint32_t Size;
	uint32_t Reserved;
	uint32_t BitsOffset;
} BITMAPFILEHEADER;

#define BITMAP_FILEHEADER_SIZE 14

typedef   struct {
	uint32_t HeaderSize;
	int32_t Width;
	int32_t Height;
	uint16_t Planes;
	uint16_t BitCount;
	uint32_t Compression;
	uint32_t SizeImage;
	int32_t PelsPerMeterX;
	int32_t PelsPerMeterY;
	uint32_t ClrUsed;
	uint32_t ClrImportant;
} BITMAPINFOHEADER;


bool SaveImage(char* szPathName, void* lpBits, int w, int h)
{
	BITMAPINFOHEADER BMIH;
	BITMAPFILEHEADER bmfh;

	FILE *pFile = fopen(szPathName, "wb");

	if (pFile == NULL)
	{
		return false;
	}

	BMIH.HeaderSize = sizeof(BITMAPINFOHEADER);
	BMIH.Width = w;
	BMIH.Height = h;
	BMIH.Planes = 1;
	BMIH.BitCount = 24;
	BMIH.Compression = BI_RGB;
	BMIH.SizeImage = w * h * 3;

	int nBitsOffset = sizeof(BITMAPFILEHEADER) + BMIH.HeaderSize;
	long lImageSize = BMIH.SizeImage;
	long lFileSize = nBitsOffset + lImageSize;
	bmfh.Signature = 'B' + ('M' << 8);
	bmfh.BitsOffset = nBitsOffset;
	bmfh.Size = lFileSize;
	bmfh.Reserved = 0;

	unsigned int nWrittenFileHeaderSize = fwrite(&bmfh, 1, sizeof(BITMAPFILEHEADER), pFile);
	unsigned int nWrittenInfoHeaderSize = fwrite(&BMIH, 1, sizeof(BITMAPINFOHEADER), pFile);
	unsigned int nWrittenDIBDataSize = fwrite(lpBits, 1, lImageSize, pFile);

	fclose(pFile);

	return true;

}

void setPixel(int x, int y, RGB rgb)
{
	int ptr = ((x + (y*w)) * 3);

	bitmapImage[ptr] = rgb.b;
	bitmapImage[ptr + 1] = rgb.g;
	bitmapImage[ptr + 2] = rgb.r;
}

int gcnt = 15;
int gw = w / gcnt;
int full = 255;
//调整下面的参数可以调颜色
int depth[15] = { 254,189,151,124,103,86,71,59,48,38,29,21,13,6,0 };
void Line()
{
	int i, j, c;
	RGB rgb;
	for (i = 0; i < w; i++)
	{
		rgb.r = full;
		c = depth[i / gw];
		rgb.g = c;
		rgb.b = c;
		//printf("%d\n", c);
		for (j = 0; j < h / 4; j++)
			setPixel(i, j, rgb);
	}

	for (i = 0; i < w; i++)
	{
		rgb.g = full;
		c = depth[i / gw];
		rgb.r = c;
		rgb.b = c;
		for (j = h / 4; j < h / 4 * 2.0f; j++)
			setPixel(i, j, rgb);
	}

	for (i = 0; i < w; i++)
	{
		rgb.b = full;
		c = depth[i / gw];
		rgb.r = c;
		rgb.g = c;
		for (j = h / 4 * 2.0f; j < h / 4 * 3.0f; j++)
			setPixel(i, j, rgb);
	}

	for (i = 0; i < w; i++)
	{
		c = depth[i / gw];
		rgb.r = c;
		rgb.g = c;
		rgb.b = c;
		for (j = h / 4 * 3.0f; j < h; j++)
			setPixel(i, j, rgb);
	}

}

int main()
{
	bitmapImage = (unsigned char*)malloc(w*h * 3);
	memset(bitmapImage, 0, w*h * 3);

	RGB color;
	color.r = 255;

	Line();
	color.g = 255;

	char fname[] = "test.bmp\0";
	SaveImage(fname, bitmapImage, w, h);
	system("pause");
	return 0;
}
