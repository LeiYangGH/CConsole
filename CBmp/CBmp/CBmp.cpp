#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#include<math.h>

#ifdef _cplusplus
extern "c" {
#endif

#pragma pack(1)


	typedef struct BM {
		char  pBM[2];
		int   nSize;
		short nReserve1;
		short nReserve2;
		int   nOffset;
	} BM;


	typedef struct biheader {
		int   nSize; //size（48）
		int   nWidth; //长
		int   nHeight; //宽
		short nPlanes; //平面数
		short nBitCount; //色数
		int   nCompression; //压缩
		int   nSizeImage; //图片的尺寸
		int   nXPixPerMeter;
		int   nYPixPerMeter;
		int   nClrUsed;
		int   nCirImportant;
	} BIHEADER;

	typedef struct rgb {
		unsigned char B;
		unsigned char G;
		unsigned char R;
	} RGB;

	typedef struct rgbquad {
		unsigned char B;
		unsigned char G;
		unsigned char R;
		unsigned char Reserved;
	}RGBQUAD;

	typedef struct image {
		BM        biBitmap;
		BIHEADER  biHeader;
		RGBQUAD       *pPallet;
		RGB   *pRGB;
	}IMAGE;



#pragma pack()
#ifdef _cplusplus
}
#endif

void print_rgb(RGB x)
{
	printf("R,G,B = (%u,%u,%u)\n", x.R, x.G, x.B);
	//printf("蓝　%u\n",x.B);
	//printf("蓝　%u\n",x.B);
	//printf("蓝　%u\n",x.B);
}


void print_header(BIHEADER x)
{
	printf("尺寸48                  　  %d [byte]\n", x.nSize);
	printf("图片长                              %d [pix]\n", x.nWidth);
	printf("图片宽                            %d [pix]\n", x.nHeight);
	printf("平面数                           %d \n", x.nPlanes);
	printf("色数                         %d [bit]\n", x.nBitCount);
	printf("压缩                            %d [byte]\n", x.nCompression);
	printf("图片的尺寸                          %d [byte]\n", x.nSizeImage);
	printf("X轴方向解像度          %d [pix/m]\n", x.nXPixPerMeter);
	printf("Y轴方向解像度          %d [pix/m]\n", x.nYPixPerMeter);
	printf("                                      %d\n", x.nClrUsed);
	printf("                                      %d\n", x.nCirImportant);
}

void print_BM(BM x)
{
	printf("%c%c\n", x.pBM[0], x.pBM[1]);
	printf("Size    %d\n", x.nSize);
	printf("Reserve %d\n", x.nReserve1);
	printf("Reserve %d\n", x.nReserve2);
	printf("Offset  %d\n", x.nOffset);
}

unsigned char RGB2Index(const RGB val)
{
	unsigned char uRet;
	uRet = 255; //val.G;
	return (uRet);
}

int ResizeImage(IMAGE *img, int nWidth, int nHeight)
{
	if (img->biHeader.nBitCount == 24) {
		img->biBitmap.nSize = 12 + 40 + ((1 << img->biHeader.nBitCount) * sizeof(RGBQUAD)) + (nHeight*nWidth*img->biHeader.nBitCount / 8);
	}

	img->biHeader.nWidth = nWidth;
	img->biHeader.nHeight = nHeight;
	img->biHeader.nSizeImage = img->biHeader.nWidth*img->biHeader.nHeight*img->biHeader.nBitCount / 8;

	free(img->pRGB);
	if (img->biHeader.nBitCount != 24) {
		img->pRGB = (RGB*)malloc(img->biHeader.nWidth*img->biHeader.nHeight*img->biHeader.nBitCount / 8);
		memset(img->pRGB, 0, img->biHeader.nWidth*img->biHeader.nHeight*img->biHeader.nBitCount / 8);
	}//asita  else{
	 // img->pRGB=(RGB*)malloc(sizeof(RGB)*img->biHeader.nWidth*img->biHeader.nHeight*img->biHeader.nBitCount/8);
	 // memset(img->pRGB,0,img->biHeader.nWidth*img->biHeader.nHeight*img->biHeader.nBitCount/8);
	 // }
	return 0;//
}


