import bmpWriting
import random
def barnsleyFern(trans, chance = None, local = None,
                 size = (2048, 2048), color = (0xffffff, 0x000000), 
                 init = None, depth = 1048576, path = 'barnsleyFern.bmp'):
    image = bmpWriting.Image(*size, color[0])
    pos = list(init) if init else [0, 0]
    local = local if local else \
            bmpWriting.Local_coordination('E', (-1, -1), (1, 1), 1024)
    for i in range(depth):
        tran = random.choices(trans, chance)[0]
        pos_new = [tran[0] * pos[0] + tran[1] * pos[1] + tran[2],
                   tran[3] * pos[0] + tran[4] * pos[1] + tran[5]]
        pos = pos_new
        if image.inside(*local.from_local(pos)):
            image.set_at(*local.from_local(pos), color[1])
    image.save(path)
if __name__ == '__main__':
    barnsleyFern([[-0.4612054658106728, -0.18421622013526684, 0.8200018614245714,
                   0.15062308605687624, 0.41509321981152447, -0.5373931075075806],
                  [0.26327130338062843, 0.5142767793873098, -0.8317557319488103,
                   -0.30130288141285844, -0.9472499158717338, 0.14965908236378955],
                  [0.7567452477825529, 0.11446012746460865, -0.9593268923020173,
                   -0.3906129343789404, -0.4944958073044887, 0.8444025798579378],
                  [0.5859588616172846, -0.24440463574371707, 0.4884664320542753,
                   0.21812280807019113, 0.9922412572329409, -0.027338667080179624
                   ]], size = (8192, 8192), local = bmpWriting.Local_coordination
                 ('E', (-4, -4), (4, 4), 1024), color = (0xffffff, 0x000000),
                 path = 'barnsleyFern-1.bmp', depth = 8468608)
    barnsleyFern([[-0.8053954407762309, -0.18361422478483602, -0.9824207839520669,
                   -0.19690520535264744, -0.7507788290664514, 0.11991281795594189],
                  [0.10248461418228816, -0.5203002036913256, -0.79246827759979,
                   0.3113374505268285, -0.6845915282866444, -0.798386302521046],
                  [-0.2749644429702729, -0.4480841623728815, 0.27815226074147104,
                   0.8141092645093131, 0.28241766712086136, -0.8554621750171876],
                  [-0.28726876174143623, 0.286191988002406, -0.30939082334651413,
                   -0.33405646822768764, 0.1732377940493861, 0.6277837300242732]],
                 size = (8192, 8192), local = bmpWriting.Local_coordination
                 ('E', (-4, -4), (4, 4), 1024), color = (0xffffff, 0x000000),
                 path = 'barnsleyFern-2.bmp', depth = 8468608)
    
