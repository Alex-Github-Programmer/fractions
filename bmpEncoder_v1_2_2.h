#ifndef _BMPENCODER_H
#define _BMPENCODER_H 0x010202

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

typedef unsigned long _ulong;
struct _Bitmap {
	FILE* file;
	int flag;
	int readable;
	_ulong width;
	_ulong height;
	_ulong padSize;
	_ulong rowSize;
	_ulong dataSize;
	_ulong fileSize;
};
typedef struct _Bitmap BITMAP;

BITMAP* BitmapHeaderInit(const char* filename, int readable, _ulong width, _ulong height) {
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
	*(_ulong*)(bmpHeader + 0x02) = bitmap -> fileSize;
	*(_ulong*)(bmpHeader + 0x12) = width;
	*(_ulong*)(bmpHeader + 0x16) = height;
	*(_ulong*)(bmpHeader + 0x22) = bitmap -> dataSize;
	fwrite(bmpHeader, 54, 1, bitmap -> file);
	fflush(bitmap -> file);
	return bitmap;
}
BITMAP* BitmapInit(const char* filename, int readable, _ulong width, _ulong height, _ulong bgcolor) {
	BITMAP *bitmap = BitmapHeaderInit(filename, readable, width, height);
	_ulong i, j;
	for(i=0; i<height; ++i) {
		for(j=0; j<width; ++j){
			fwrite((char*)&bgcolor, 3, 1, bitmap -> file);
		}
		fwrite(pad, bitmap -> padSize, 1, bitmap -> file);
		fflush(bitmap -> file);
	}
	return bitmap;
}
inline void BitmapSetAt(BITMAP* bitmap, _ulong x, _ulong y, _ulong color) {
	fseek(bitmap -> file, 54 + bitmap -> rowSize * x + 3 * y, 0);
	fwrite((char*)&color, 3, 1, bitmap -> file);
}
inline void BitmapSetThrough(BITMAP* bitmap, _ulong color) {
	fwrite((char*)&color, 3, 1, bitmap -> file);
}
inline void BitmapGetAt(BITMAP* bitmap, _ulong x, _ulong y, _ulong* color) {
	fseek(bitmap -> file, 54 + bitmap -> rowSize * x + 3 * y, 0);
	fread((char*)color, 3, 1, bitmap -> file);
}
inline void BitmapGetThrough(BITMAP* bitmap, _ulong* color) {
	fread((char*)color, 3, 1, bitmap -> file);
}
inline void BitmapWritePad(BITMAP* bitmap) {
	fwrite(pad, bitmap -> padSize, 1, bitmap -> file);
}
inline void BitmapSeek(BITMAP* bitmap, _ulong x, _ulong y) {
	fseek(bitmap -> file, 54 + bitmap -> rowSize * x + 3 * y, 0);
}
inline void BitmapFlush(BITMAP* bitmap) {
	fflush(bitmap -> file);
}
inline void BitmapClose(BITMAP* bitmap) {
	fclose(bitmap -> file);
}

#ifdef _BMP_GRADIENT
inline _ulong GradientShort(_ulong x) {
	switch(x / 15) {
		case 0: return 0xff00ff | (15-x) * 17 << 8;
		case 1: return 0x0000ff | (30-x) * 17 << 16;
		case 2: return 0x0000ff | (x-30) * 17 << 8;
		case 3: return 0x00ff00 | (60-x) * 17;
		case 4: return 0x00ff00 | (x-60) * 17 << 16;
		case 5: return 0xff0000 | (90-x) * 17 << 8;
		case 6: return 0xff0000 | (x-90) * 17 << 16;
		case 7: return (120-x) * 17 << 16;
		default:return 0x000000;
	}
	return 0;
}
inline _ulong GradientShortReversed(_ulong x) {
	switch(x / 15) {
		case 0: return 0xff00ff | (15-x) * 17 << 8;
		case 1: return 0xff0000 | (30-x) * 17;
		case 2: return 0xff0000 | (x-30) * 17 << 8;
		case 3: return 0x00ff00 | (60-x) * 17 << 16;
		case 4: return 0x00ff00 | (x-60) * 17;
		case 5: return 0x0000ff | (90-x) * 17 << 8;
		case 6: return 0x0000ff | (x-90) * 17;
		case 7: return (120-x) * 17;
		default:return 0x000000;
	}
	return 0;
}
inline _ulong GradientLong(_ulong x) {
	switch(x / 17) {
		case 0: return 0xff00ff | (17-x) * 15 << 8;
		case 1: return 0x0000ff | (34-x) * 15 << 16;
		case 2: return 0x0000ff | (x-34) * 15 << 8;
		case 3: return 0x00ff00 | (68-x) * 15;
		case 4: return 0x00ff00 | (x-68) * 15 << 16;
		case 5: return 0xff0000 | (102-x)* 15 << 8;
		case 6: return 0xff0000 | (x-102)* 15 << 16;
		case 7: return (136-x) * 15 << 16;
		default:return 0x000000;
	}
	return 0;
}
inline _ulong GradientLongReversed(_ulong x) {
	switch(x / 17) {
		case 0: return 0xff00ff | (17-x) * 15 << 8;
		case 1: return 0xff0000 | (34-x) * 15;
		case 2: return 0xff0000 | (x-34) * 15 << 8;
		case 3: return 0x00ff00 | (68-x) * 15 << 16;
		case 4: return 0x00ff00 | (x-68) * 15;
		case 5: return 0x0000ff | (102-x)* 15 << 8;
		case 6: return 0x0000ff | (x-102)* 15;
		case 7: return (136-x) * 15;
		default:return 0x000000;
	}
	return 0;
}
#endif

#ifdef _BMP_CONVERT
#warning BMP_CONVERT submodule deprecated
inline double ConvertCenter(double midpoint, double ratio, double width, double coord) {
	return midpoint + (coord - width / 2) / ratio;
}
inline double ConvertLeftEdge(double edge, double ratio, double coord) {
	return edge + coord / ratio;
}
inline double ConvertBothEdge(double left, double right, double width, double coord) {
	return left + coord * (right - left) / width;
}
#endif

#ifdef _BMP_TRANSFORM
struct _Transformation {
	double left;
	double scale;
};
typedef struct _Transformation TRANSFORMATION;

inline TRANSFORMATION TransformCenter(double center, double scale, double width) {
	TRANSFORMATION transformation;
	transformation.left = center - scale * width / 2;
	transformation.scale = scale;
	return transformation;
}
inline TRANSFORMATION TransformLeftEdge(double left, double scale) {
	TRANSFORMATION transformation;
	transformation.left = left;
	transformation.scale = scale;
	return transformation;
}
inline TRANSFORMATION TransformBothEdge(double left, double right, double width) {
	TRANSFORMATION transformation;
	transformation.left = left;
	transformation.scale = (right - left) / width;
	return transformation;
}

inline double Transform(TRANSFORMATION transformation, double coordinate) {
	return coordinate * transformation.scale + transformation.left; 
}
#endif

#ifdef __cplusplus
}
#endif

#endif
