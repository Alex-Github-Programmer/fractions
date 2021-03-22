#include "bmpWriting.h"
BITMAP* bitmap;
_ulong i, j, cnt;
double x, y, m, n, p, q;
int main() {
	bitmap=BitmapHeaderInit("mandelbrotSet.bmp", 0, 2048, 1536);
	for(i=0; i<1536; ++i) {
		for(j=0; j<2048; ++j) {
			x = (j - 1024.0) / 384.0;
			y = (i - 768.0) / 384.0;
			m = 0;
			n = 0;
			for(cnt=0; cnt<106; cnt++) {
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
