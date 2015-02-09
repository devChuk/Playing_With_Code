import string
import random
from PIL import Image, ImageDraw



print "please enter a name"
s = raw_input()
print "your letter is " + s[:1].upper()


im = Image.open("output.png")

x, y =  im.size
eX, eY = 30, 60 #Size of Bounding Box for ellipse

bbox =  (0, 0, x, y)
draw = ImageDraw.Draw(im)
draw.rectangle(bbox) # it works, but it needs color
del draw

im.save("output.png")
im.show()