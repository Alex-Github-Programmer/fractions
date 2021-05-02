#ifndef _MANDELBROTJULIASET_H
#define _MANDELBROTJULIASET_H 0x010100

#define _BMP_GRADIENT
#define _BMP_TRANSFORM
#include "bmpEncoder.h"
#if _BMPENCODER_H < 0x010201
#error bmpEncoder.h lower than v1.2.1
#endif

#ifdef __cplusplus
extern "C" {
#endif

int mandelbrotSet(const char *filename, _ulong width, _ulong height, TRANSFORMATION transX, TRANSFORMATION transY, _ulong (*gradient)(_ulong)) {
	BITMAP *bitmap=BitmapHeaderInit(filename, 0, width, height);
	_ulong i, j, cnt;
	double x, y, m, n, p, q;
	for(i=0; i<height; ++i) {
		for(j=0; j<width; ++j) {
			x = Transform(transX, j);
			y = Transform(transY, i);
			m = 0;
			n = 0;
			for(cnt=0; cnt<137; cnt++) {
				p = m*m - n*n + x;
				q = 2*m*n + y;
				m = p;
				n = q;
				if(m*m + n*n > 4.0) break;
			}
			BitmapSetThrough(bitmap, (*gradient)(cnt));
		}
		BitmapWritePad(bitmap);
		BitmapFlush(bitmap);
	}
	BitmapClose(bitmap);
	return 0;
}

int juliaSet(const char *filename, _ulong width, _ulong height, TRANSFORMATION transX, TRANSFORMATION transY, double initX, double initY, _ulong (*gradient)(_ulong)) {
	BITMAP *bitmap=BitmapHeaderInit(filename, 0, width, height);
	_ulong i, j, cnt;
	double x, y, m, n, p, q;
	for(i=0; i<height; ++i) {
		for(j=0; j<width; ++j) {
			x = initX;
			y = initY;
			m = Transform(transX, j);
			n = Transform(transY, i);
			for(cnt=0; cnt<137; cnt++) {
				p = m*m - n*n + x;
				q = 2*m*n + y;
				m = p;
				n = q;
				if(m*m + n*n > 4.0) break;
			}
			BitmapSetThrough(bitmap, (*gradient)(cnt));
		}
		BitmapWritePad(bitmap);
		BitmapFlush(bitmap);
	}
	BitmapClose(bitmap);
	return 0;
}

#ifdef __cplusplus
}
#endif

#endif
