import array
from math import *
from random import random
import os
class bmp:
    """ bmp data structure """

    def __init__(self, w=1080, h=1920):
        self.w = w
        self.h = h
    def calc_data_size (self):
        if((self.w*3)%4 == 0):
            self.dataSize = self.w * 3 * self.h
        else:
            self.dataSize = (((self.w * 3) // 4 + 1) * 4) * self.h

        self.fileSize = self.dataSize + 54
    def conv2byte(self, l, num, len):
        tmp = num
        for i in range(len):
            l.append(tmp & 0x000000ff)
            tmp >>= 8
    def gen_bmp_header (self):
        self.calc_data_size();
        self.bmp_header = [0x42, 0x4d]
        self.conv2byte(self.bmp_header, self.fileSize, 4) #file size
        self.conv2byte(self.bmp_header, 0, 2)
        self.conv2byte(self.bmp_header, 0, 2)
        self.conv2byte(self.bmp_header, 54, 4) #rgb data offset
        self.conv2byte(self.bmp_header, 40, 4) #info block size
        self.conv2byte(self.bmp_header, self.w, 4)
        self.conv2byte(self.bmp_header, self.h, 4)
        self.conv2byte(self.bmp_header, 1, 2)
        self.conv2byte(self.bmp_header, 24, 2) #888
        self.conv2byte(self.bmp_header, 0, 4)  #no compression
        self.conv2byte(self.bmp_header, self.dataSize, 4) #rgb data size
        self.conv2byte(self.bmp_header, 0, 4)
        self.conv2byte(self.bmp_header, 0, 4)
        self.conv2byte(self.bmp_header, 0, 4)
        self.conv2byte(self.bmp_header, 0, 4)
    def print_bmp_header (self):
        length = len(self.bmp_header)
        for i in range(length):
            print("{:0>2x}".format(self.bmp_header[i]), end=' ')
            if i%16 == 15:
                print('')
        print('')
    def paint_bgcolor(self, color=0xffffff):
        self.rgbData = []
        for r in range(self.h):
            self.rgbDataRow = []
            for c in range(self.w):
                self.rgbDataRow.append(color)
            self.rgbData.append(self.rgbDataRow)
    def set_at(self,x, y, color):
        self.rgbData[y][x] = color
    def paint_line(self, x1, y1, x2, y2, color):
        k = (y2 - y1) / (x2 - x1)
        for x in range(x1, x2+1):
            y = int(k * (x - x1) + y1)
            self.rgbData[y][x] = color

    def paint_rect(self, x1, y1, w, h, color):
        for x in range(x1, x1+w):
            for y in range(y1, y1+h):
                self.rgbData[y][x] = color
    def save_image(self, name="save.bmp"):
        f = open(name, 'wb')

        #write bmp header
        f.write(array.array('B', self.bmp_header).tobytes())

        #write rgb data
        zeroBytes = self.dataSize // self.h - self.w * 3

        for r in range(self.h):
            l = []
            for i in range(len(self.rgbData[r])):
                p = self.rgbData[r][i]
                l.append(p & 0x0000ff)
                p >>= 8
                l.append(p & 0x0000ff)
                p >>= 8
                l.append(p & 0x0000ff)

            f.write(array.array('B', l).tobytes())

            for i in range(zeroBytes):
                f.write(bytes(0x00))
        f.close()
def calc_color(x):
    if 0 <= x < 16:
        return 0xffffff - x * 256 * 17
    elif 16 <= x < 32:
        return 0xff00ff - (x - 16) * 256 * 256  * 17
    elif 32 <= x < 48:
        return 0x0000ff + (x - 32) * 256 * 17
    elif 48 <= x < 64:
        return 0x00ffff - (x - 48) * 17
    elif 64 <= x < 80:
        return 0x00ff00 + (x - 64) * 256 * 256 * 17
    elif 80 <= x < 96:
        return 0xffff00 - (x - 80) * 256 * 17
    elif 96 <= x < 112:
        return 0xff0000 - (x - 96) * 256 * 256 * 17
    else:
        raise TypeError(x)
def calc_x(m, r, w, x):
    return m + (x - w) / r
def calc_y(m, r, h, y):
    return m + (y - h) / r
def main(g):
    image = bmp(2048, 1536)
    image.gen_bmp_header()
    image.print_bmp_header()
    image.paint_bgcolor(0x123456)
    p = random() * 2 - 1
    q = random() * 2 - 1
    print(complex(p, q))
    for i in range(2048):
        for j in range(1536):
            #x = (i - 1024) / 384
            #y = (j - 768) / 384
            #x = (i - 1908) / 1536
            #y = (j - 216) / 1536
            #x = calc_x(-219 / 384 - 614 / 98304 - 51 / 25165824, 402653184, 1024, i)
            #y = calc_x(246 / 384 - 272 / 98304 - 359 / 25165824, 402653184, 768, j)
            #x = calc_x(-219 / 384 + 212 / 6144 - 458 / 98304, 1572864, 1024, i)
            #y = calc_x(246 / 384 - 704 / 6144 - 59 / 98304, 1572864, 768, j)
            x = calc_x(0, 384, 1024, i)
            y = calc_x(0, 384, 768, j)
            #x = calc_x(-219 / 384 + 152 / 6144, 98304, 1024, i)
            #y = calc_x(246 / 384 - 129 / 6144, 98304, 768, j)
            #x = calc_x(-219 / 384 + 943 / 6144, 98304, 1024, i)
            #y = calc_x(246 / 384 - 271 / 6144, 98304, 768, j)
            #x = calc_x(138 / 384 + 9 / 6144 - 660 / 98304, 98304, 1024, i)
            #y = calc_x(247 / 384 - 11 / 6144 + 434 / 98304, 98304, 768, j)
            #x = calc_x(0, 6144, 1024, i)
            #y = calc_x(1, 6144, 768, j)
            m = complex(x, y)
            n = complex(p, q)
            #m = 1
            #n = -0.4 + 0.6j
            #n = 0.285
            #n = -0.70176 - 0.3842j
            #n = 0.5 + 0.5j
            #m = complex(x, y)
            cnt = 0
            while cnt < 111:
                m = m * m + n
                #m = m * m * n - n
                #m = n * m * (1 - m)
                if abs(m) > 2:
                    break
                cnt += 1
            #if cnt == 111:
            #    print('mandelbrot')
            image.set_at(i, j, calc_color(cnt))
        if i % 16 == 15:
            print(f'rendering... {i / 2048 * 100:.2f}%({i}/2048)')
    image.save_image("julia-%d.bmp" % g)
for i in range(400, 500):
    main(i)
os.system('pause')
