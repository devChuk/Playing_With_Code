def intVerif():
	userInput = raw_input("Enter a number: ")
	if userInput.lstrip("-").isdigit():
		print("True")
		print(type(userInput))
	else:
		print("False")
		print(type(userInput))

intVerif()