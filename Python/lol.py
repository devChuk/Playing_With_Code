import random;
while (True):
	answer = input("I'm guessing a number between 1 and 10. What is it?\n")
	cheese = random.randrange(11)
	if answer == cheese:
		print "Yes you got it!\n"
	else:
		print "nope! my number is " + str(cheese) + "\n";