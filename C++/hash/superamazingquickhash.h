#ifndef SUPERAMAZINGQUICKHASH_H
#define SUPERAMAZINGQUICKHASH_H
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
	using namespace std;

class Holder {
public:
    enum Type {
        BOOL,
        INT,
        STRING,
        // Other types you want to store into vector.
    };

    template<typename T>
    Holder (Type type, T val);

    ~Holder () {
        // You want to properly destroy
        // union members below that have non-trivial constructors
    }

    operator bool () const {
        if (type_ != BOOL) {
           throw SomeException();
        }
        return impl_.bool_;
    }
    // Do the same for other operators
    // Or maybe use templates?

private:
    union Impl {
        bool   bool_;
        int    int_;
        string string_;

        Impl() { new(&string_) string; }
    } impl_;

    Type type_;

    // Other stuff.
};


// template <class T>
// class HashEntry {	
// private:
// 	string key;
// 	T* value;
// public:
// 	HashEntry();
// 	HashEntry(string key, T& value);
// 	string getKey();
// 	T getValue();
// };

// class HashMap {
// private:
// 	HashEntry** table;
// public:
// 	HashMap(int size);				//	return an instance of the class with pre-allocated space for the given number of objects.
// // 	bool set(string key, T value);	// stores the given key/value pair in the hash map. Returns a boolean value indicating success / failure of the operation.
// // 	T get(string key);				// return the value associated with the given key, or null if no value is set.
// // 	T delete(string key);			// delete the value associated with the given key, returning the value on success or null if the key has no value.
// // 	float load();					// return a float value representing the load factor (`(items in hash map)/(size of hash map)`) of the data structure. Since the size of the dat structure is fixed, this should never be greater than 1.
// };

// // template<class T>
// // HashEntry<T>::HashEntry() : key(""), value(NULL) {}

// template<class T>
// HashEntry<T>::HashEntry(string key, T& value) : key(key), value(&value) {}

// template<class T>
// string HashEntry<T>::getKey() {return key;}

// template<class T>
// T HashEntry<T>::getValue() {return *value;}

// template<class T>
// HashMap::HashMap(int size) {
// 	table = new HashEntry<T>*[size];
//     for (int i = 0; i < size; i++)
//           table[i] = NULL;
// }

#endif