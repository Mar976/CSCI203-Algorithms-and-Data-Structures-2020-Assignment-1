# CSCI203-Algorithms-and-Data-Structures-2020

Description

This is assignment is based on AVL tree using array implementation. The program gets a text file as input and read each character and store it in the array of pool [], however when the character is space it will call a function insert to insert the word in the right leaf in the tree. To insert each word in the tree, it will check if the word already exists, then check if the word should go to the left side of tree or the right side. Once it reaches an empty leaf then the word will be stored in the tree. 
In the step, it will check if the tree is balanced, which compare the height leaves if the height is 2 than it will use appropriate rotate to rotate the nodes and keep the balance. This attribute of the AVL tree makes the program faster. I used an extra array to read the index from the avl tree into an array to use it to merge sort and then print.
Once the all the words are stored AVL tree then it will be merged sorted base on the count of each word. The merge sort keeps dividing the array into two part and sort each part, then merge. 
Once the array is sorted then the program will print the first and last 10 words in the array. 


Data Structure 

•	Struct Word: Word structure store the data, such as value, start index in pool, end index in pool, count of the word in the text file, index of the word in the left node, index of right word in the text array, depth of the current node in the AVL tree. I used it to store each word information when I am reading it from the file and store it in the array of words. Struct is better because it stores many information related to the one object under one name in a block a memory.
•	Text []: It is used to store word struct. I used this because in the assignment we were not supposed to use dynamic memory and in the left and right side of the words, we needed to store index, not Word. Therefore, it is more efficient to use array for accessing each word using index and sort it uses its index which makes the program faster. 
•	Pool []: It is used to store all the characters of the data file into array of character. It is better to use this because it will help us avoid dealing with array of string. The start and end integer store each word’s start index and end index in the array of pool respectively. 
•	Sorted[]: I used another array to read the avl tree into an index and use it to merge sort and then print the words using the sorted index. 


Standard Algorithm 

•	AVL Tree implementation using Array: AVL tree is a BST tree which is balanced. AVL tree is more efficient than BST because it keeps the tree balanced so in worst case the size of the problem will be O(Log n) when BST is O(n).
•	Merge Sort: Merge sort is more efficient compare to the other sort algorithm. I did few tests and I figure out the both quick sort and merge sort are both efficient that I used merge sort because I already have sorted array alphabetically using AVL tree so if I would use quick sort to sort base on count then I would lose the alphabetic order of the array. Therefore, I used merge sort which keep the alphabetic sort of the array while sorting the words with same count base on the count.  
