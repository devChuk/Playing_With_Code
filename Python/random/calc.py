while True:
	math = raw_input("Enter math: ")
	if ('+' in math):
		elements = math.partition('+')
		print int(elements[0]) + int(elements[2])
	elif '-' in math:
		elements = math.partition('-')
		print int(elements[0]) - int(elements[2])
	elif '/' in math:
		elements = math.partition('/')
		print int(elements[0]) - int(elements[2])
	elif '**' in math:
		elements = math.partition('**')
		print int(elements[0]) ** int(elements[2])
	elif '*' in math:
		elements = math.partition('*')
		print int(elements[0]) * int(elements[2])