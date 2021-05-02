#ifndef BARNSLEYFERN_H
#define BARNSLEYFERN_H 0x010000

#include <stdlib.h>

#define _BMP_TRANSFORM
#include "bmpEncoder.h"
#if _BMPENCODER_H < 0x010202
#error bmpEncoder.h lower than v1.2.2
#endif

#ifdef __cplusplus
extern "C" {
#endif

int barnsleyFern(const char *filename, _ulong width, _ulong height, TRANSFORMATION transX, TRANSFORMATION transY, _ulong count, double affine[][6], _ulong repeat, _ulong bgcolor, _ulong fgcolor) {
	BITMAP *bitmap=BitmapInit(filename, 0, width, height, bgcolor);
	_ulong random;
	double x = 0, y = 0, x_, y_;
	_ulong i, j;
	while(repeat--) {
		random = rand() % count;
		x_ = x * affine[random][0] + y * affine[random][1] + affine[random][2];
		y_ = x * affine[random][3] + y * affine[random][4] + affine[random][5];
		x = x_;
		y = y_;
		i = Transform(transX, x);
		j = Transform(transY, y);
		printf("%lu %lu\n", i, j);
		if(i < width && j < height) {
			BitmapSetAt(bitmap, i, j, fgcolor);
		}
	}
	BitmapClose(bitmap);
	return 0;
}

#ifdef __cplusplus
}
#endif

#endif
