#include "bmpWriting.h"
_ulong RainbowColor(_ulong x) {
	if(0<=x && x<15) {
		return 0xff00ff | (15-x) *17 << 8;
	} else if(15<=x && x<30) {
		return 0xff0000 | (30-x) * 17;
	} else if(30<=x && x<45) {
		return 0xff0000 | (x-30) * 17 << 8;
	} else if(45<=x && x<60) {
		return 0x00ff00 | (60-x) * 17 << 16;
	} else if(60<=x && x<75) {
		return 0x00ff00 | (x-60) * 17;
	} else if(75<=x && x<90) {
		return 0x0000ff | (90-x) * 17 << 8;
	} else if(90<=x && x<105) {
		return 0x0000ff | (x-90) * 17;
	} else {
		return 0x000000;
	}
}
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
			BitmapSetThrough(bitmap, RainbowColor(cnt));
		}
		BitmapWritePad(bitmap);
		BitmapFlush(bitmap);
	}
	BitmapClose(bitmap);
	return 0;
}
