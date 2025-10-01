import cv2



mask = [
    [0,0,1,1,1,1,1,1,1,1,],
    [0,1,1,1,1,1,1,1,1,1,],
    [1,1,1,1,1,1,1,1,1,1,],
    [0,1,1,1,1,1,1,1,1,1,],
    [0,0,1,1,1,1,1,1,0,0,],
    ]

frames = []

for img_id in range(1,29):
    path = "./assets/compass{}.bmp".format(img_id)
    img = cv2.imread(path)
    x = 0
    y = 2
    colors = []
    while x < 10:
        if mask[y][x] == 1:
            colors.append(img[y][x])
        if x % 2 == 0:
            y -= 1
        else:
            y += 1
        if y < 0 or y > 4:
            x += 1
            if x % 2 == 0:
                y = 4
            else:
                y = 0
    frames.append(colors)

print("#pragma once")
print("#include <stdint.h>")
print("uint32_t frames[{0}][{1}] = ".format(len(frames), len(frames[0])))
print("{")
for frame in frames:
    print("{")
    for color in frame:
        g,b,r = color
        rgb = r << 16 | g << 8 | b
        print("{},".format(hex(rgb)))
    print("},")
print("};")