# Aho-Corasick-algorithm
Program that does the following:
* Create a function that constructs the failure links trie of a given set of pattens.
* Create a function that searches for occurrences of all these patterns (exact matching) within another text string using Aho-Corasick algorithm. Use the failure links trie of the above function.
* Test the function in main() on the example in lecture and make sure it outputs the exact (ti, pj) and Rep(). Let the function output all these information.
* comments explaining the code before each code line, the test case, and following the CodingStyle.pdf file.

# Functions 
* InitializeTables
```
function to convert from int to char and vice versa
```
* CreateTrieNode
```
Function to create node
```
* InitializeTrie
```
Function to initialize the root of trie
```
* InsertTriePattern
```
Function to insert each pattern in the trie
```
* InsertRead
```
Function to conver each pattern to integer array.
```
* Display
```
Function to print all content of trie.
```
* getAllProperSuffixs
```
Function to calculate propersuffix.
```
* QueryTrieRead
```
Function to search in trie of a given propersuffix converted to integer numbers.
```
* SearchInTrie
```
Function to Search in trie of given proper suffix.
```
* CreatFailureLink
```
Function to Create failure link of each node in the trie.
```
* Search
```
Function to Search of number of pattern in given text.
```
* DeleteTrie
```
Function to delete the trie.
```
