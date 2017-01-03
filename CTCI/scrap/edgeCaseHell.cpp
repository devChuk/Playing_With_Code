/*
The Pursuit of Good Code: How to Handle Edge Cases
This is a very rough draft of ideas. For now, I'm just going to play with edge cases here

Good Code is code that's never finished.
It mutates, due to both intended and unintended changes. 

Document it, and make the mutations as simple as you can, but no simpler.
Don’t be a dick. Try to teach others about your decisions for each mutation.

Good Code is documented and simple. It's 

Perfection is not what we aim for. It's what to start with.

A good coder is like a good pool player.

When you see a professional pool player, you at first might not be impressed:
"Sure, they got all of the balls in, but they had only easy shots!" This is because,
when a pool player is making her shot, she doesn't think about what ball will go into
which pocket, she's also thinking about where the cue ball will end up. Setting up
for the next shot takes tremendous skill and practice, but it also means that it
looks easy.

Now, bringing this metaphor to code, a good coder writes code that looks like it was
easy and straightforward to do. Many of the examples by Brian Kernighan in his books
follow this pattern. Part of the "trick" is coming up with a proper conceptualization
of the problem and its solution. When we don't understand a problem well enough,
we're more likely to over-complicate our solutions, and we will fail to see unifying
ideas.

With a proper conceptualization of the problem, you get everything else: readability,
maintainability, efficiency, and correctness. Because the solution seems so
straightforward, there will likely be fewer comments, because extra explanation is
unnecessary. A good coder can also see the long term vision of the product, and form
their conceptualizations accordingly.

quiet insanity
https://medium.com/@landongn/12-years-later-what-i-ve-learned-about-being-a-software-engineer-d6e334d6e8a3#.lnnqky9xe
http://softwareengineering.stackexchange.com/questions/17443/what-does-it-mean-to-write-good-code
*/



/*
Edge Cases
https://www.quora.com/How-can-I-get-better-at-handling-edge-cases-in-computer-programming

Can the list be empty?
Can this while loop run infinitely? Perhaps stick with for loops as less
flexibility leads to fewer changes to mess up.

Correctness:
extreme large numbers
extreme negative numbers
arithmetic overflows
^long long ints to the rescue

single number
empty array


very large arrays
large long sequence of ones
large long sequence of minus ones


https://codility.com/demo/take-sample-test/
*/

// you can use includes, for example:
// #include <algorithm>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

int solution(vector<int> &A) {
    // write your code in C++14 (g++ 6.2.0)
    if (A.size() == 0)
        return -1;
    if (A.size() == 1)
        return 0;
    
    long long int leftSideSum = 0;
    long long int rightSideSum = 0;
    int pointer = 0;
    for (int i = 1; i < A.size(); i++) {
        rightSideSum += (long long) A[i];   
    }
    
    while (pointer < A.size()) {
        //std::cout << leftSideSum << " " << rightSideSum << std::endl;
        if (leftSideSum == rightSideSum)
            return pointer;
        pointer++;
        leftSideSum += (long long) A[pointer - 1];
        rightSideSum -= (long long) A[pointer];
    
    return -1;
}


int main() {


	return 0;
}