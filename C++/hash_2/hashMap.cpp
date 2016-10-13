#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <cstring>

template <class T>
class HashMap {
public:
	HashMap(const int& capacity) : capacity(capacity), size(0) {
		storage = std::vector<T*>(capacity);
	}
	bool set(const std::string& key, T& item) {
		// hash key, then store item at hashed key
		int index = hash(key);

		if (storage[index] == nullptr) {
			storage[index] = &item;
			size++;
			return true;
		}

		return false;
	}
	T get(const std::string& key) {
		// hash key, then return item at hashed key
		int index = hash(key);
		if (storage[index] == nullptr)
			return NULL;
		else
			return *storage[index];
	}
	T del(const std::string& key) {
		// hash key, then remove item at hashed key
		int index = hash(key);
		if (storage[index] == nullptr)
			return NULL;
		else {
			T item = *storage[index];
			storage[index] = nullptr;
			size--;
			return item;
		}
	}
	float loadFactor() {
		// return a float value representing the load factor of the data structure
		return (float)size / (float)capacity;
	}
private:
	std::vector<T*> storage;
	int capacity;
	int size;


	int hash(const std::string& key) {
		int keyLength = key.length();
		char ch[keyLength + 1];
		strcpy(ch, key.c_str());

		int sum = 0;
		for (int i = 0; i < keyLength; i++)
			sum += ch[i];
		return sum % capacity;
	}
};