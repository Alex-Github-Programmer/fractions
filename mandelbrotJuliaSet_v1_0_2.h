#ifndef _MANDELBROTJULIASET_H
#define _MANDELBROTJULIASET_H 0x010002

#include "bmpWriting.h"
#if _BMP_H < 0x010102
#error bmpWriting.h lower than v1.1.2
#endif

int mandelbrotSet(const char *path, _ulong width, _ulong height) {
	BITMAP* bitmap=BitmapHeaderInit(path, 0, width, height);
	_ulong i, j, cnt;
	double x, y, m, n, p, q, ratio = height / 4.0;
	for(i=0; i<height; ++i) {
		for(j=0; j<width; ++j) {
			x = (long)(j - width/2) / ratio;
			y = (long)(i - height/2) / ratio;
			m = 0;
			n = 0;
			for(cnt=0; cnt<121; cnt++) {
				p = m*m - n*n + x;
				q = 2*m*n + y;
				m = p;
				n = q;
				if(m*m + n*n > 4.0) break;
			}
			BitmapSetThrough(bitmap, BitmapRainbowColor(cnt));
		}
		BitmapWritePad(bitmap);
		BitmapFlush(bitmap);
	}
	BitmapClose(bitmap);
	return 0;
}

#endif