IMAGE *CreateImage(void)
{
	IMAGE *hRet = NULL;
	int i;
	int nWidth = 500;
	int nHeight = 700;
	int nBitCount = 24; /* 8; */
	int j, k;//tuika
	int size = 10;// tuika

	hRet = (IMAGE*)malloc(sizeof(IMAGE));
	if (hRet != NULL) {
		hRet->biBitmap.pBM[0] = 'B';
		hRet->biBitmap.pBM[1] = 'M';
		if (nBitCount == 24) {
			hRet->biBitmap.nSize = 12 + 40 + (nHeight*nWidth*nBitCount / 8);
		}
		else {
			hRet->biBitmap.nSize = 12 + 40 + ((1 << nBitCount) * sizeof(RGBQUAD)) + (nHeight*nWidth*nBitCount / 8);
		}

		hRet->biBitmap.nReserve1 = 0;
		hRet->biBitmap.nReserve2 = 0;
		if (nBitCount != 24) {
			hRet->biBitmap.nOffset = 54 + (1 << nBitCount) * sizeof(RGBQUAD);
		}
		else {
			hRet->biBitmap.nOffset = 54;
		}
		//
		hRet->biHeader.nSize = 40;
		hRet->biHeader.nWidth = nWidth;
		hRet->biHeader.nHeight = nHeight;
		hRet->biHeader.nPlanes = 1;
		hRet->biHeader.nBitCount = nBitCount;
		hRet->biHeader.nCompression = 0;
		hRet->biHeader.nSizeImage = hRet->biHeader.nWidth*hRet->biHeader.nHeight*hRet->biHeader.nBitCount / 8;
		hRet->biHeader.nXPixPerMeter = 0;
		hRet->biHeader.nYPixPerMeter = 0;
		if (hRet->biHeader.nBitCount != 24) {
			hRet->biHeader.nClrUsed = 1 << hRet->biHeader.nBitCount;
			hRet->biHeader.nCirImportant = 1 << hRet->biHeader.nBitCount;
		}
		else {
			hRet->biHeader.nClrUsed = 0;
			hRet->biHeader.nCirImportant = 0;
		}
		//
		if (hRet->biHeader.nBitCount != 24) {
			hRet->pPallet = (RGBQUAD*)malloc(sizeof(RGBQUAD)*(1 << hRet->biHeader.nBitCount));
			for (i = 0; i<1 << hRet->biHeader.nBitCount; i++) {
				hRet->pPallet[i].R = i;
				hRet->pPallet[i].G = i;
				hRet->pPallet[i].B = i;
				hRet->pPallet[i].Reserved = 0;
			}
		}
		else {
			hRet->pPallet = NULL;
		}
		//
		if (hRet->biHeader.nBitCount != 24) {
			hRet->pRGB = (RGB*)malloc(hRet->biHeader.nWidth*hRet->biHeader.nHeight*hRet->biHeader.nBitCount / 8);
			memset(hRet->pRGB, 255, hRet->biHeader.nWidth*hRet->biHeader.nHeight*hRet->biHeader.nBitCount / 8);
		}
		else {
			hRet->pRGB = (RGB*)malloc(sizeof(RGB)*hRet->biHeader.nWidth*hRet->biHeader.nHeight);
			memset(hRet->pRGB, 255, sizeof(RGB)*hRet->biHeader.nWidth*hRet->biHeader.nHeight);
		}
		/*
		//tuika
		for(j=0; j=size; j++){
		for(k=0; k=size; k++){
		hRet->pPallet[i].R=100;
		hRet->pPallet[i].G=100;
		hRet->pPallet[i].B=100;
		hRet->pPallet[i].Reserved=0;
		}
		}

		//tuika
		*/
	}
	return (hRet);
}

void PrintImage(IMAGE *img) {
	int i;
	print_BM(img->biBitmap);
	print_header(img->biHeader);
	if (img->biHeader.nClrUsed>0) {
		for (i = 0; i<img->biHeader.nClrUsed; i++) {
			printf("Pallet #%d  R, G, B,*=(%d,%d,%d,%d)\n", i,
				img->pPallet[i].R,
				img->pPallet[i].G,
				img->pPallet[i].B,
				img->pPallet[i].Reserved);
		}
	}
}

void SaveImage(IMAGE *img, const char *pFilename)
{
	FILE *fp = NULL;

	fp = fopen(pFilename, "wb");
	if (fp != NULL) {
		fwrite(&(img->biBitmap), sizeof(BM), 1, fp); //header
		fwrite(&(img->biHeader), sizeof(BIHEADER), 1, fp);//zyouhou
		if (img->biHeader.nClrUsed>0) {
			//pal gaso
			fwrite(img->pPallet, sizeof(RGBQUAD), img->biHeader.nClrUsed, fp);
			fwrite(img->pRGB, 1,
				img->biHeader.nHeight*
				img->biHeader.nWidth*
				img->biHeader.nBitCount / 8, fp);
		}
		else {
			//gaso
			fwrite(img->pRGB, sizeof(RGB),
				img->biHeader.nHeight*
				img->biHeader.nWidth*
				img->biHeader.nBitCount / 8, fp);
		}
	}
}

