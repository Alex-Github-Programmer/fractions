#ifndef _BMP_H
#define _BMP_H

#include <stdio.h>
#include <malloc.h>

#ifdef __cplusplus
extern "C" {
#endif

char bmpHeader[] = {
	0x42, 0x4d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 7
	0x00, 0x00, 0x36, 0x00, 0x00, 0x00, 0x28, 0x00, //15
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //23
	0x00, 0x00, 0x01, 0x00, 0x18, 0x00, 0x00, 0x00, //31
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //39
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //47
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00 //53
};
char pad[3] = {0, 0, 0};

struct _Bitmap {
	FILE* file;
	int flag;
	int	readable;
	long width;
	long height;
	long padSize;
	long rowSize;
	long dataSize;
	long fileSize;
};
typedef struct _Bitmap BITMAP;

BITMAP* BitmapInit(char* filename, int readable, unsigned long width, unsigned long height, unsigned long bgcolor) {
	BITMAP *bitmap = (BITMAP*)malloc(sizeof(BITMAP));
	bitmap -> file = fopen(filename, readable?"wb+":"wb");
	bitmap -> flag = ferror(bitmap -> file) ? 0 : 1;
	bitmap -> readable = readable;
	bitmap -> width = width;
	bitmap -> height = height;
	bitmap -> padSize = width % 4;
	bitmap -> rowSize = width * 3 + bitmap -> padSize;
	bitmap -> dataSize = bitmap -> rowSize * height;
	bitmap -> fileSize = bitmap -> dataSize + 54;
	*(unsigned long*)(bmpHeader + 0x02) = bitmap -> fileSize;
	*(unsigned long*)(bmpHeader + 0x12) = width;
	*(unsigned long*)(bmpHeader + 0x16) = height;
	*(unsigned long*)(bmpHeader + 0x22) = bitmap -> dataSize;
	fwrite(bmpHeader, 54, 1, bitmap -> file);
	fflush(bitmap -> file);
	unsigned long i, j;
	for(i=0; i<height; ++i) {
		for(j=0; j<width; ++j){
			fwrite((char*)&bgcolor, 3, 1, bitmap -> file);
		}
		fwrite(pad, bitmap -> padSize, 1, bitmap -> file);
		fflush(bitmap -> file);
	}
	return bitmap;
}
void BitmapSetAt(BITMAP* bitmap, unsigned long x, unsigned long y, unsigned long color) {
	fseek(bitmap -> file, 54 + bitmap -> rowSize * x + 3 * y, 0);
	fwrite((char*)&color, 3, 1, bitmap -> file);
}
void BitmapFlush(BITMAP* bitmap) {
	fflush(bitmap -> file);
}
void BitmapClose(BITMAP* bitmap) {
	fclose(bitmap -> file);
}

#ifdef __cplusplus
}
#endif

#endif
