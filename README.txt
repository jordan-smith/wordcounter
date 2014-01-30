wordCounter is a program that counts the number of occurences of each word in a text file.
I've implemented a trie to store the dictionary of words that gets accumulated. This
provides speedy access to stored words (since a trie's height depends on the length of the
longest prefix). Fast access and search is ideal for quickly comparing words and necessary
for applications I have in mind. The tradeoff with tries is that they tend to waste space
due to un-used pointers at each node. I've tried to decrease the space overhead by
dynamically adjusting the arrays of pointers at each node. Any node that represents a
fully formed word also holds an occurence counter.

The main method in wordCounter.cpp solicits input from the user in the form of a text file
and returns an alphabetized list of along with their occurence count.
