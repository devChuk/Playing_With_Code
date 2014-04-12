/*
Here is an example!
function addContact(id, refreshCallback) {
    refreshCallback();
    // You can also pass arguments if you need to
    // refreshCallback(id);
}

function refreshContactList() {
    alert('Hello World');
}

addContact(1, refreshContactList);
*/

/* Here is the prompt!
1. 

var map=function(L,F){...}

map takes a list and a function and returns a new list where each element is 
the result of applying F on each element.

So, map([1,2,3,4,5],function(x){return x*x;}) would return [1,4,9,16,25]

2. 

var filter=function(L,F) {...}

filter takes a list and a function and returns a new list where only those elements that return true for F(e) will be in the new list.

So, filter([1,2,3,4,5,6],function(x) { return x%2==0;}) would return
[2,4,6]
*/

function map(_list,Func) {
	var ans = new Array();
	_list.forEach(function(entry) {
		ans.push(Func(entry));
	});
	console.log(_list);
	console.log(ans);
}


function filter(_list,Func) {
	var ans = new Array();
	_list.forEach(function(entry) {
		if (Func(entry))
			ans.push(entry);
	})
	console.log(_list);
	console.log(ans);
}

