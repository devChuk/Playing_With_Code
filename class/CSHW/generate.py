import string
import random
from PIL import Image, ImageColor, ImageDraw



print "please enter a name"
s = raw_input()
print "your letter is " + s[:1].upper()


im = Image.new("RGB",(800,800),"red")

x, y =  im.size
eX, eY = 30, 60 #Size of Bounding Box for ellipse

box =  [0, 0, x, y]
draw = ImageDraw.Draw(im)

# Image.new("RGB", (600, 600), (250, 250, 400))

# draw.rectangle([0, 0, x, y],fill = 1) # it works, but it needs color


del draw

im.save("output.png")
im.show()