HOW TO RUN
============

`node knob.js`

The file can also be copied and pasted into the a browser's developer console. 


HOW IT WORKS
============

flatten(arr) is a function that accepts an arbitrarily-deep nested Array-like structure and returns a flattened structure with any null values removed.

It works by iterating through the array and running through three cases.

1) If the current element is a value that is neither an array or null, then it is pushed into the result array.

2) If the current element is an array nested within, then flatten() is recursively called on it to concatenate the nested array into the result array.

3) If the current element is null, then nothing happens. It is not pushed into the array.

Area of focus: front-end