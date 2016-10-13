#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <functional>
#include <algorithm>
#include <math.h>

bool uniqueChars(std::string input) {
	// std::vector<std::string> chars;
	// for (int i = 0; i < input.length; i++) {
	// 	if (chars.indexOf(input.str(i,i+1))  == -1)
	// 		chars.push_back(input.str(i,i+1));
	// 	else
	// 		return false;
	// 	return true;
	// }
	//////////
	// std::vector<std::string> chars;
	// for (int i = 0; i < input.length(); i++) {
	// 	if (std::find(chars.begin(),chars.end(),input.substr(i,i+1))  == chars.end())
	// 		chars.push_back(input.substr(i,i+1));
	// 	else
	// 		return false;
	// }
	// return true;
	///////////
	for (int i = 0; i < input.length(); i++) {
		for (int j = i + 1; j < input.length(); j++) {
			if (input.substr(i,i+1) == input.substr(j,j+1))
				return false;
		}
	}
	return true;
}

void reverse(char* str) {
	// char* end = str;
	// char* ans;
	// if (*str) {
	// 	while (*end)
	// 		end++;
	// 	while (*end != *str) {
	// 		ans = end;
	// 		ans++;
	// 		*end--;
	// 	}
	// }
	// return ans;
	////////////
	char* end = str;
	char tmp;
	if (*str) {
		while (*end)
			end++;
		end--;
		while (end > str) {
			tmp = *str;
			*str++ = *end;
			*end-- = tmp;
		}
	}
}

bool permuCheck(std::string strA, std::string strB) {
	if (strA.length() == strB.length()) {
		std::sort(strA.begin(), strA.end());
		std::sort(strB.begin(), strB.end());
		for (int i = 0; i < strA.length(); i++)
			if (strA[i] != strB[i])
				return false;
		return true;
	} else
	return false;
	
	// OR, MAKE AN ARRAY THAT RECORDS THE FREQUENCY OF ALL POSSIBLE CHARS
	// THEN HAVE IT RECORD THE FREQ OF CHARS IN strA, then remove/compare with strB.
}


// "Mr|John|||Smith|"
void replaceTwenty(std::string& str, int length) {
	int count = 0, newLength;

	for (int i = 0; i < length; i++)
		if (str[i] == ' ')
			count++;

	newLength = length + 2 * count;
	str[newLength] = '\0';

	for (int i = length - 1; i >= 0; i--) {
		if (str[i] == ' ') {
			str[newLength - 1] = '0';
			str[newLength - 2] = '2';
			str[newLength - 3] = '%';
			newLength = newLength -3;
		} else {
			str[newLength - 1] = str[i];
			newLength--;
		}
	}
}

int main() {
	// std::cout << uniqueChars("abcda") << std::endl;
	// std::cout << uniqueChars("abcd") << std::endl;

	// char somebuffer[100] = "a string";
	// char* ptr = somebuffer;  // ptr now points to somebuffer
	// std::cout << ptr << std::endl; // prints "a string"
	// reverse(ptr);
	// std::cout << ptr << std::endl; // prints "a string"

	// std::cout << permuCheck("abcd","dcba") << std::endl;
	// std::cout << permuCheck("abcd","dcbacc") << std::endl;
	// std::cout << permuCheck("abcd","aacd") << std::endl;
	
	std::string charlie = "Mr John Smith    ";
	replaceTwenty(charlie, 13);
	std::cout << charlie << std::endl;








	return 0;
}