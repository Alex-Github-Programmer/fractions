#ifndef SANDPILEMODEL_H
#define SANDPILEMODEL_H 0x010001

#include <string.h>

#include "bmpEncoder.h"
#if _BMPENCODER_H < 0x010201
#error bmpEncoder.h lower than v1.2.1
#endif

#ifndef WIDTH
#define WIDTH 16389
#endif
#ifndef HEIGHT
#define HEIGHT 16389
#endif
#ifndef STACK_SIZE
#define STACK_SIZE 16384
#endif
#define STACK_OVERFLOW_ERROR 0x80000000

#ifdef __cplusplus
extern "C" {
#endif

_ulong _stack[STACK_SIZE + 8][2], _top;
_ulong count[WIDTH][HEIGHT];
int sandpileModel(const char* filename, _ulong width, _ulong height, _ulong originX, _ulong originY, _ulong color[], _ulong repeat) {
	_ulong i, j, m, n, q;
	memset(count, 0, sizeof(count));
	printf("z!");
	++originX;
	++originY;
	count[originX][originY] += repeat;
	_top = 1;
	_stack[0][0] = originX;
	_stack[0][1] = originY;
	while(_top) {
		--_top;
		m = _stack[_top][0];
		n = _stack[_top][1];
		if((m+1) && (width-m) && (n+1) && (height-n)) {
			if(count[m][n]>=4) {
#ifndef IGNORE_STACKOVERFLOW
				if(_top > STACK_SIZE) {
					return STACK_OVERFLOW_ERROR;
				}
#endif
				q = count[m][n] >> 2;
				count[m+1][n] += q; _stack[_top][0] = m+1; _stack[_top][1] = n; ++_top;
				count[m-1][n] += q; _stack[_top][0] = m-1; _stack[_top][1] = n; ++_top;
				count[m][n+1] += q; _stack[_top][0] = m; _stack[_top][1] = n+1; ++_top;
				count[m][n-1] += q; _stack[_top][0] = m; _stack[_top][1] = n-1; ++_top;
				count[m][n] &= 3;
			}
		}
	}
	BITMAP *bitmap = BitmapHeaderInit(filename, 0, width - 1, height - 1);
	for(i=1; i<=width; ++i) {
		for(j=1; j<=width; ++j) {
			BitmapSetThrough(bitmap, color[count[i][j]]);
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
