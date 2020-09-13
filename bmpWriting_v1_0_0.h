#include<stdio.h>
#include<string.h>
#include<malloc.h>
#ifdef __cplusplus
class Image {
	public:
		int width;
		int height;
		int data_size;
		int file_size;
		int pad_bytes;
		char bmp_header[54];
		int *rgb_data;
		Image(int width, int height, int bgcolor) {
			this -> width = width;
			this -> height = height;
			if(this -> width * 3 % 4 == 0) {
				this -> data_size = this -> width * 3 / 4 * this -> height;
				this -> pad_bytes = 0;
			}
			else {
				this -> data_size = (this -> width * 3 / 4 + 1) * this -> height;
				this -> pad_bytes = 4 - this -> width * 3 % 4;
			}
			this -> file_size = this -> data_size + 54;
			memset(this -> bmp_header, 0, sizeof(this -> bmp_header));
			this -> bmp_header[ 0] = 0x42;
			this -> bmp_header[ 1] = 0x4d;
			this -> bmp_header[10] = 54;
			this -> bmp_header[14] = 40;
			this -> bmp_header[26] =  1;
			this -> bmp_header[28] = 24;
			this -> _replace( 2, 4, this -> file_size);
			this -> _replace(18, 4, this -> width);
			this -> _replace(22, 4, this -> height);
			this -> _replace(34, 4, this -> data_size);
			this -> rgb_data = (int*) calloc(height * width, sizeof(int));
			for(int i = 0; i < height * width; i ++) {
				this -> rgb_data[i] = bgcolor;
			}
		}
		void set_at(int x, int y, int color) {
			this -> rgb_data[x * this -> width + y] = color;
		}
		void save(char path[]) {
			FILE* fp = fopen(path, "wb");
			for(int i = 0; i < 54; i ++) {
				fputc(this -> bmp_header[i], fp);
			}
			for(int i = 0; i < this -> height; i ++) {
				for(int j = 0; j < this -> width; j ++) {
					fputc( this -> rgb_data[i * this -> width + j]		& 0xff, fp);
					fputc((this -> rgb_data[i * this -> width + j] >>  8) & 0xff, fp);
					fputc((this -> rgb_data[i * this -> width + j] >> 16) & 0xff, fp);
				}
				for(int j = 0; j < this -> pad_bytes; j ++) {
					fputc(0, fp);
				}
			}
			fclose(fp);
		}
		bool inside(int x, int y) {
			return	(0 <= x && x < this -> width) ||
					(0 <= y && y < this -> height)
		}
		
	private:
		void _replace(int offset, int length, int number) {
			int tmp = number;
			for(int i = offset; i < offset + length; i ++) {
				this -> bmp_header[i] = tmp & 0xff;
				tmp >>= 8;
			}
		}
};
class Local_coordination {
	public:
		double offset_x;
		double offset_y;
		double scale;
		Local_coordination(char typestr, double m_l, double m_t, double s_r, double s_b, double scale) {
			if(typestr == 'E' || typestr == 'e') {
				this -> offset_x = -m_l;
				this -> offset_x = -m_t;
			}
			else if(typestr == 'C' || typestr == 'c') {
				this -> offset_x = -m_l + s_r / 2;
				this -> offset_x = -m_t + s_b / 2;
			}
		}
		int from_local_x(double pos_x) {
			return (pos_x + this -> offset_y) * this -> scale
			
		}
		int from_local_y(double pos_y) {
			return (pos_y + this -> offset_y) * this -> scale
		}
		
};
int from_local_x(double pos_x, char typestr, double m_l, double m_t, double s_r, double s_b, double scale) {
	return Local_coordination(typestr, m_l, m_t, s_r, s_b, scale).from_local_x(pos_x);
}
int from_local_y(double pos_y, char typestr, double m_l, double m_t, double s_r, double s_b, double scale) {
	return Local_coordination(typestr, m_l, m_t, s_r, s_b, scale).from_local_y(pos_y);
}
class Color {
	public:
		int red;
		int green;
		int blue;
		Color(int red, int green, int blue) {
			this -> red = red;
			this -> green = green;
			this -> blue = blue;
		}
		Color(int hex) {
			this -> red = arg >> 16;
		    this -> green = (arg >> 8) & 0xff;
		    this -> blue = arg & 0xff;
		}
		int to_hex() {
			return (this -> red << 16) | (this -> blue << 8) | this -> green;
		}
		Color from_int(int x) {
		    if(0 <= x < 16)
			    return Color(0xffffff - x * 256 * 16);
			else if(16 <= x < 32)
			    return Color(0xff00ff - (x - 16) * 256 * 256  * 16);
			else if(32 <= x < 48)
			    return Color(0x0000ff + (x - 32) * 256 * 16);
		    else if(48 <= x < 64)
			    return Color(0x00ffff - (x - 48) * 16);
		    else if(64 <= x < 80)
			    return Color(0x00ff00 + (x - 64) * 256 * 256 * 16);
		    else if(80 <= x < 96)
			    return Color(0xffff00 - (x - 80) * 256 * 16);
		    else if(96 <= x < 112)
			    return Color(0xff0000 - (x - 96) * 256 * 256 * 16);
		    else
			    return Color(0xffffff);
		}
};
#else
#endif
