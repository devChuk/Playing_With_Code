import datetime
import time

print "please enter q to quit"
f = open('attendance.csv', 'w')
while True:
	n = raw_input()
	if (n == "q"):
		break
	print "you entered", n
	d = unicode(datetime.datetime.now())
	f.write(d + "," + n + "\n")