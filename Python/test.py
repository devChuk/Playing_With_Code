alpha = {'a': 2, 'b': 3, 'c': 5, 'd': 7, 'e': 11, 'f': 13, 'g': 17,	'h': 19, 'i': 23, 'j': 29, 'k': 31,	'l': 37, 'm': 41, 'n': 43, 'o': 47, 'p': 53, 'q': 59, 'r': 61, 's': 67, 't': 71, 'u': 73, 'v': 79, 'w': 83, 'x': 89, 'y': 97, 'z': 101}


dic = ["swag", "swagger", "world", "hello"]
res = "llo worldhe"

def geniusHash( str ):
	product = 1
	for s in str:
		product = product * alpha[s]
	return product

def findWords( str ):
	finhash = str.replace(" ", "")
	finhash = geniusHash(finhash)
	print finhash
	# for word in dic:


findWords( "llo worldhe" )
findWords( "hello world" )