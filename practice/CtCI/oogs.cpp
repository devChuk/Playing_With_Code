
Array length: 100
[1, 2, 3, …, 99]

//if a number next to it is a duplicate, return that number

vector<int> arr; //[1,2,..99]

int binSearch(vector<int> &arr) {
	return binSearch(arr, 0, arr.size());
}

int binSearch(vector<int> &arr, int start, int end) {
	if (start == end) { //! end - start < 2
		return arr[start];
}
int mid = (start + end) / 2;

if (arr[mid] == 1 + mid) {				//follows the pattern
	return binSearch(arr, mid, end);
} else { 							//breaks pattern
	return binSearch(arr, start, mid);
}
}

[1,2,3,3,4]
0 5
mid = 2

binSearch(arr, 2, 5)
2 5
mid = 3

binSearch(arr, 2, 3)
4 5

while(



int binSearch(vector<int> &arr) {
	int start = 0;
	int end = arr.size();
while (true) {
	int mid = (start + end) / 2;
	if (mid != arr.size() - 1 && arr[mid] == arr[mid + 1]) {
		return arr[mid];
}
	if (mid != 0 && arr[mid] == arr[mid - 1]) {
		return arr[mid];
}
if (arr[mid] == 1 + mid) {		//follows the pattern
	start = mid;
} else { 					//breaks pattern
	end = mid;
}
}
}