//#define nHeight 100
//#define nWidth 100

int main(int argc, char *argv[]) {

	FILE *fp = NULL;
	FILE *fp2 = NULL;
	BM x, x2;
	BIHEADER y, y2;
	RGB *c = NULL;
	unsigned char *c2 = NULL;
	int i, j;
	int nHeight, nWidth;
	RGBQUAD pal[256]; //256色
	unsigned char Release;
	//unsigned char image[nHeight][nWidth][3];
	unsigned char image[100][100][3];
	unsigned char R;
	unsigned char G;
	unsigned char B;
	IMAGE *pImage = NULL;

	//读写
	fp = fopen("test.bmp", "rb");
	if (fp == NULL) {
		exit(1);
		//goto Release;
	}

	pImage = CreateImage();
	PrintImage(pImage);
	SaveImage(pImage, "hoge.bmp");

	exit(1);


	fread(&x, sizeof(x), 1, fp);
	fread(&y, sizeof(y), 1, fp);
	print_BM(x);
	print_header(y);


	nHeight = y.nHeight;
	nWidth = y.nWidth;

	printf("%d %d\n", nHeight, nWidth);


	c = (RGB*)malloc(sizeof(RGB)*nHeight*nWidth);
	if (c == NULL) {
		printf("失败\n");
		//goto Release;
		exit(1);
	}

	c2 = (unsigned char*)malloc(nHeight*nWidth);
	if (c2 == NULL) {
		printf("失败\n");
		//goto Release;
		exit(1);
	}



	fread(c, sizeof(RGB), nHeight*nWidth, fp);

	for (j = 0; j < nHeight; j++) {
		for (i = 0; i < nWidth; i++) {
			print_rgb(c[nWidth*j + i]);
		}
	}


	//另存为
	fp2 = fopen("out.bmp", "wb");
	if (fp2 == NULL) {
		printf("失败 \n");
		exit(1);
	}


	x2 = x;
	y2 = y;

	//x2更新
	{
		x2.nSize = 12 + 40 + 1024 + (nHeight*nWidth); //size计算
		x2.nOffset = x2.nOffset + 1024; //+1024
	}

	//y2更新
	{
		//y2.nheight = y.nheight*2
		//y2.nwidth = y.nwidth*2
		//y2.nSizeimage = y.nSizeimage*4
		y2.nBitCount = 8;//8bit
		y2.nSizeImage = y2.nWidth*y2.nHeight*y2.nBitCount / 8;
		y2.nClrUsed = 256; //256色
		y2.nCirImportant = 256;
	}


	//颜色准备

	for (i = 0; i<256; i++) {
		pal[i].R = i;
		pal[i].G = i;
		pal[i].B = i;
		pal[i].Reserved = 0;
	}

	//c2存为c
	for (j = 0; j < nHeight; j++) {
		for (i = 0; i < nWidth; i++) {
			c2[nWidth*j + i] = RGB2Index(c[nWidth*j + i]);
		}
	}

	/*
	for(j = 0; j < nHeight; j++) {
	for(i = 0; i < nWidth; i++) {
	//间隔线

	c2[nWidth*j+i]; R=100;
	c2[nWidth*j+i]; G=100;
	c2[nWidth*j+i]; B=100;
	}
	}
	*/

	//头
	fwrite(&x2, sizeof(x2), 1, fp2);
	//写入
	fwrite(&y2, sizeof(y2), 1, fp2);
	//pal　代入
	fwrite(pal, sizeof(RGBQUAD), 256, fp2);
	//代入2
	fwrite(c2, sizeof(unsigned char), nHeight*nWidth, fp2);

Release:


	if (c != NULL) {
		free(c);
	}

	if (c2 != NULL) {
		free(c2);
	}
	if (fp2 != NULL) {
		fclose(fp2);
	}

	if (fp != NULL) {
		fclose(fp);
	}

	return 0;
}
/*
//间隔线（黑）


c2[168*90+i] G=255
c2[168*90+i] B=255

//间隔线（白）

c2[168*60+i] R=0
c2[168*60+i] G=0
c2[168*60+i] B=0
*/