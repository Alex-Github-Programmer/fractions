'''
v0.1.0
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
        self.bmp_header = [0] * 54
        self.bmp_header[ 0] = 0x42
        self.bmp_header[ 1] = 0x4d
        self.bmp_header[10] = 54
        self.bmp_header[14] = 40
        self.bmp_header[26] =  1
        self.bmp_header[28] = 24
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
    def set_at(self, x, y, color):
        self.rgb_data[int(y)][int(x)] = Color(color).to_hex()
    def get_at(self, x, y):
        return self.rgb_data[int(y)][int(x)]
    def inside(self, x, y):
        return 0 <= x < self.width and 0 <= y < self.height
    def save(self, path):
        f = open(path, 'wb')
        arr = array.array('B', self.bmp_header)
        for i in range(self.height):
            for j in range(self.width):
                arr.extend((self.rgb_data[i][j]        & 0xff,
                           (self.rgb_data[i][j] >> 8)  & 0xff,
                           (self.rgb_data[i][j] >> 16) & 0xff))
            arr.extend((*bytes(self.pad_bytes), ))
        f.write(arr.tobytes())   
        f.close()
class Local_coordination:
    def __init__(self, typestr, arg1, arg2, scale):
        if typestr == 'E' or typestr == 'e':
            self.var1 = (-arg1[0], -arg1[1])
        elif typestr == 'C' or typestr == 'c':
            self.var1 = (-arg1[0] + arg2[0] / 2, -arg[1] + arg2[1] / 2)
        else:
            raise ValueError(typestr)
        self.var2 = scale
    def from_local(self, pos):
        return ((pos[0] + self.var1[0]) * self.var2,
                (pos[1] + self.var1[1]) * self.var2)
def from_local(pos, typestr, arg1, arg2, scale):
    return Local_cordination(typestr, arg1, arg2, scale).global_to_local(pos)
class Color:
    def __init__(self, arg):
        if isinstance(arg, __class__):
            self.red = arg.red
            self.green = arg.green
            self.blue = arg.blue
        elif isinstance(arg, int):
            self.red = arg >> 16
            self.green = (arg >> 8) & 0xff
            self.blue = arg & 0xff
        else:
            self.red, self.green, self.blue = arg
    def to_rgb(self):
        return (self.red, self.green, self.blue)
    def to_hex(self):
        return (self.red << 16) | (self.blue << 8) | self.green
    def from_int(self, x):
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
            return 0xffffff
def hex_to_rgb(x):
    return Color(x).to_rgb()
def rgb_to_hex(x):
    return Color(x).to_hex()
def int_gradient_to_rgb(x):
    return Color(x).to_rgb()
def int_gradient_to_hex(x):
    return Color(x).to_hex()
if __name__ == '__main__':
    image = Image(1920, 1080)
    for i in range(100, 1000):
        for j in range(100, 1000):
            image.set_at(i, j, i * 1000 + j)
    image.save('output.bmp')
