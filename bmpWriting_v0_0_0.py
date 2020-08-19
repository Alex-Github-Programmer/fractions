'''
v0.0.0
For reading opreations of bitmap photo(*.bmp).
An optimized version with higher efficiency.
Raw code: http://exasic.com/article/index.php?md=py-bmp
'''
import array
class Image:
    def __init__(self, width, height, bgcolor = 0xffffff):
        self.width = width
        self.height = height
        if self.width * 3 % 4 == 0:
            self.data_size = self.width * 3 // 4 * self.height
            self.pad_bytes = 0
        else:
            self.data_size = (self.width * 3 // 4 + 1)  * self.height
            self.pad_bytes = 4 - self.width * 3 % 4
        self.file_size = self.data_size + 54
        self.bmp_header = [0x42, 0x4d, # 0
                           0, 0, 0, 0, # 2 file size
                           0, 0, 0, 0, # 6
                           54,0, 0, 0, #10
                           40,0, 0, 0, #14
                           0, 0, 0, 0, #18 width
                           0, 0, 0, 0, #22 height
                           1, 0, 24,0, #26
                           0, 0, 0, 0, #30
                           0, 0, 0, 0, #34 data size
                           0, 0, 0, 0, #38
                           0, 0, 0, 0, #42
                           0, 0, 0, 0, #46
                           0, 0, 0, 0  #50
                           ]           #53
        self._replace( 2, 4, self.file_size)
        self._replace(18, 4, self.width)
        self._replace(22, 4, self.height)
        self._replace(34, 4, self.data_size)
        self.rgb_data = [[bgcolor] * self.width
                         for i in range(self.height)]
    def _replace(self, offset, length, number):
        tmp = number
        for i in range(offset, offset + length):
            self.bmp_header[i] = tmp & 0xff
            tmp >>= 8
    def set_at(self,x, y, color):
        self.rgb_data[y][x] = color
    def save(self, path):
        f = open(path, 'wb')
        arr = array.array('B', self.bmp_header)
        for i in range(self.height):
            l = []
            for j in range(self.width):
                arr.extend((self.rgb_data[i][j]        & 0xff,
                           (self.rgb_data[i][j] >> 8)  & 0xff,
                           (self.rgb_data[i][j] >> 16) & 0xff))
            arr.extend((*bytes(self.pad_bytes), ))
        f.write(arr.tobytes())   
        f.close()
if __name__ == '__main__':
    image = Image(1920, 1080)
    for i in range(100, 1000):
        for j in range(100, 1000):
            image.set_at(i, j, i * 1000 + j)
    image.save('output.bmp')
