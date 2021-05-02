#ifndef _FEIGENBAUMGRAPH_H
#define _FEIGENBAUMGRAPH_H 0x010000

#include <string.h>

#define _BMP_TRANSFORM
#include "bmpEncoder.h"
#if BMPENCODER_H < 0x010201
#error bmpEncoder.h lower than v1.2.1
#endif

#ifdef __cplusplus
extern "C" {
#endif

int feigenbaumGraph(const char* filename, _ulong width, _ulong height, TRANSFORMATION trans, double left, double right, _ulong preRepeat, _ulong repeat, _ulong max) {
	BITMAP *bitmap=BitmapHeaderInit(filename, 0, width, -height);
	_ulong i, j, gray;
	_ulong grayScale[width];
	double rate, x;
	for(i=0; i<height; ++i) {
		memset(grayScale, 0, sizeof(grayScale));
		rate = Transform(trans, i);
		x = 0.5;
		for(j=0; j<preRepeat; ++j) {
			x *= rate * (1-x);
		}
		for(j=0; j<repeat; ++j) {
			x *= rate * (1-x);
			if(grayScale[(int)(x * width)] < max){
				++grayScale[(int)(x * width)];
			}
		}
		for(j=0; j<width; ++j) {
			gray = (max-grayScale[j]) * 255 / max;
			BitmapSetThrough(bitmap, (gray<<16) | (gray<<8) | gray);
		}
		BitmapWritePad(bitmap);
		BitmapFlush(bitmap);
		if(i%10==0)printf("%lu\n",i);
	}
	BitmapClose(bitmap);
	return 0;
}

#ifdef __cplusplus
}
#endif

#endif
