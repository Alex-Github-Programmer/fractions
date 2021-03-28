#ifndef _MANDELBROTJULIASET_H
#define _MANDELBROTJULIASET_H 0x010003

#include "bmpWriting.h"
#if _BMP_H < 0x010103
#error bmpWriting.h lower than v1.1.3
#endif

int mandelbrotSet(const char *path, _ulong width, _ulong height, double xpos, double ypos, double ratio, _ulong (*gradient)(_ulong)) {
	BITMAP* bitmap=BitmapHeaderInit(path, 0, width, height);
	_ulong i, j, cnt;
	double x, y, m, n, p, q;
	for(i=0; i<height; ++i) {
		for(j=0; j<width; ++j) {
			x = BitmapConvertCenterLocalCoord(xpos, ratio, width, j);
			y = BitmapConvertCenterLocalCoord(ypos, ratio, height, i);
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

int juliaSet(const char *path, _ulong width, _ulong height, double xpos, double ypos, double ratio, double initX, double initY, _ulong (*gradient)(_ulong)) {
	BITMAP* bitmap=BitmapHeaderInit(path, 0, width, height);
	_ulong i, j, cnt;
	double x, y, m, n, p, q;
	for(i=0; i<height; ++i) {
		for(j=0; j<width; ++j) {
			x = initX;
			y = initY;
			m = BitmapConvertCenterLocalCoord(xpos, ratio, width, j);
			n = BitmapConvertCenterLocalCoord(ypos, ratio, height, i);
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

#endif
