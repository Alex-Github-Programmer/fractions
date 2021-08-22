#include "bmpEncoder_v2_0_1.h"
#include "bmpPalette_v0_0_1.h"
int main() {
	int i, j;
	uint32_t absHeight, rowSize, pixelArraySize, offBits, size;
	BMP bmp = BMPInit(16*6+1, -16*4-1, 8, 25, colorChecker25, &absHeight, &rowSize, 
		&pixelArraySize, &offBits, &size);
	if(bmp == NULL) {
		puts("An error occured");
		return 0;
	}
	for(i=0; i<=16*4; ++i) {
		for(j=0; j<=16*6; ++j) {
			if((i & 15) && (j & 15)) {
				bmp[rowSize * i + j + offBits] = (i >> 4) * 6 + (j >> 4) + 1;
			} else {
				bmp[rowSize * i + j + offBits] = 0;
			}
		}
	}
	BMPsave(bmp, "colorChecker.bmp");
	puts("File created successfully");
	return 0;
}
