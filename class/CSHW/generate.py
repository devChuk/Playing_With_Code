#brian chuk
import string
from PIL import Image, ImageColor, ImageDraw, ImageFont
from random import randint



print "please enter a name"
s = raw_input()
print "your letter is " + s[:1].upper()

r = randint(0,250)
g = randint(0,250)
b = randint(0,250)


im = Image.new("RGB",(800,800),(r,g,b))

draw = ImageDraw.Draw(im)

font = ImageFont.truetype("arial.ttf", 700)

draw.text((150, 35), s[:1].upper(), font=font)

del draw

im.save("output.png")
im.show()