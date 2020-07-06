import array
from math import *
import os
class bmp:
    def __init__(self, width, height):
        self.width = width
        self.height = height
    def calc_data_size(self):
        self.dataSize = ceil(self.width * 3 / 4)
        self.fileSize = self.dataSize + 54
    def convert(self, num, length):
        t = num
        for i in range(length):
            self.header.append(t & 0xff)
            t >>= 8
    def gen_header(self):
        self.calc_data_size();
        self.header = [0x42, 0x4d]
        self.convert(self.fileSize, 4)
        self.convert(0, 2)
        self.convert(0, 2)
        self.convert(54, 4)
        self.convert(40, 4)
        self.convert(self.width, 4)
        self.convert(self.height, 4)
        self.convert(1, 2)
        self.convert(24, 2)
        self.convert(0, 4)
        self.convert(self.dataSize, 4)
        self.convert(0, 4)
        self.convert(0, 4)
        self.convert(0, 4)
        self.convert(0, 4)
    def background(self, color = 0xffffff):
        self.rgbData = [[color] * self.width
                        for i in range(self.height)]
    def set_at(self, x, y, color):
        self.rgbData[y][x] = color
    def save_image(self, name="save.bmp"):
        f = open(name, 'wb')
        f.write(array.array('B', self.header).tobytes())
        zeroBytes = self.dataSize // self.height - self.width * 3
        for r in range(self.height):
            l = []
            for i in range(len(self.rgbData[r])):
                p = self.rgbData[r][i]
                l.append(p & 0x0000ff)
                p >>= 8
                l.append(p & 0x0000ff)
                p >>= 8
                l.append(p & 0x0000ff)
            f.write(array.array('B', l).tobytes())
            if zeroBytes > 0:
                f.write(bytes(zeroBytes))
        f.close()
    def print_header(self):
        length = len(self.header)
        for i in range(length):
            print("{:0>2x}".format(self.header[i]), end=' ')
            if i % 16 == 15:
                print('')
        print('')
def calc_color(x):
    if 0 <= x < 16:
        return 0xffffff - x * 256 * 16
    elif 16 <= x < 32:
        return 0xff00ff - (x - 16) * 256 * 256  * 16
    elif 32 <= x < 48:
        return 0x0000ff + (x - 32) * 256 * 16
    elif 48 <= x < 64:
        return 0x00ffff - (x - 48) * 16
    elif 64 <= x < 80:
        return 0x00ff00 + (x - 64) * 256 * 256 * 16
    elif 80 <= x < 96:
        return 0xffff00 - (x - 80) * 256 * 16
    elif 96 <= x < 112:
        return 0xff0000 - (x - 96) * 256 * 256 * 16
    else:
        return 0x000000
def calc_x(m, r, w, x):
    return m + (x - w) / r
def calc_y(m, r, h, y):
    return m + (y - h) / r
def main():
    image = bmp(2048, 1536)
    image.gen_header()
    image.background()
    for i in range(2048):
        for j in range(1536):
            x = calc_x(0, 384, 1024, i)
            y = calc_x(0, 384, 768, j)
            m = 0
            n = complex(x, y)
            cnt = 0
            while cnt < 112:
                m = m * m + n
                if abs(m) > 2:
                    break
                cnt += 1
            image.set_at(i, j, calc_color(cnt))
        if i % 16 == 15:
            print(f'rendering... {i / 2048 * 100:.2f}%({i}/2048)')
    image.save_image("mandelbrot_temp.bmp")
main()
