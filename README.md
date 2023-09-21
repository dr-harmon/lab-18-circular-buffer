# Lab 18: Circular Buffer

In this lab we will implement a simple array-like ADT of a fixed capacity. It should support the following operations:

* Initialize the ADT with a given capacity. The number of elements must never exceed this amount.
* Insert an element at a given index:
    * If the index is between 0 and `size - 1`, then the elements after the index will be shifted up to make room for the new element.
    * If the index equals the current size of the list, then the new element will simply be added to the end.
    * For any other index, the insert method should throw an exception.
    * The `insert` method should throw an exception if the size of the list equals the maximum capacity.
* Delete an element at a given index:
    * If the index is between 0 and `size - 1`, then the elements after the index will be shifted down to fill in the empty space.
    * Otherwise, the `delete` method should throw an exception.
* Get or set an element at a given index using the subscript operator (`[]`).
* Get the current size of the ADT.
* Write a character representatiom of the ADT to an output stream.

## Part 1: Basic Implementation

A skeleton class called `CircularBuffer` has been provided for you. Your task is to implement all of the missing methods until all unit tests pass.

Note:

* The underlying data structure can be a C array, STL array, STL vector, or any other suitable type.
* The stream insertion operator (`<<`) is already implemented and can be used for debugging in `main`. 
* The exact type of exceptions you throw and what they contain are up to you. As long as you throw an exception under the appropriate conditions, the tests should pass.
* For the insertion and deletion operations, you might find the pseudocode in [Code Fragment 6.1](https://learning-oreilly-com.lpclibrary.idm.oclc.org/library/view/data-structures-and/9780470383278/ch06.html#methods_insert_open_parenthesis_i_comma) in the textbook to be helpful.

Do not continue to the next step until all unit tests pass. That would be a good time to commit your work in source control so that you can revert to a "known good" copy if needed.

## Part 2: 0-Index Optimizations

Insertion and deletion in an array is `O(n)`, but inserting or deleting at the end is constant time. We can use a simple trick to make inserting or deleting at the _beginning_ constant time as well. The trick is to make the array _circular_, meaning that the first element can start at any position in the underlying array (not just index 0), and any elements that would extend past the end of the array wrap around to the beginning.

Your task, then, is to modify your array ADT so that inserting or deleting elements at the beginning is an `O(1)` operation. This optimization should not alter the correctness or performance of any other operation.

To implement this optimization and make the array circular, you will need to:

* Add a new private member that keeps track of the location of the first element as an offset into the underlying array (e.g. `start`).
* Modify all indexing operations so that they account for the fact that the first element could be at any position in the underlying array. This can be done by adding the requested index to the starting offset, modulo the total size of the underlying array.
* Add special cases to the `insert` and `delete` methods so that, if the requested index is 0, the starting offset is simply adjusted and no `O(n)` operations are required.
