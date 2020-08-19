import array
import sys
sys.setrecursionlimit(10000000)
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
##        self.rgbData = []
##        for r in range(self.h):
##            self.rgbDataRow = []
##            for c in range(self.w):
##                self.rgbDataRow.append(color)
##            self.rgbData.append(self.rgbDataRow)
        rgbDataRow = [color] * (self.w+1)
        self.rgbData = [rgbDataRow.copy() for i in range(self.h)]
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
sand = list([0] * 2003 for i in range(2003))
final = ''
image = bmp(2003, 2003)
image.gen_bmp_header()
image.print_bmp_header()
image.paint_bgcolor(0x000000)
def update(i, j):
    if i == 0 or i == 2002 or j == 0 or j == 2002:
        sand[i][j] = 0
    elif sand[i][j] >= 4:
        q = sand[i][j] // 4
        sand[i + 1][j] += q
        sand[i - 1][j] += q
        sand[i][j + 1] += q
        sand[i][j - 1] += q
        sand[i][j] %= 4
        update(i + 1, j)
        update(i - 1, j)
        update(i, j + 1)
        update(i, j - 1)
for i in range(40000):
    sand[1001][1001] += 1
    update(1001, 1001)
    if i%100==0:print(i)
for i in range(1, 2003):
    for j in range(1, 2003):
        image.set_at(i, j, [0x0000ff, 0x00ffff, 0x00ff00, 0xff0000][sand[i][j]])
    if i%100==0:print(i)
image.save_image('sand.bmp')
